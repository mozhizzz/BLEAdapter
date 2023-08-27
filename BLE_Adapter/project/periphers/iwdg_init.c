#include "rf_driver_hal.h"
#include "rf_driver_hal_iwdg.h"

#include "iwdg_init.h"


extern IWDG_HandleTypeDef iwdg_handle;


void IWDG_Init(void)
{
  __HAL_RCC_WDG_CLK_ENABLE();
  
  __HAL_RCC_WDG_FORCE_RESET();
  __HAL_RCC_WDG_RELEASE_RESET();
  
  while(__HAL_RCC_GET_IT(RCC_IT_WDGRSTRELRDY) == 0)
  {}
  
  iwdg_handle.Instance = IWDG;
  iwdg_handle.Init.Prescaler = IWDG_PRESCALER;
  iwdg_handle.Init.Window = IWDG_WINDOW;
  iwdg_handle.Init.Reload = IWDG_RELOAD;
  if (HAL_IWDG_Init(&iwdg_handle) != HAL_OK)
  {}
}
