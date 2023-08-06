#include <string.h>

#include "rf_driver_hal.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_gap.h"
#include "FreeRTOS.h"
#include "task.h"

#include "ble_init.h"
#include "ble_it.h"
#include "ble_tick.h"
#include "ble_config.h"
#include "ble_state.h"
#include "usart_init.h"
#include "usart_it.h"
#include "flash.h"
#include "at.h"
#include "iwdg_init.h"

// usart params
UART_HandleTypeDef usart_handle;
DMA_HandleTypeDef dma_usart_tx_handle;
DMA_HandleTypeDef dma_usart_rx_handle;
uint8_t usart_RxBuffer[USART_RXBUFFERSIZE];
uint16_t usart_receiced_frame_size;
uint8_t frame[MAX_FRAME_SIZE];

// usart sign
volatile uint8_t is_usart_received;
volatile uint8_t is_usart1_init_frame_received;

// ble params
volatile uint16_t connection_handle = 0;
uint8_t ble_role;
volatile uint16_t tran_tran_handle = 0;
uint8_t Connected_Address[6];
uint8_t Connected_Address_Type;
uint8_t advertising_filter;
uint16_t advertisiting_handle;
volatile int app_flags = SET_CONNECTABLE;
uint8_t ble_name[BLE_NAME_SIZE] = {PERIPHERAL_DEVICE_NAME};
uint8_t mac_address[6] = {PERIPHERAL_PUBLIC_ADDRESS};
uint8_t ble_tx_power = 25;
uint8_t adv_data[BlE_ADVERTISE_CONTENT_SIZE] = {
    2, AD_TYPE_FLAGS, FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE|FLAG_BIT_BR_EDR_NOT_SUPPORTED,
		13, 0x09, PERIPHERAL_DEVICE_NAME};
Advertising_Set_Parameters_t Advertising_Set_Parameters[1];
VTIMER_HandleType peripheralTimerHandle;
uint16_t update_rate = 2000; 
uint8_t Timer_expired = FALSE;
uint8_t filter_name_keyword[FILTER_NAME_KEYWORD_SIZE];
uint8_t filter_name_keyword_size;
uint8_t filter_name_keyword_enable;
uint8_t filter_phy_address_keyword[FILTER_PHY_ADDRESS_KEYWORD_SIZE];
uint8_t filter_phy_address_keyword_size;
uint8_t filter_phy_address_keyword_enable;
uint32_t filter_signal_strength;
uint8_t filter_signal_strength_size;
uint8_t filter_signal_strength_enable;
Device_InfoDef devices[MAX_DEVICE_SIZE];
Scan_InfoDef scans[MAX_SCAN_SIZE];
uint32_t current_sn;
uint32_t connect_passkey = 123456;
UUID_t pincode_verify_char_uuid = {.UUID_128 = {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0xe3,0xff,0x00,0x00}};
uint16_t read_char_by_uuid_handle;
uint8_t clt_error_resp_error_code;

// ble sign
volatile uint8_t is_advertising_report_received;
uint16_t at_command_handle;
uint8_t password_pair_enable = 0;
uint8_t is_device_connected = 0;
uint8_t is_scan_finished = 0;
uint8_t is_tran_tran_char_handle_get = 0;
uint8_t is_pincode_verify_char_handle_get = 0;
uint8_t is_pairing_completed = 0;
uint8_t is_tx_notification_enable = 0;
uint8_t is_connection_complete_event_generated = 0;
uint8_t is_disconnection_complete_event_generated = 0;
uint8_t is_pairing_complete_event_generated = 0;
uint8_t is_notification_event_generated = 0;
uint8_t is_disc_read_char_by_uuid_resp_event_generated = 0;
uint8_t is_clt_error_resp_event_generated = 0;

// AT
uint8_t mode;
uint8_t ret_ok[10] = "OK{CR}{LF}";
uint8_t suf[18] = "{CR}{LF}OK{CR}{LF}";
uint8_t suf_half[8] = "{CR}{LF}";

// flash
uint8_t flash_tem[TOTAL_SIZE];

// iwdg
IWDG_HandleTypeDef iwdg_handle;


int main(void)
{
	tBleStatus ret;
	
	if (SystemInit(SYSCLK_64M, BLE_SYSCLK_32M) != SUCCESS) 
	{
		while(1);
	}
	
	HAL_Init();
	
	read_flash(ADAPTER_MODE_OFFSET, flash_tem, TOTAL_SIZE);
	
	MX_GPIOA_Init();
	USART1_init();
//	IWDG_Init();
	BLE_Init();
	
	HAL_UART_Receive_DMA(&usart_handle, (uint8_t *)usart_RxBuffer, USART_RXBUFFERSIZE);
	disable_usart_dma_rx_it();

//	if (flash_tem[ADAPTER_MASTER_ROLE_ENABLE_OFFSET] == 1)
//	{
//		if (flash_tem[DEFAULT_ADDRESS_ENABLE_OFFSET] == 1)
//		{
//			memcpy((uint8_t*)&address[0], (uint8_t*)&flash_tem[DEFAULT_ADDRESS_OFFSET], DEFAULT_ADDRESS_SIZE);
//			address_type = flash_tem[DEFAULT_ADDRESS_TYPE_OFFSET];
//			memcpy((uint8_t*)&connect_passkey, (uint8_t*)&flash_tem[DEFAULT_ADDRESS_PINCODE_OFFSET], 4);
//		}
//		else
//		{
//			memcpy((uint8_t*)&address[0], (uint8_t*)&flash_tem[LAST_TIME_ADDRESS_OFFSET], DEFAULT_ADDRESS_SIZE);
//			address_type = flash_tem[LAST_TIME_ADDRESS_TYPE_OFFSET];
//			memcpy((uint8_t*)&connect_passkey, (uint8_t*)&flash_tem[LAST_TIME_ADDRESS_PINCODE_OFFSET], 4);
//		}
//		
//		ret = aci_gap_create_connection(LE_1M_PHY_BIT, 0x00, address);
//	}
//	
//	ret = aci_gap_create_connection(LE_1M_PHY_BIT, 0x00, address);
	
	while(1)
	{
		ModulesTick();
		APP_Tick();
		
		if (is_scan_finished == 1)
		{
			scan_handle();
		}
		
		if (is_connection_complete_event_generated == 1)
		{
			connection_complete_event_handle();
		}
		
		if (is_clt_error_resp_event_generated == 1)
		{
			clt_error_resp_event_handle();
		}
		
		if (is_pairing_complete_event_generated == 1)
		{
			pairing_complete_event_handle();
		}
		
		if (is_notification_event_generated == 1)
		{
			notification_event_handle();
		}
		
		if (is_disconnection_complete_event_generated == 1)
		{
			disconnection_complete_event_handle();
		}
		
		if (is_usart_received == 1)
		{
			usart_receive_handle();
		}			
		
		if (is_disc_read_char_by_uuid_resp_event_generated == 1)
		{
			disc_read_char_by_uuid_resp_event_handle();
		}

//		__HAL_IWDG_RELOAD_COUNTER(&iwdg_handle);
	}
}

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName )
{
}

void vApplicationIdleHook( void )
{}
	
void vApplicationMallocFailedHook(void)
{}
	
void vApplicationTickHook(void)
{}
