#include <string.h>

#include "rf_driver_hal.h"

#include "usart_init.h"
#include "flash.h"


extern UART_HandleTypeDef usart_handle;
extern DMA_HandleTypeDef dma_usart_tx_handle;
extern DMA_HandleTypeDef dma_usart_rx_handle;

extern uint32_t baud_rate;
extern uint32_t data_len;
extern uint32_t stop_bits;
extern uint32_t parity;

extern uint8_t flash_tem[TOTAL_SIZE];

void MX_GPIOA_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
}


void USART1_init(void)
{
	uint32_t baud_rate;
	uint32_t data_len;
	uint32_t stop_bits;
	uint32_t parity;
	
	memcpy((uint8_t*)&baud_rate, (uint8_t*)&flash_tem[USART_BAUD_RATE_OFFSET], USART_BAUD_RATE_SIZE);
	memcpy((uint8_t*)&data_len, (uint8_t*)&flash_tem[USART_DATA_LEN_OFFSET], USART_DATA_LEN_SIZE);
	memcpy((uint8_t*)&stop_bits, (uint8_t*)&flash_tem[USART_STOP_BITS_LEN_OFFSET], USART_STOP_BITS_LEN_SIZE);
	memcpy((uint8_t*)&parity, (uint8_t*)&flash_tem[USART_PARITY_OFFSET], USART_PARITY_SIZE);
	
  GPIO_InitTypeDef GPIO_InitStruct;
	
	__HAL_RCC_DMA_CLK_ENABLE();
	
  usart_handle.Instance = USART1;
  usart_handle.Init.BaudRate = baud_rate;
  usart_handle.Init.WordLength = data_len;
  usart_handle.Init.StopBits = stop_bits;
  usart_handle.Init.Parity = parity;
  usart_handle.Init.Mode = UART_MODE_TX_RX;
  usart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  usart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
  usart_handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  usart_handle.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  usart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

  if (usart_handle.Init.HwFlowCtl != UART_HWCONTROL_NONE)
  {
    assert_param(IS_UART_HWFLOW_INSTANCE(usart_handle->Instance));
  }
  else
  {
    assert_param((IS_UART_INSTANCE(usart_handle->Instance)) || (IS_LPUART_INSTANCE(usart_handle->Instance)));
  }

  usart_handle.Lock = HAL_UNLOCKED;

	__HAL_RCC_USART_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	dma_usart_rx_handle.Instance = DMA1_Channel2;
	dma_usart_rx_handle.Init.Request = DMA_REQUEST_USART1_RX;
	dma_usart_rx_handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dma_usart_rx_handle.Init.PeriphInc = DMA_PINC_DISABLE;
	dma_usart_rx_handle.Init.MemInc = DMA_MINC_ENABLE;
	dma_usart_rx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dma_usart_rx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dma_usart_rx_handle.Init.Mode = DMA_NORMAL;
	dma_usart_rx_handle.Init.Priority = DMA_PRIORITY_HIGH;
	if (HAL_DMA_Init(&dma_usart_rx_handle) != HAL_OK)
	{}

	__HAL_LINKDMA(&usart_handle, hdmarx, dma_usart_rx_handle);
	
	dma_usart_tx_handle.Instance = DMA1_Channel1;
	dma_usart_tx_handle.Init.Request = DMA_REQUEST_USART1_TX;
	dma_usart_tx_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dma_usart_tx_handle.Init.PeriphInc = DMA_PINC_DISABLE;
	dma_usart_tx_handle.Init.MemInc = DMA_MINC_ENABLE;
	dma_usart_tx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dma_usart_tx_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dma_usart_tx_handle.Init.Mode = DMA_NORMAL;
	dma_usart_tx_handle.Init.Priority = DMA_PRIORITY_LOW;
	if (HAL_DMA_Init(&dma_usart_tx_handle) != HAL_OK)
	{}
		
  __HAL_LINKDMA(&usart_handle, hdmatx, dma_usart_tx_handle);
		
	HAL_NVIC_SetPriority(DMA_IRQn, 2);
  HAL_NVIC_EnableIRQ(DMA_IRQn);

	HAL_NVIC_SetPriority(USART1_IRQn, 2);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

  usart_handle.gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(&usart_handle);

  if (UART_SetConfig(&usart_handle) != HAL_OK)
	{}

  if (usart_handle.AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT)
  {
    UART_AdvFeatureConfig(&usart_handle);
  }

  CLEAR_BIT(usart_handle.Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(usart_handle.Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

  __HAL_UART_ENABLE(&usart_handle);
	
	__HAL_UART_ENABLE_IT(&usart_handle, UART_IT_IDLE);
	
	if (UART_CheckIdleState(&usart_handle) != HAL_OK)
	{}
}



