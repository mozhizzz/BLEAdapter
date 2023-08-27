#include <string.h>

#include "rf_driver_hal.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_gap.h"
#include "SEGGER_RTT.h"

#include "log.h"
#include "uart.h"
#include "dma.h"
#include "ble.h"
#include "tasks.h"


int main(void)
{
	if (SystemInit(SYSCLK_64M, BLE_SYSCLK_32M) != SUCCESS) 
	{
		while(1);
	}
	
	HAL_Init();
	
	SEGGER_RTT_Init();
	printLog("---------------------------Applicatiopn Start-------------------------------\n");  // ???
	
	DMA_Init();
	// USART1_Init();

	System_Task_Init();
	
	while(1);
}


extern void Error_Handler(void)
{
	printLog("Error Status!");
	while (1);
}
