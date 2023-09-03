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


NOSTACK_FUNCTION(NORETURN_FUNCTION(void NMI_IRQHandler(void)))
{
  HAL_CrashHandler(__get_MSP(), NMI_SIGNATURE);
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


void hci_le_connection_complete_event(uint8_t Status, uint16_t Connection_Handle, uint8_t Role, uint8_t Peer_Address_Type, uint8_t Peer_Address[6], uint16_t Conn_Interval, uint16_t Conn_Latency, uint16_t Supervision_Timeout, uint8_t Master_Clock_Accuracy)
{
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
}


void hci_disconnection_complete_event(uint8_t Status, uint16_t Connection_Handle, uint8_t Reason)
{
}


void aci_gatt_tx_pool_available_event(uint16_t Connection_Handle, uint16_t Available_Buffers)
{
}


void hci_le_extended_advertising_report_event(uint8_t Num_Reports, Extended_Advertising_Report_t Advertising_Report[])
{
}


void aci_gap_proc_complete_event(uint8_t Procedure_Code, uint8_t Status, uint8_t Data_Length, uint8_t Data[])
{
}


void disc_read_char_by_uuid_resp_event_handle(void)
{
}


void aci_gatt_clt_disc_read_char_by_uuid_resp_event(uint16_t Connection_Handle,
                                                    uint16_t Attribute_Handle,
                                                    uint8_t Attribute_Value_Length,
                                                    uint8_t Attribute_Value[])
{
}


void aci_gatt_clt_notification_event(uint16_t Connection_Handle,
                                     uint16_t Attribute_Handle,
                                     uint16_t Attribute_Value_Length,
                                     uint8_t Attribute_Value[])
{
}


void aci_gap_pairing_complete_event(uint16_t Connection_Handle,
                                    uint8_t Status,
                                    uint8_t Reason)
{
}


void aci_gap_pass_key_req_event(uint16_t Connection_Handle)
{
}


void aci_gatt_clt_error_resp_event(uint16_t Connection_Handle,
                                   uint8_t Req_Opcode,
                                   uint16_t Attribute_Handle,
                                   uint8_t Error_Code)
{
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
