#include "bluenrg_lp_stack.h"
#include "rf_driver_hal.h"
#include "rf_driver_hal_vtimer.h"
#include "hal_miscutil.h"
#include "bluenrg_lp_evb_com.h"

#include "ble_it.h"
#include "ble_init.h"
#include "ble_state.h"
#include "usart_init.h"
#include "flash.h"
#include "at.h"


// usart
extern UART_HandleTypeDef usart_handle;
extern uint8_t usart_RxBuffer[USART_RXBUFFERSIZE];
extern uint8_t frame[MAX_FRAME_SIZE];

// ble
extern volatile uint16_t connection_handle;
extern int app_flags;
extern uint8_t Connected_Address_Type;
extern uint8_t Connected_Address[6];
extern Device_InfoDef devices[MAX_DEVICE_SIZE];
extern uint32_t current_sn;
extern uint8_t suf_half[8];
extern uint8_t filter_name_keyword[FILTER_NAME_KEYWORD_SIZE];
extern uint8_t filter_name_keyword_size;
extern uint8_t filter_name_keyword_enable;
extern uint8_t filter_phy_address_keyword[FILTER_PHY_ADDRESS_KEYWORD_SIZE];
extern uint8_t filter_phy_address_keyword_size;
extern uint8_t filter_phy_address_keyword_enable;
extern uint32_t filter_signal_strength;
extern uint8_t filter_signal_strength_size;
extern uint8_t filter_signal_strength_enable;
extern volatile uint16_t tran_tran_handle;
extern Scan_InfoDef scans[MAX_SCAN_SIZE];
extern UUID_t tran_tran_char;
extern UUID_t tran_tran_service;
extern uint8_t password_pair_enable;
extern uint32_t connect_passkey;
extern uint8_t tran_tran_char_uuid_size;
extern uint8_t greetings[GREETINGS_SIZE];
extern uint8_t greetings_size;
extern uint16_t read_char_by_uuid_handle;
extern UUID_t pincode_verify_char_uuid;
extern uint8_t tran_tran_tx_char_uuid_size;
extern UUID_t tran_tran_tx_char_uuid;
extern uint8_t clt_error_resp_error_code;

extern uint8_t is_connection_complete_event_generated;
extern uint8_t is_disconnection_complete_event_generated;
extern uint8_t is_pairing_complete_event_generated;
extern uint8_t is_notification_event_generated;
extern uint8_t is_device_connected;
extern uint8_t is_scan_finished;
extern uint8_t is_pairing_completed;
extern uint8_t is_pincode_verify_char_handle_get;
extern uint8_t is_tran_tran_char_handle_get;
extern uint8_t is_tx_notification_enable;
extern uint8_t is_disc_read_char_by_uuid_resp_event_generated;
extern uint8_t is_clt_error_resp_event_generated;

extern uint8_t flash_tem[TOTAL_SIZE];


void get_tran_tran_char_handle_by_uuid(void)
{
	UUID_t tran_tran_tx_char_uuid;
	uint8_t tran_tran_tx_char_uuid_size;
	
	tran_tran_tx_char_uuid_size = flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_OFFSET];
	memcpy((uint8_t*)&tran_tran_tx_char_uuid.UUID_128[0], (uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_OFFSET], tran_tran_tx_char_uuid_size);
	
	if (tran_tran_tx_char_uuid_size == 2)
	{
		if (aci_gatt_clt_disc_char_by_uuid(connection_handle, 0x0001, 0xFFFF, 0x01, &tran_tran_tx_char_uuid) == 0)
		{}
	}
	else if (tran_tran_tx_char_uuid_size == 16)
	{
		if (aci_gatt_clt_disc_char_by_uuid(connection_handle, 0x0001, 0xFFFF, 0x02, &tran_tran_tx_char_uuid) == 0)
		{}
	}
}


NOSTACK_FUNCTION(NORETURN_FUNCTION(void NMI_IRQHandler(void)))
{
  HAL_CrashHandler(__get_MSP(), NMI_SIGNATURE);
  while (1)
  {}
}


NOSTACK_FUNCTION(NORETURN_FUNCTION(void HardFault_IRQHandler(void)))
{
  HAL_CrashHandler(__get_MSP(), HARD_FAULT_SIGNATURE);  
  while (1)
  {}
}


void BLE_WKUP_IRQHandler(void)
{
  HAL_VTIMER_WakeUpCallback();
}


void CPU_WKUP_IRQHandler(void) 
{
  HAL_VTIMER_TimeoutCallback();
}


