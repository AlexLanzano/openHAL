#ifndef STM32WB55XX_NUCLEO_H
#define STM32WB55XX_NUCLEO_H

#include <openHAL/platform/st/stm32wb55xx.h>

enum {
    LED_PIN,
    LPUART1_TX_PIN,
    LPUART1_RX_PIN,
};

extern ohal_Clock rcc;
extern ohal_Gpio gpio;
extern ohal_Timer sysTickTimer;
extern ohal_Uart lpuart1;
extern ohal_Flash flash;

#endif /* STM32WB55XX_NUCLEO_H */
