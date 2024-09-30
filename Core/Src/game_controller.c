#include "game_controller.h"
#include "logger.h"

/**
  * @brief  Function implementing the Game Controller entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void gameController(void)
{
  LOG_INFO("gameController entry");

  /* Infinite loop */
  while (1)
  {
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(100));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(50));
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    tx_thread_sleep(UX_MS_TO_TICK_NON_ZERO(800));            
  }
}