void BLE_TX_RX_IRQHandler(void)
{
  uint32_t blue_status = BLUE->STATUSREG;
  uint32_t blue_interrupt = BLUE->INTERRUPT1REG;
  
  BLUE->INTERRUPT1REG = blue_interrupt;

  BLE_STACK_RadioHandler(blue_status|blue_interrupt);
  HAL_VTIMER_RadioTimerIsr();

  blue_interrupt = BLUE->INTERRUPT1REG;
}


void hci_hardware_error_event(uint8_t Hardware_Code)
{
  if (Hardware_Code <= 0x03)
  {
    NVIC_SystemReset();
  }
}


void aci_hal_fw_error_event(uint8_t FW_Error_Type,
                            uint8_t Data_Length,
                            uint8_t Data[])
{
  if (FW_Error_Type <= 0x03)
  {
    uint16_t connHandle;
    
    connHandle = LE_TO_HOST_16(Data);
    
    aci_gap_terminate(connHandle, BLE_ERROR_TERMINATED_REMOTE_USER); 
  }
}


void connection_complete_event_handle(void)
{
	is_pincode_verify_char_handle_get = 0;
	is_tran_tran_char_handle_get = 0;
	
	if (aci_gatt_clt_disc_char_by_uuid(connection_handle, 0x0001, 0xFFFF, 0x02, &pincode_verify_char_uuid) == 0)
	{}
	
	is_device_connected = 1;
	is_connection_complete_event_generated = 0;
}


void hci_le_connection_complete_event(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6], uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy)
{
	if(Status != BLE_STATUS_SUCCESS)
    return;
	
	APP_FLAG_SET(CONNECTED);
	APP_FLAG_CLEAR(SET_CONNECTABLE);
	
	connection_handle = Connection_Handle;
	
	is_connection_complete_event_generated = 1;
}


void hci_le_enhanced_connection_complete_event(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6], uint8_t Local_Resolvable_Private_Address[6], uint8_t Peer_Resolvable_Private_Address[6], uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy)
{
  hci_le_connection_complete_event(Status,
                                   Connection_Handle,
                                   Role,
                                   Peer_Address_Type,
                                   Peer_Address,
                                   Conn_Interval,
                                   Conn_Latency,
                                   Supervision_Timeout,
                                   Master_Clock_Accuracy);
}


void disconnection_complete_event_handle(void)
{
	char a[] = "disconnect";
	HAL_UART_Transmit(&usart_handle, (uint8_t*)&a, sizeof(a), 5);
	
	is_disconnection_complete_event_generated = 0;
}


void hci_disconnection_complete_event(uint8_t Status, uint16_t Connection_Handle, uint8_t Reason)
{
	APP_FLAG_CLEAR(CONNECTED);
  APP_FLAG_SET(SET_CONNECTABLE);

	is_device_connected = 0;
	
	is_disconnection_complete_event_generated = 1;
}


void aci_gatt_tx_pool_available_event(uint16_t Connection_Handle, uint16_t Available_Buffers)
{
  APP_FLAG_CLEAR(TX_BUFFER_FULL);
}


uint8_t judge_sub_string(uint8_t* string1, uint8_t string1_len, uint8_t* string2, uint8_t string2_len)
{
	if (string1_len < string2_len)
	{
		return 0;
	}
	else
	{
		for (int i=0; i<=string1_len-string2_len; i++)
		{
			if (memcmp(&string1[i], &string2[0], string2_len) == 0)
			{
				return 1;
			}
		}
		return 0;
	}
}


