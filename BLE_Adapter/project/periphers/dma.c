#include "rf_driver_hal.h"

#include "dma.h"


extern void DMA_Init(void)
{
    /* DMA controller clock enable */
    __HAL_RCC_DMA_CLK_ENABLE();

    /* DMA interrupt init */
    HAL_NVIC_SetPriority(DMA_IRQn, 1);
    HAL_NVIC_EnableIRQ(DMA_IRQn);
}
