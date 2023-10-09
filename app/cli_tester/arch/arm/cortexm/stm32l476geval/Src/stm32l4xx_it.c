#include <ubinos.h>

#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL)

#include "main.h"
#include "stm32l4xx_it.h"

#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)

/**
 * @brief  This function handles DTTY_STM32_UART interrupt request.
 * @param  None
 * @retval None
 */
void DTTY_STM32_UART_IRQHandler(void)
{
    HAL_UART_IRQHandler(&DTTY_STM32_UART_HANDLE);
}

#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */

#if (STM32CUBEL4__DTTY_STM32_USBD_ENABLE == 1)

/**
  * @brief  This function handles USB-On-The-Go FS global interrupt request.
  * @param  None
  * @retval None
  */
void OTG_FS_IRQHandler(void)
{
    HAL_PCD_IRQHandler(&DTTY_STM32_PCD_HANDLE);
}

#endif /* (STM32CUBEL4__DTTY_STM32_USBD_ENABLE == 1) */

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */

#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) */

