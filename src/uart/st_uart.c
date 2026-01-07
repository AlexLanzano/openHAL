#include <openHAL/uart/st_uart.h>
#include <openHAL/uart/uart.h>
#include <openHAL/clock/clock.h>
#include <openHAL/error.h>
#include <openHAL/reg.h>
#include <openHAL/bitops.h>

#define STUART_CR1_REG 0x00
#define STUART_CR1_UE OHAL_MASK(0)
#define STUART_CR1_RE OHAL_MASK(2)
#define STUART_CR1_TE OHAL_MASK(3)

#define STUART_BRR_REG 0x0C
#define STUART_BRR_BRR_MASK OHAL_MASK_RANGE(19, 0)

#define STUART_ISR_REG 0x1C
#define STUART_ISR_RXFNE_MASK OHAL_MASK(5)
#define STUART_ISR_TC_MASK OHAL_MASK(6)

#define STUART_RDR_REG 0x24
#define STUART_RDR_RDR_MASK OHAL_MASK_RANGE(8, 0)

#define STUART_TDR_REG 0x28
#define STUART_TDR_TDR_MASK OHAL_MASK_RANGE(8, 0)

static ohal_Error StUart_Init(ohal_Uart *uartDev)
{
    ohal_Error err;
    ohal_StUart_Cfg *cfg;
    ohal_Reg *reg = &uartDev->dev.reg;
    size_t clockFreq;
    u32 brr;

    cfg = (ohal_StUart_Cfg *)uartDev->cfg;

    err = ohal_Clock_GetRate(cfg->sysClk, &clockFreq);
    if (err != OHAL_SUCCESS) {
        return err;
    }

    brr = (clockFreq / cfg->baud) * 256;
    

    err = ohal_Reg_Set(reg, STUART_BRR_REG,
                          ohal_SetBits(STUART_BRR_BRR_MASK, brr));
    if (err) {
        return err;
    }

    err = ohal_Reg_Update(reg, STUART_CR1_REG, STUART_CR1_UE | STUART_CR1_RE | STUART_CR1_TE,
                          ohal_SetBits(STUART_CR1_UE, 1) |
                          ohal_SetBits(STUART_CR1_RE, 1) |
                          ohal_SetBits(STUART_CR1_TE, 1));
    if (err) {
        return err;
    }
    
    return OHAL_SUCCESS;
}

static ohal_Error StUart_Deinit(ohal_Uart *uartDev)
{

    return OHAL_SUCCESS;
}

static ohal_Error StUart_Send(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    ohal_Error err;
    size_t txComplete = 0;
    ohal_Reg *reg = &uartDev->dev.reg;
    
    for (size_t i = 0; i < dataSz; ++i) {
        err = ohal_Reg_Set(reg, STUART_TDR_REG, 
                           ohal_SetBits(STUART_TDR_TDR_MASK, data[i]));
        if (err) {
            return err;
        }

        while (!txComplete) {
            err = ohal_Reg_Get(reg, STUART_ISR_REG, STUART_ISR_TC_MASK, &txComplete);
            if (err) {
                return err;
            }
        }

    }

    return OHAL_SUCCESS;
}

static ohal_Error StUart_Recv(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    ohal_Error err;
    size_t dataReceived = 0;
    ohal_Reg *reg = &uartDev->dev.reg;
    size_t d;
    
    for (size_t i = 0; i < dataSz; ++i) {
        while (!dataReceived) {
            err = ohal_Reg_Get(reg, STUART_ISR_REG, STUART_ISR_RXFNE_MASK, &dataReceived);
            if (err) {
                return err;
            }
        }

        err = ohal_Reg_Get(reg, STUART_RDR_REG, 
                           STUART_RDR_RDR_MASK, &d);
        if (err) {
            return err;
        }

        data[i] = d;
    }

    return OHAL_SUCCESS;
}

static ohal_Error StUart_Cmd(ohal_Uart *uartDev, size_t cmd, void *args)
{

    return OHAL_SUCCESS;
}

ohal_UartOps g_stUartOps = {
    .Init = StUart_Init,
    .Deinit = StUart_Deinit,
    .Send = StUart_Send,
    .Recv = StUart_Recv,
    .Cmd = StUart_Cmd,
};
