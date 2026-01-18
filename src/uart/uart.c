#include <openHAL/uart/uart.h>
#include <openHAL/error.h>
#include <openHAL/print.h>

inline ohal_Error ohal_Uart_Init(ohal_Uart *uartDev)
{
    if (!uartDev || !uartDev->driver || !uartDev->driver->Init) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->driver->Init(uartDev);
}

inline ohal_Error ohal_Uart_Deinit(ohal_Uart *uartDev)
{
    if (!uartDev || !uartDev->driver || !uartDev->driver->Deinit) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->driver->Deinit(uartDev);
}

inline ohal_Error ohal_Uart_Send(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    if (!uartDev || !uartDev->driver || !uartDev->driver->Send || !data) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->driver->Send(uartDev, data, dataSz);
}

inline ohal_Error ohal_Uart_Recv(ohal_Uart *uartDev, u8 *data, size_t dataSz)
{
    if (!uartDev || !uartDev->driver || !uartDev->driver->Recv || !data) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->driver->Recv(uartDev, data, dataSz);
}

inline ohal_Error ohal_Uart_Cmd(ohal_Uart *uartDev, size_t cmd, void *args)
{
    if (!uartDev || !uartDev->driver || !uartDev->driver->Cmd) {
        ohal_PrintErr(OHAL_EINVAL, "Invalid argument");
        return OHAL_EINVAL;
    }

    return uartDev->driver->Cmd(uartDev, cmd, args);
}
