#ifndef _UART_H
#define _UART_H


#define USART1_TX_PIN       GPIO_PIN_9
#define USART1_TX_PORT      GPIOA
#define USART1_RX_PIN       GPIO_PIN_8
#define USART1_RX_PORT      GPIOA


extern UART_HandleTypeDef huart1;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

extern void USART1_Init(void);

#endif
