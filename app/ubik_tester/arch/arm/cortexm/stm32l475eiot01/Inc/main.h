/**
  ******************************************************************************
  * @file    BSP/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Definition for DTTY_STM32_UART */

#if (UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER == 1)

#define DTTY_STM32_UART                         USART1
#define DTTY_STM32_UART_HANDLE                  huart1

#define DTTY_STM32_UART_CLK_ENABLE()            __HAL_RCC_USART1_CLK_ENABLE()
#define DTTY_STM32_UART_RX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define DTTY_STM32_UART_TX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define DTTY_STM32_UART_FORCE_RESET()           __HAL_RCC_USART1_FORCE_RESET()
#define DTTY_STM32_UART_RELEASE_RESET()         __HAL_RCC_USART1_RELEASE_RESET()

#define DTTY_STM32_UART_TX_Pin                  GPIO_PIN_6
#define DTTY_STM32_UART_TX_GPIO_Port            GPIOB
#define DTTY_STM32_UART_TX_AF                   GPIO_AF7_USART1
#define DTTY_STM32_UART_RX_Pin                  GPIO_PIN_7
#define DTTY_STM32_UART_RX_GPIO_Port            GPIOB
#define DTTY_STM32_UART_RX_AF                   GPIO_AF7_USART1

#define DTTY_STM32_UART_IRQn                    USART1_IRQn
#define DTTY_STM32_UART_IRQHandler              USART1_IRQHandler

#else

#error "Unsupported UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER"

#endif

extern UART_HandleTypeDef DTTY_STM32_UART_HANDLE;

void dtty_stm32_uart_rx_callback(void);
void dtty_stm32_uart_tx_callback(void);
void dtty_stm32_uart_err_callback(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
