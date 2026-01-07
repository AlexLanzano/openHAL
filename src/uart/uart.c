#include <openHAL/uart/uart.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Uart_Init(ohal_Uart *uartDev)
{
    if (!uartDev || !uartDev->ops || !uartDev->ops->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->ops->Init(uartDev);
}

inline ohal_Error ohal_Uart_Deinit(ohal_Uart *uartDev)
{
    if (!uartDev || !uartDev->ops || !uartDev->ops->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->ops->Deinit(uartDev);
}

inline ohal_Error ohal_Uart_Send(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    if (!uartDev || !uartDev->ops || !uartDev->ops->Send || !data) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->ops->Send(uartDev, data, dataSz);
}

inline ohal_Error ohal_Uart_Recv(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    if (!uartDev || !uartDev->ops || !uartDev->ops->Recv || !data) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->ops->Recv(uartDev, data, dataSz);
}

inline ohal_Error ohal_Uart_Cmd(ohal_Uart *uartDev, size_t cmd, void *args)
{
    if (!uartDev || !uartDev->ops || !uartDev->ops->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->ops->Cmd(uartDev, cmd, args);
}
