#ifndef OHAL_UART_H
#define OHAL_UART_H

#include <openHAL/device.h>
#include <openHAL/error.h>
#include <stddef.h>

typedef struct ohal_Uart ohal_Uart;

typedef struct {
    ohal_Error (*Init)(ohal_Uart *uartDev);
    ohal_Error (*Deinit)(ohal_Uart *uartDev);
    ohal_Error (*Send)(ohal_Uart *uartDev, u8 *data, size_t dataSz);
    ohal_Error (*Recv)(ohal_Uart *uartDev, u8 *data, size_t dataSz);
    ohal_Error (*Cmd)(ohal_Uart *uartDev, size_t cmd, void *args);
} ohal_UartOps;

struct ohal_Uart {
    ohal_Device dev;
    ohal_UartOps *ops;
    void *cfg;
};

/**
 * @brief Initializes a UART device and its driver.
 *
 * @param uartDev Pointer to the UART instance to initialize.
 *
 * @retval OHAL_SUCCESS Driver-specific init completed.
 * @retval OHAL_EINVAL  Null pointer or driver rejected configuration.
 */
ohal_Error ohal_Uart_Init(ohal_Uart *uartDev);

/**
 * @brief Deinitializes a UART device and releases resources.
 *
 * @param uartDev Pointer to the UART instance to deinitialize.
 *
 * @retval OHAL_SUCCESS Driver-specific deinit completed.
 * @retval OHAL_EINVAL  Null pointer or driver refused to deinit.
 */
ohal_Error ohal_Uart_Deinit(ohal_Uart *uartDev);

/**
 * @brief Sends a buffer over the UART.
 *
 * @param uartDev Pointer to the UART instance.
 * @param data    Buffer to transmit.
 * @param dataSz  Number of bytes to send.
 *
 * @retval OHAL_SUCCESS Buffer was queued or transmitted.
 * @retval OHAL_EINVAL  Null pointer or driver failed to send.
 */
ohal_Error ohal_Uart_Send(ohal_Uart *uartDev, u8 *data, size_t dataSz);

/**
 * @brief Receives data from the UART into a buffer.
 *
 * @param uartDev Pointer to the UART instance.
 * @param data    Destination buffer.
 * @param dataSz  Maximum number of bytes to read.
 *
 * @retval OHAL_SUCCESS Buffer was filled or receive started.
 * @retval OHAL_EINVAL  Null pointer or driver failed to receive.
 */
ohal_Error ohal_Uart_Recv(ohal_Uart *uartDev, u8 *data, size_t dataSz);

/**
 * @brief Issues a driver-specific command to a UART device.
 *
 * @param uartDev Pointer to the UART instance.
 * @param cmd     Numeric command selector defined by the driver.
 * @param args    Optional command arguments, interpreted per cmd.
 *
 * @retval OHAL_SUCCESS Command accepted and executed.
 * @retval OHAL_EINVAL  Null pointer, unknown command, or bad args.
 */
ohal_Error ohal_Uart_Cmd(ohal_Uart *uartDev, size_t cmd, void *args);

#endif /* OHAL_UART_H */
