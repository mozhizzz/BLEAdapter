#include <string.h>

#include "rf_driver_hal.h"
#include "bluenrg_lp_api.h"
#include "steval_idb011V1_config.h"
#include "rf_driver_hal_gpio.h"

#include "usart_init.h"
#include "usart_it.h"
#include "at.h"


// usart 
extern UART_HandleTypeDef usart_handle;
extern DMA_HandleTypeDef dma_usart_tx_handle;
extern DMA_HandleTypeDef dma_usart_rx_handle;
extern uint8_t usart_RxBuffer[USART_RXBUFFERSIZE];
extern volatile uint8_t is_usart_received;
extern uint16_t usart_receiced_frame_size;
extern uint8_t is_usart1_init_frame_received;

// ble
extern uint8_t is_device_connected;
extern volatile uint16_t connection_handle;
extern volatile uint16_t tran_tran_handle;

// AT
extern uint8_t mode;


void disable_usart_dma_tx_it(void)
{
	__HAL_DMA_DISABLE_IT(&dma_usart_tx_handle, DMA_IT_HT);
}


void disable_usart_dma_rx_it(void)
{
	__HAL_DMA_DISABLE_IT(&dma_usart_rx_handle, DMA_IT_HT);
}


void usart_receive_handle(void)
{
	if (memcmp(usart_RxBuffer, ENTER_AT_MODE, sizeof(ENTER_AT_MODE)-1) == 0)
	{
		enter_AT_command_mode();
	}
	else if (memcmp(usart_RxBuffer, EXIT_AT_MODE, sizeof(EXIT_AT_MODE)-1) == 0)
	{
		exit_AT_command_mode();
	}
	else if (memcmp(usart_RxBuffer, AT_RESET, sizeof(AT_RESET)-1) == 0)
	{
		soft_reset();
	}
	else if (memcmp(usart_RxBuffer, COM_INFO_QUERY, sizeof(COM_INFO_QUERY)-1) == 0)
	{
		serial_port_info_query();
	}
	else if (memcmp(usart_RxBuffer, COM_INFO_CONFIG, sizeof(COM_INFO_CONFIG)-1) == 0)
	{
		serial_port_info_set();
	}
	else if (memcmp(usart_RxBuffer, LOCAL_BLE_NAME_QUERY, sizeof(LOCAL_BLE_NAME_QUERY)-1) == 0)
	{
		local_ble_name_query();
	}
	else if (memcmp(usart_RxBuffer, LOCAL_BLE_NAME_CONFIG, sizeof(LOCAL_BLE_NAME_CONFIG)-1) == 0)
	{
		local_ble_name_set();
	}
	else if (memcmp(usart_RxBuffer, LOCAL_MAC_QUERY, sizeof(LOCAL_MAC_QUERY)-1) == 0)
	{
		local_mac_address_query();
	}
	else if (memcmp(usart_RxBuffer, TX_POWER_QUERY, sizeof(TX_POWER_QUERY)-1) == 0)
	{
		transimit_power_query();
	}
	else if (memcmp(usart_RxBuffer, TX_POWER_CONFIG, sizeof(TX_POWER_CONFIG)-1) == 0)
	{
		transimit_power_set();
	}
	else if (memcmp(usart_RxBuffer, PASSWORD_ENABLE_QUERY, sizeof(PASSWORD_ENABLE_QUERY)-1) == 0)
	{
		password_pair_enable_query();
	}
	else if (memcmp(usart_RxBuffer, PASSWORD_ENABLE_CONFIG, sizeof(PASSWORD_ENABLE_CONFIG)-1) == 0)
	{
		password_pair_enable_set();
	}
	else if (memcmp(usart_RxBuffer, START_SCAN_CONFIG, sizeof(START_SCAN_CONFIG)-1) == 0)
	{
		start_search_device();
	}
	else if (memcmp(usart_RxBuffer, SN_CONNECT_CONFIG, sizeof(SN_CONNECT_CONFIG)-1) == 0)
	{
		direct_connect_by_sn();
	}
	else if (memcmp(usart_RxBuffer, MAC_CONNECT_CONFIG, sizeof(MAC_CONNECT_CONFIG)-1) == 0)
	{
		direct_connect_by_mac_address();
	}
	else if (memcmp(usart_RxBuffer, DEFAULT_DEVICE_QUERY, sizeof(DEFAULT_DEVICE_QUERY)-1) == 0)
	{
		default_connect_device_params_query();
	}
	else if (memcmp(usart_RxBuffer, DEFAULT_DEVICE_CONFIG, sizeof(DEFAULT_DEVICE_QUERY)-1) == 0)
	{
		default_connect_device_params_set();
	}
	else if (memcmp(usart_RxBuffer, ROLE_QUERY, sizeof(ROLE_QUERY)-1) == 0)
	{
		role_control_query();
	}
	else if (memcmp(usart_RxBuffer, ROLE_CONFIG, sizeof(ROLE_CONFIG)-1) == 0)
	{
		role_control_set();
	}
	else if (memcmp(usart_RxBuffer, TRAN_TRAN_QUERY, sizeof(TRAN_TRAN_QUERY)-1) == 0)
	{
		transparent_transimission_service_info_query();
	}
	else if (memcmp(usart_RxBuffer, TRAN_TRAN_CONFIG, sizeof(TRAN_TRAN_CONFIG)-1) == 0)
	{
		transparent_transimission_service_info_set();
	}
	else if (memcmp(usart_RxBuffer, MANUFACTURER_QUERY, sizeof(MANUFACTURER_QUERY)-1) == 0)
	{
		manufacturer_info_query();
	}
	else if (memcmp(usart_RxBuffer, MANUFACTURER_CONFIG, sizeof(MANUFACTURER_CONFIG)-1) == 0)
	{
		manufacturer_info_set();
	}
	else if (memcmp(usart_RxBuffer, ADV_INTERVAL_QUERY, sizeof(ADV_INTERVAL_QUERY)-1) == 0)
	{
		broadcast_interval_query();
	}
	else if (memcmp(usart_RxBuffer, ADV_INTERVAL_CONFIG, sizeof(ADV_INTERVAL_CONFIG)-1) == 0)
	{
		broadcast_interval_set();
	}
	else if (memcmp(usart_RxBuffer, SCAN_INTERVAL_QUERY, sizeof(SCAN_INTERVAL_QUERY)-1) == 0)
	{
		scan_interval_query();
	}
	else if (memcmp(usart_RxBuffer, SCAN_INTERVAL_CONFIG, sizeof(SCAN_INTERVAL_CONFIG)-1) == 0)
	{
		scan_interval_set();
	}
	else if (memcmp(usart_RxBuffer, CONNECT_INTERVAL_QUERY, sizeof(CONNECT_INTERVAL_QUERY)-1) == 0)
	{
		connect_interval_query();
	}
	else if (memcmp(usart_RxBuffer, CONNECT_INTERVAL_CONFIG, sizeof(CONNECT_INTERVAL_CONFIG)-1) == 0)
	{
		connect_interval_set();
	}
	else if (memcmp(usart_RxBuffer, HELLO_QUERY, sizeof(HELLO_QUERY)-1) == 0)
	{
		greetings_query();
	}
	else if (memcmp(usart_RxBuffer, HELLO_CONFIG, sizeof(HELLO_CONFIG)-1) == 0)
	{
		greetings_set();
	}
	else if (memcmp(usart_RxBuffer, DEVICE_FILTER_QUERY, sizeof(DEVICE_FILTER_QUERY)-1) == 0)
	{
		device_filter_info_query();
	}
	else if (memcmp(usart_RxBuffer, DEVICE_FILTER_CONFIG, sizeof(DEVICE_FILTER_CONFIG)-1) == 0)
	{
		device_filter_info_set();
	}
	else
	{
		if (is_device_connected == 1)
		{
			aci_gatt_clt_write(connection_handle, tran_tran_handle, usart_receiced_frame_size, usart_RxBuffer);
		}
	}
	
	memset(usart_RxBuffer, 0 , USART_RXBUFFERSIZE);
	HAL_UART_Receive_DMA(&usart_handle, (uint8_t *)usart_RxBuffer, USART_RXBUFFERSIZE);
	disable_usart_dma_rx_it();
	is_usart_received = 0;
}


void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&usart_handle);
	
	if(__HAL_UART_GET_FLAG(&usart_handle, UART_FLAG_IDLE) != RESET && is_usart1_init_frame_received == 1) 
	{
		__HAL_UART_CLEAR_IDLEFLAG(&usart_handle);
		HAL_UART_DMAStop(&usart_handle); 
		usart_receiced_frame_size = USART_RXBUFFERSIZE - __HAL_DMA_GET_COUNTER(&dma_usart_rx_handle);
		
		is_usart_received = 1;
	}
	else
	{
		is_usart1_init_frame_received = 1;
		__HAL_UART_CLEAR_IDLEFLAG(&usart_handle);
	}
}


void DMA_IRQHandler(void)
{
  if(__HAL_DMA_GET_FLAG(DMA1, DMA_FLAG_TC1 ))
	{
    HAL_DMA_IRQHandler(&dma_usart_tx_handle);
  }
  
  if(__HAL_DMA_GET_FLAG(DMA1, DMA_FLAG_TC2 ))
	{
		HAL_DMA_IRQHandler(&dma_usart_rx_handle);
  }
}
