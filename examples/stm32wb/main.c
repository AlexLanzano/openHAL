#include <openHAL/openHAL.h>
#include <openHAL/bitops.h>
#include "stm32wb55xx_nucleo.h"

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
    ohal_StFlash_SetLatencyArgs args = {
        .latency = OHAL_ST_FLASH_LATENCY_3
    };

    err = ohal_Flash_Cmd(&flash, OHAL_ST_FLASH_CMD_SET_LATENCY, &args);
    if (err) {
        goto loop;
    }

    err = ohal_Clock_Init(&rcc); 
    if (err) {
        ohal_PrintErr(err, "Failed to ohal_Clock_Init");
        goto loop;
    }

    err = ohal_Clock_Enable(&rcc);
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
        err = ohal_Gpio_Set(&gpio, LED_PIN, 1);
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Gpio_Set");
            goto loop;
        }

        WaitMs(1000);

        err = ohal_Gpio_Set(&gpio, LED_PIN, 0);
        if (err) {
            ohal_PrintErr(err, "Failed to ohal_Gpio_Set");
            goto loop;
        }

        WaitMs(1000);
    }

loop:
    while (1);

}