void scan_handle(void)
{
	uint8_t ret;
	uint8_t current_frame_size = 0;
	uint8_t is_name_repeat;
	uint8_t is_address_repeat;
	uint8_t device_name[32];
	uint8_t device_name_len;
	uint8_t address[6];
	uint8_t j;
	uint8_t is_device_has_name;
	uint8_t string_size = 0;
	int current_vaild_sn = 0;
	char string[10];
	
	for (int i=0; i<current_sn-1; i++)
	{
		j = 0;
		is_device_has_name = 0;
		is_name_repeat = 0;
		is_address_repeat = 0;
		while(j < scans[i].dev_info_len)
		{
			if (scans[i].dev_info[j+1] == 0x09)
			{
				is_device_has_name = 1;
				memcpy((uint8_t*)&device_name[0], (uint8_t*)&scans[i].dev_info[j+2], scans[i].dev_info[j]-1);
				device_name_len = scans[i].dev_info[j]-1;
				break;
			}
			else
			{
				j += scans[i].dev_info[j]+1;
			}
		}
		
		if (is_device_has_name == 0)
		{
			device_name[0] = 'N';
			device_name[1] = '/';
			device_name[2] = 'A';
			device_name_len = 3;
			for (int k=0; k<i; k++)
			{
				if (memcmp(scans[k].address, scans[i].address, 6) == 0)
				{
					is_address_repeat = 1;
				}
			}
		}
		else
		{
			for (int k=0; k<current_vaild_sn; k++)
			{
				if (memcmp(devices[k].address, scans[i].address, 6) == 0)
				{
					is_address_repeat = 1;
				}
//				if (device_name_len != devices[k].device_name_len)
//				{
//					continue;
//				}
//				
//				if (memcmp(device_name, devices[k].device_name, device_name_len) == 0)
//				{
//					is_name_repeat = 1;
//					break;
//				}
			}
		}
		
		if (is_name_repeat == 1 || is_address_repeat == 1)
		{
			continue;
		}
		
		if (filter_name_keyword_enable == 1)
		{
			ret = judge_sub_string(device_name, device_name_len, filter_name_keyword, filter_name_keyword_size);
			if (ret == 0)
			{
				continue;
			}
		}
		
		if (filter_phy_address_keyword_enable == 1)
		{
			ret = judge_sub_string((uint8_t*)&scans[i].address[0], 6, filter_phy_address_keyword, filter_phy_address_keyword_size);
			if (ret == 0)
			{
				continue;
			}
		}
		
		if (filter_signal_strength_enable == 1)
		{
			if (scans[i].RSSI < filter_signal_strength)
			{
				continue;
			}
		}
		
		memcpy((uint8_t*)&address[0], (uint8_t*)&scans[i].address[0], 6);
		
		memcpy((uint8_t*)&devices[current_vaild_sn].device_name[0], (uint8_t*)&device_name[0], device_name_len);
		devices[current_vaild_sn].device_name_len = device_name_len;
		memcpy((uint8_t*)&devices[current_vaild_sn].address[0], (uint8_t*)&address[0], 6);
		devices[current_vaild_sn].address_type = scans[i].address_type;
		devices[current_vaild_sn].serial_num = current_vaild_sn+1;
			
		Int2String(current_vaild_sn+1, string);
		string_size = get_string_size(string, 10);
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
		current_frame_size += string_size;
		memset(string, 0, 10);
		
		frame[current_frame_size] = ',';
		current_frame_size++;
		
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&device_name, device_name_len);
		current_frame_size += device_name_len;
		
		frame[current_frame_size] = ',';
		current_frame_size++;
		
		for (int k=0; k<6; k++)
		{
			HexToAsc((char *)&frame[current_frame_size], address[k]);
			current_frame_size += 2;
			if (k < 5)
			{
				frame[current_frame_size] = ':';
				current_frame_size++;
			}
		}
		
		frame[current_frame_size] = ',';
		current_frame_size++;
		
		Int2String((int)scans[i].RSSI, string);
		string_size = get_string_size(string, 10);
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string[0], string_size);
		current_frame_size += string_size;
		memset(string, 0, 10);
		
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf_half[0], 8);
		current_frame_size += 8;
		
		HAL_UART_Transmit(&usart_handle, frame, current_frame_size, 100);
		memcpy((uint8_t*)&devices[current_vaild_sn].device_name[0], (uint8_t*)&device_name[0], device_name_len);
		current_frame_size = 0;
		current_vaild_sn++;
	}
	
	is_scan_finished = 0;
}


void hci_le_extended_advertising_report_event(uint8_t Num_Reports, Extended_Advertising_Report_t Advertising_Report[])
{
	if (Advertising_Report[0].Event_Type == 0x1B)
	{
		if (current_sn < MAX_DEVICE_SIZE)
		{
			scans[current_sn].RSSI = Advertising_Report[0].RSSI;
			scans[current_sn].address_type = Advertising_Report[0].Address_Type;
			memcpy((uint8_t*)&scans[current_sn].address[0], (uint8_t*)&Advertising_Report[0].Address[0], 6);
			scans[current_sn].dev_info_len = Advertising_Report[0].Data_Length;
			memcpy((uint8_t*)&scans[current_sn].dev_info[0], (uint8_t*)&Advertising_Report[0].Data[0], Advertising_Report[0].Data_Length);
			current_sn++;
		}
		else
		{
			current_sn++;
			if (aci_gap_terminate_proc(0x01) != BLE_STATUS_SUCCESS) 
			{}
		}
	}
}


