#ifndef _USART_IT_H
#define _USART_IT_H

void USART1_IRQHandler(void);
void DMA_IRQHandler(void);
void disable_usart_dma_tx_it(void);
void disable_usart_dma_rx_it(void);
void usart_receive_handle(void);

#endif
