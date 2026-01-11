#include <openHAL/openHAL.h>
#include <openHAL/clock/st_clock.h>
#include <openHAL/gpio/st_gpio.h>
#include <openHAL/timer/systick.h>
#include <openHAL/uart/st_uart.h>
#include <openHAL/bitops.h>

extern ohal_ClockOps g_stClockOps;
extern ohal_GpioOps g_stGpioOps;
extern ohal_TimerOps g_sysTickOps;
extern ohal_UartOps g_stUartOps;

ohal_StClock_PeriphClk periphClkEn[] =
{
    OHAL_ST_CLOCK_PERIPH_GPIOA,
    OHAL_ST_CLOCK_PERIPH_GPIOB,
    OHAL_ST_CLOCK_PERIPH_LPUART1,
};

ohal_StClock_Cfg clkCfg =
{
    .sysClkSrc = OHAL_ST_CLOCK_SYSCLK_SRC_PLL,
    .sysClkCfg.pll =
    {
        .clkSrc = OHAL_ST_CLOCK_PLLCLK_SRC_MSI,
        /* 64 MHz */
        .n = 32,
        .m = 0,
        .r = 1,
        .q = 0,
        .p = 0,
    },
    .periphClkEn = periphClkEn,
    .periphClkEnCount = sizeof(periphClkEn),
};

ohal_Clock clk = {
    .dev = {
        .name = "pllClk",
        .reg = {
            .base = 0x58000000,
            .size = 0x400,
        },
    },
    .ops = &g_stClockOps,
    .cfg = &clkCfg,
};

ohal_StGpio_Cfg gpioCfg[] = {
    { /* LED */
        .port = OHAL_STGPIO_PORT_B,
        .pin = 5,
        .mode = OHAL_STGPIO_MODE_OUT,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_LOW,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 0,
    },
    { /* LPUART1 TX */
        .port = OHAL_STGPIO_PORT_A,
        .pin = 2,
        .mode = OHAL_STGPIO_MODE_ALTFN,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_FAST,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 8,
    },
    { /* LPUART1 RX */
        .port = OHAL_STGPIO_PORT_A,
        .pin = 3,
        .mode = OHAL_STGPIO_MODE_ALTFN,
        .outType = OHAL_STGPIO_OUTTYPE_PUSHPULL,
        .speed = OHAL_STGPIO_SPEED_FAST,
        .pull = OHAL_STGPIO_PULL_UP,
        .altFn = 8,
    },
};

ohal_Gpio gpio = {
    .dev = {
        .name = "gpio",
        .reg = {
            .base = 0x48000000,
            .size = 0x2000,
        },
    },
    .ops = &g_stGpioOps,
    .pinCfg = &gpioCfg,
    .pinCount = sizeof(gpioCfg) / sizeof(ohal_StGpio_Cfg),
};

ohal_SysTick_Cfg sysTickCfg = {
    .cyclesPerTick = 64000000 / 1000,
    .clkSrc = OHAL_SYSTICK_CLKSRC_SYSCLK,
    .tickInt = OHAL_SYSTICK_TICKINT_ENABLED,
};

ohal_Timer sysTickTimer = {
    .dev = {
        .name = "SysTick Timer",
        .reg = {
            .base = 0xE000E010,
            .size = 0x400,
        },
    },
    .ops = &g_sysTickOps,
    .cfg = &sysTickCfg,
};

ohal_StUart_Cfg lpuart1Cfg = {
    .baud = 115200,
    .sysClk = &clk,
};

ohal_Uart lpuart1 = {
    .dev = {
        .name = "LPUART1",
        .reg = {
            .base = 0x40008000,
            .size = 0x400,
        },
    },
    .ops = &g_stUartOps,
    .cfg = &lpuart1Cfg,
};

volatile size_t g_tick = 0;
volatile uint8_t g_waiting = 0;
volatile uint8_t g_tickOverflow = 0;

void SysTick_Handler()
{
    size_t tickBefore = g_tick++;
    if (g_waiting) {
        if (tickBefore > g_tick)
            g_tickOverflow = 1;
    }
}

void WaitMs(size_t ms)
{
    size_t startCount = g_tick;
    g_waiting = 1;
    while (1) {
        size_t currentCount = g_tick;
        if (g_tickOverflow) {
            if ((SIZE_MAX - startCount) + currentCount > ms) {
                break;
            }
        } else if (currentCount - startCount > ms) {
            break;
        }
    }

    g_waiting = 0;
    g_tickOverflow = 0;
}

void main(void)
{
    ohal_Error err;
    ohal_Reg flash =
    {
        .base = 0x58004000,
        .size = 0x400
    };
    u32 acrMask = OHAL_MASK_RANGE(2, 0);

    err = ohal_Reg_Update(&flash, 0, acrMask, ohal_SetBits(acrMask, 3));
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Reg_Set");
        goto loop;
    }

    err = ohal_Clock_Init(&clk); 
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Init");
        goto loop;
    }

    err = ohal_Clock_Enable(&clk);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Enable");
        goto loop;
    }

    err = ohal_Gpio_Init(&gpio);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Gpio_Init");
        goto loop;
    }

    err = ohal_Uart_Init(&lpuart1);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Uart_Init");
        goto loop;
    }

    err = ohal_Timer_Init(&sysTickTimer);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Timer_Init");
        goto loop;
    }

    err = ohal_Timer_Start(&sysTickTimer);
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Timer_Start");
        goto loop;
    }

    while (1) {
        u8 input[8];
        err = ohal_Uart_Send(&lpuart1, (u8 *)"Enter Stuff:\r\n", 14);
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Uart_Send");
            goto loop;
        }

        err = ohal_Uart_Recv(&lpuart1, input, sizeof(input));
        if (err) {
            goto loop;
        }

        err = ohal_Uart_Send(&lpuart1, input, sizeof(input));
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Uart_Send");
            goto loop;
        }
        err = ohal_Gpio_Set(&gpio, 0, 1);
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Gpio_Set");
            goto loop;
        }

        WaitMs(1000);

        err = ohal_Gpio_Set(&gpio, 0, 0);
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Gpio_Set");
            goto loop;
        }

        WaitMs(1000);
    }

loop:
    while (1);

}