void aci_gap_proc_complete_event(uint8_t Procedure_Code, uint8_t Status, uint8_t Data_Length, uint8_t Data[])
{
	if (Procedure_Code == 0x01 && Status == 0)
	{
		is_scan_finished = 1;
	}
}


void disc_read_char_by_uuid_resp_event_handle(void)
{
	if (is_pincode_verify_char_handle_get == 0)
	{
		aci_gatt_clt_write_without_resp(connection_handle, read_char_by_uuid_handle, flash_tem[GREETINGS_LEN_OFFSET], (uint8_t*)&flash_tem[GREETINGS_OFFSET]);
		
		get_tran_tran_char_handle_by_uuid();
		
		is_pincode_verify_char_handle_get = 1;
	}
	if (is_tran_tran_char_handle_get == 0)
	{
		uint8_t client_char_conf_data[] = {0x01, 0x00};
		uint8_t ret;
		
		tran_tran_handle = read_char_by_uuid_handle;
		is_tran_tran_char_handle_get = 1;

		ret = aci_gatt_clt_write_without_resp(connection_handle, tran_tran_handle+2, sizeof(client_char_conf_data), client_char_conf_data);
	}
	
	is_disc_read_char_by_uuid_resp_event_generated = 0;
}


void aci_gatt_clt_disc_read_char_by_uuid_resp_event(uint16_t Connection_Handle,
                                                    uint16_t Attribute_Handle,
                                                    uint8_t Attribute_Value_Length,
                                                    uint8_t Attribute_Value[])
{
	read_char_by_uuid_handle = Attribute_Handle;
	is_disc_read_char_by_uuid_resp_event_generated = 1;
}


void notification_event_handle(void)
{
	is_notification_event_generated = 0;
}


void aci_gatt_clt_notification_event(uint16_t Connection_Handle,
                                     uint16_t Attribute_Handle,
                                     uint16_t Attribute_Value_Length,
                                     uint8_t Attribute_Value[])
{
	if (Attribute_Handle == tran_tran_handle+1)
	{
		HAL_UART_Transmit_DMA(&usart_handle, (uint8_t*)&Attribute_Value, Attribute_Value_Length);
	}
	
	is_notification_event_generated = 1;
}


void pairing_complete_event_handle(void)
{
	is_pairing_complete_event_generated = 0;
}

void aci_gap_pairing_complete_event(uint16_t Connection_Handle,
                                    uint8_t Status,
                                    uint8_t Reason)
{
	char a[] = "pairing completed!";
	if (Status != BLE_STATUS_SUCCESS)
	{
		HAL_UART_Transmit(&usart_handle, (uint8_t*)&Reason, 1, 1);
		aci_gap_terminate(connection_handle, 0x13);
	}
	else
	{
		is_pairing_completed = 1;
		HAL_UART_Transmit(&usart_handle, (uint8_t*)&a, sizeof(a), 10);
	}
	
	is_pairing_complete_event_generated = 1;
}


void aci_gap_pass_key_req_event(uint16_t Connection_Handle)
{
	tBleStatus ret;
	char res[] = "password input";
	
	ret = aci_gap_pass_key_resp(connection_handle, connect_passkey);

	if (ret == BLE_STATUS_SUCCESS)
	{
		HAL_UART_Transmit(&usart_handle, (uint8_t*)&res, sizeof(res), 10);
	}
}


void clt_error_resp_event_handle(void)
{
	if (clt_error_resp_error_code == 0x0A)
	{
		if (is_pincode_verify_char_handle_get == 0)
		{
			is_pincode_verify_char_handle_get = 1;
			
			get_tran_tran_char_handle_by_uuid();
		}
		else if (is_tran_tran_char_handle_get == 0)
		{
			is_tran_tran_char_handle_get = 1;
		}
	}
	
	is_clt_error_resp_event_generated = 0;
}


void aci_gatt_clt_error_resp_event(uint16_t Connection_Handle,
                                   uint8_t Req_Opcode,
                                   uint16_t Attribute_Handle,
                                   uint8_t Error_Code)
{
	clt_error_resp_error_code = Error_Code;
	is_clt_error_resp_event_generated = 1;
}


void BLE_ERROR_IRQHandler(void)
{
	NVIC_SystemReset();
}


void aci_gatt_srv_attribute_modified_event(uint16_t Connection_Handle,
                                       uint16_t Attr_Handle,
                                       uint16_t Attr_Data_Length,
                                       uint8_t Attr_Data[])
{
}


void hci_encryption_change_event(uint8_t Status,
                                 uint16_t Connection_Handle,
                                 uint8_t Encryption_Enabled)
{
}
