/*
 * Copyright (c) 2021 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL)

#include <ubinos/bsp/arch.h>

#include "main.h"

#include <stdio.h>

#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)

UART_HandleTypeDef DTTY_STM32_UART_HANDLE;

/**
 * @brief  Tx Transfer completed callback
 * @param  huart: UART handle.
 * @note   This example shows a simple way to report end of DMA Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)
#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_tx_callback();
    }
#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */
#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */
}

/**
 * @brief  Rx Transfer completed callback
 * @param  huart: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)
#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_rx_callback();
    }
#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */
#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */
}

/**
 * @brief  UART error callbacks
 * @param  huart: UART handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)
#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_err_callback();
    }
#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */
#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */
}

#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */

#if (STM32CUBEL4__DTTY_STM32_USBD_ENABLE == 1)

USBD_HandleTypeDef DTTY_STM32_USBD_HANDLE;
PCD_HandleTypeDef DTTY_STM32_PCD_HANDLE;

#endif /* (STM32CUBEL4__DTTY_STM32_USBD_ENABLE == 1) */

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) */

