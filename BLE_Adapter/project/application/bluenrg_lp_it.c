#include "rf_driver_hal.h"
#include "crash_handler.h"
#include "hal_miscutil.h"

#include "bluenrg_lp_it.h"
#include "uart.h"


/******************************************************************************/
/* Peripheral Interrupt Handlers                                              */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file.                                          */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 and channel2 global interrupt.
  */
void DMA_IRQHandler(void)
{
  if( __HAL_DMA_GET_FLAG(DMA1, DMA_FLAG_TC1 ) ){
    HAL_DMA_IRQHandler(&hdma_usart1_tx);
  }
  
  if( __HAL_DMA_GET_FLAG(DMA1, DMA_FLAG_TC2 ) ){
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  }
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart1);
}


NOSTACK_FUNCTION(NORETURN_FUNCTION(void HardFault_IRQHandler(void)))
{
  //HAL_CrashHandler(__get_MSP(), HARD_FAULT_SIGNATURE);  
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}
