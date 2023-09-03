#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

#include "rf_driver_hal.h"
#include "core_cm0plus.h"
#include "bluenrg_lp_api.h"
#include "link_layer.h"
#include "cmsis_armcc.h"

#include "usart_init.h"
#include "ble_init.h"
#include "ble_state.h"
#include "flash.h"
#include "at.h"


// usart params
extern UART_HandleTypeDef usart_handle;
extern uint8_t usart_RxBuffer[USART_RXBUFFERSIZE];
extern uint8_t frame[256];

// ble
extern volatile uint16_t connection_handle;
extern uint8_t mac_address[6];
extern uint8_t filter_name_keyword[FILTER_NAME_KEYWORD_SIZE];
extern uint8_t filter_name_keyword_size;
extern uint8_t filter_name_keyword_enable;
extern uint8_t filter_phy_address_keyword[FILTER_PHY_ADDRESS_KEYWORD_SIZE];
extern uint8_t filter_phy_address_keyword_size;
extern uint8_t filter_phy_address_keyword_enable;
extern uint32_t filter_signal_strength;
extern uint8_t filter_signal_strength_size;
extern uint8_t filter_signal_strength_enable;
extern Device_InfoDef devices[MAX_DEVICE_SIZE];
extern uint32_t current_sn;
extern uint32_t connect_passkey;
extern uint8_t is_device_connected;
extern volatile int app_flags;
extern uint8_t is_tran_tran_char_handle_get;
extern uint8_t is_pincode_verify_char_handle_get;

// AT param
extern uint8_t mode;
extern uint8_t ret_ok[10];
extern uint8_t suf[18];

// flash
extern uint8_t flash_tem[TOTAL_SIZE];


void avtive_disconnect(void)
{
	aci_gap_terminate(connection_handle, 0x13);
	
	is_device_connected = 0;
	is_tran_tran_char_handle_get = 0;
	is_pincode_verify_char_handle_get = 0;
}


char* Int2String(int num, char *str)
{
    int i = 0;
    if(num<0)
    {
        num = -num;
        str[i++] = '-';
    } 
 
    do
    {
        str[i++] = num%10+48; 
        num /= 10;   
    }while(num);
    
    str[i] = '\0';
    
    int j = 0;
    if(str[0]=='-')
    {
        j = 1;
        ++i;
    }

    for(;j<i/2;j++)
    {
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    } 
    
    return str;
}


int String2Int(char *p) 
{
	int r = 0;     
	int res = 0;   
	int pos = 1;  
	int size = strlen(p); 
	
	if (p[0] == '-')
	{
		r = size - 1;
	}
	else
	{
		r = size;
	}

	for (int i = 0; i < r; ++i)
	{
		res += (p[size-1-i]-48)*pos;
		pos *= 10;
	}
	
	return p[0]=='-'?-res:res; 
}


uint8_t get_string_size(char* string, uint8_t string_len)
{
	uint8_t string_size = 0;
	uint8_t i;
	for (i=0; i<string_len; i++)
	{
		if (string[i] == '\0')
		{
			return string_size;
		}
		else
		{
			string_size++;
		}
	}
	
	return string_len-1;
}


void HexToAsc(char *string, uint8_t num)
{
	char low = num & 0x0F;
	char high = (num & 0xF0) >> 4;
	
	switch(high){
		case 0x00:
			string[0] = '0';
			break;
		case 0x01:
			string[0] = '1';
			break;
		case 0x02:
			string[0]='2';
			break;
		case 0x03:
			string[0]='3';
			break;
		case 0x04:
		 string[0]='4';
			break;
		case 0x05:
			string[0]='5';
			break;
		case 0x06:
			string[0]='6';
			break;
		case 0x07:
			string[0]='7';
			break;
		case 0x08:
			string[0]='8';
			break;
		case 0x09:
			string[0]='9';
			break;
		case 0x0A:
			string[0]='A';
			break;
		case 0x0B:
			string[0]='B';
			break;
		case 0x0C:
			string[0]='C';
			break;
		case 0x0D:
			string[0]='D';
			break;
		case 0x0E:
			string[0]='E';
			break;
		case 0x0F:
			string[0]='F';
			break;
		default:
			return ;
	}
	
		switch(low){
		case 0x00:
			string[1] = '0';
			break;
		case 0x01:
			string[1] = '1';
			break;
		case 0x02:
			string[1]='2';
			break;
		case 0x03:
			string[1]='3';
			break;
		case 0x04:
		 string[1]='4';
			break;
		case 0x05:
			string[1]='5';
			break;
		case 0x06:
			string[1]='6';
			break;
		case 0x07:
			string[1]='7';
			break;
		case 0x08:
			string[1]='8';
			break;
		case 0x09:
			string[1]='9';
			break;
		case 0x0A:
			string[1]='A';
			break;
		case 0x0B:
			string[1]='B';
			break;
		case 0x0C:
			string[1]='C';
			break;
		case 0x0D:
			string[1]='D';
			break;
		case 0x0E:
			string[1]='E';
			break;
		case 0x0F:
			string[1]='F';
			break;
		default:
			return ;
	}
}


uint8_t AscToHex(uint8_t *string)
{
	uint8_t num = 0;
	
	switch (string[0])
	{
		case '0':
				num |= 0x00;
				break;
		case '1':
				num |= 0x01;
				break;
		case '2':
				num |= 0x02;
				break;
		case '3':
				num |= 0x03;
				break;
		case '4':
				num |= 0x04;
				break;
		case '5':
				num |= 0x05;
				break;
		case '6':
				num |= 0x06;
				break;
		case '7':
				num |= 0x07;
				break;
		case '8':
				num |= 0x08;
				break;
		case '9':
				num |= 0x09;
				break;
		case 'A':
				num |= 0x0A;
				break;
		case 'B':
				num |= 0x0B;
				break;
		case 'C':
				num |= 0x0C;
				break;
		case 'D':
				num |= 0x0D;
				break;
		case 'E':
				num |= 0x0E;
				break;
		case 'F':
				num |= 0x0F;
				break;
		default:
				break;
	}
	
	num = num << 4;
	
	switch (string[1])
	{
		case '0':
				num |= 0x00;
				break;
		case '1':
				num |= 0x01;
				break;
		case '2':
				num |= 0x02;
				break;
		case '3':
				num |= 0x03;
				break;
		case '4':
				num |= 0x04;
				break;
		case '5':
				num |= 0x05;
				break;
		case '6':
				num |= 0x06;
				break;
		case '7':
				num |= 0x07;
				break;
		case '8':
				num |= 0x08;
				break;
		case '9':
				num |= 0x09;
				break;
		case 'A':
				num |= 0x0A;
				break;
		case 'B':
				num |= 0x0B;
				break;
		case 'C':
				num |= 0x0C;
				break;
		case 'D':
				num |= 0x0D;
				break;
		case 'E':
				num |= 0x0E;
				break;
		case 'F':
				num |= 0x0F;
				break;
		default:
				break;
	}
	
	return num;
}


void enter_AT_command_mode(void)
{
    mode = AT_MODE;

    HAL_UART_Transmit(&usart_handle, ret_ok, sizeof(ret_ok), 10);
}


void exit_AT_command_mode(void)
{
    mode = TRAN_TRAN_MODE;

    HAL_UART_Transmit(&usart_handle, ret_ok, sizeof(ret_ok), 10);
}


void soft_reset(void)
{
	HAL_UART_Transmit(&usart_handle, ret_ok, sizeof(ret_ok), 10);
	
	__set_PRIMASK(1);
	NVIC_SystemReset();
}


void serial_port_info_query(void)
{
	char string[10];
	uint8_t string_size = 0;
	uint8_t current_frame_size = 0;
	uint32_t baud_rate;
	uint32_t data_len;
	uint32_t stop_bits;
	uint32_t parity;
	
	memcpy((uint8_t*)&baud_rate, (uint8_t*)&flash_tem[USART_BAUD_RATE_OFFSET], USART_BAUD_RATE_SIZE);
	Int2String(baud_rate, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	memset(string, 0, 10);
	current_frame_size += string_size;
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&data_len, (uint8_t*)&flash_tem[USART_DATA_LEN_OFFSET], USART_DATA_LEN_SIZE);
	
	if (data_len == 0)
	{
		frame[current_frame_size] = '8';
	}
	else if(data_len == USART_CR1_M_1)
	{
		frame[current_frame_size] = '7';
	}
	else
	{
		frame[current_frame_size] = '9';
	}
	current_frame_size++;
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&stop_bits, (uint8_t*)&flash_tem[USART_STOP_BITS_LEN_OFFSET], USART_STOP_BITS_LEN_SIZE);
	if (stop_bits == 0)
	{
		frame[current_frame_size] = '1';
	}
	else if(stop_bits == USART_CR2_STOP_0)
	{
		frame[current_frame_size] = '0';
		current_frame_size++;
		frame[current_frame_size] = '.';
		current_frame_size++;
		frame[current_frame_size] = '5';
	}
	else if(stop_bits == (USART_CR2_STOP_0 | USART_CR2_STOP_1))
	{
		frame[current_frame_size] = '1';
		current_frame_size++;
		frame[current_frame_size] = '.';
		current_frame_size++;
		frame[current_frame_size] = '5';
	}
	else
	{
		frame[current_frame_size] = '2';
	}
	current_frame_size ++;
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&parity, (uint8_t*)&flash_tem[USART_PARITY_OFFSET], USART_PARITY_SIZE);
	if (parity == 0)
	{
		frame[current_frame_size] = '0';
	}
	else if(parity == USART_CR1_PCE)
	{
		frame[current_frame_size] = '1';
	}
	else
	{
		frame[current_frame_size] = '2';
	}
	current_frame_size ++;
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void serial_port_info_set(void)
{
	char valid_data[20];
	uint8_t start_loc;
	uint8_t end_loc;	
	const char s[2] = ",";
	char *token;
	uint8_t sign = 0;
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	uint32_t baud_rate = String2Int(token);
	
	memcpy((uint8_t*)&flash_tem[USART_BAUD_RATE_OFFSET], (uint8_t*)&baud_rate, USART_BAUD_RATE_SIZE);
	
	while( token != NULL )
	{
		token = strtok(NULL, s);

		if (sign == 0)
		{
			 if (memcmp(token, "8", 1) == 0)
			 {
				 uint32_t data_len = UART_WORDLENGTH_8B;
				 memcpy((uint8_t*)&flash_tem[USART_DATA_LEN_OFFSET], (uint8_t*)&data_len, USART_DATA_LEN_SIZE);
			 }
			 else if (memcmp(token, "7", 1) == 0)
			 {
				 uint32_t data_len = UART_WORDLENGTH_7B;
				 memcpy((uint8_t*)&flash_tem[USART_DATA_LEN_OFFSET], (uint8_t*)&data_len, USART_DATA_LEN_SIZE);
			 }
			 else
			 {
				 uint32_t data_len = UART_WORDLENGTH_9B;
				 memcpy((uint8_t*)&flash_tem[USART_DATA_LEN_OFFSET], (uint8_t*)&data_len, USART_DATA_LEN_SIZE);
			 }
			 
			 sign++;
		}
		else if (sign == 1)
		{
			 if (memcmp(token, "1", 1) == 0)
			 {
				 uint32_t stop_bits = UART_STOPBITS_1;
				 memcpy((uint8_t*)&flash_tem[USART_STOP_BITS_LEN_OFFSET], (uint8_t*)&stop_bits, USART_STOP_BITS_LEN_SIZE);
			 }
			 else
			 {
				 uint32_t stop_bits = UART_STOPBITS_2;
				 memcpy((uint8_t*)&flash_tem[USART_STOP_BITS_LEN_OFFSET], (uint8_t*)&stop_bits, USART_STOP_BITS_LEN_SIZE);
			 }
			 
			 sign++;
		}
		else if (sign == 2)
		{
			 if (memcmp(token, "0", 1) == 0)
			 {
				 uint32_t parity = UART_PARITY_NONE;
				 memcpy((uint8_t*)&flash_tem[USART_PARITY_OFFSET], (uint8_t*)&parity, USART_PARITY_SIZE);
			 }
			 else if(memcmp(token, "1", 1) == 0)
			 {
				 uint32_t parity = UART_PARITY_EVEN;
				 memcpy((uint8_t*)&flash_tem[USART_PARITY_OFFSET], (uint8_t*)&parity, USART_PARITY_SIZE);
			 }
			 else
			 {
				 uint32_t parity = UART_PARITY_ODD;
				 memcpy((uint8_t*)&flash_tem[USART_PARITY_OFFSET], (uint8_t*)&parity, USART_PARITY_SIZE);
			 }
			 
			 sign++;
		}
  }

	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	//USART1_init();
	
	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void local_ble_name_query(void)
{
	uint8_t current_size = flash_tem[BLE_NAME_LEN_OFFSET];
	
	memcpy((uint8_t*)&frame[0], (uint8_t*)&flash_tem[BLE_NAME_OFFSET], flash_tem[BLE_NAME_LEN_OFFSET]);
	memcpy((uint8_t*)&frame[current_size+1], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_size+18);
}


void local_ble_name_set(void)
{
	uint8_t start_loc;
	uint8_t end_loc;	
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&flash_tem[BLE_NAME_OFFSET], (uint8_t*)&usart_RxBuffer[8], end_loc-start_loc);
	flash_tem[BLE_NAME_LEN_OFFSET] = end_loc-start_loc;
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void local_mac_address_query(void)
{
	HexToAsc((char *)&frame[0], mac_address[0]);
	frame[2]= ':';
	HexToAsc((char *)&frame[3], mac_address[1]);
	frame[5]= ':';
	HexToAsc((char *)&frame[6], mac_address[2]);
	frame[8]= ':';
	HexToAsc((char *)&frame[9], mac_address[3]);
	frame[11]= ':';
	HexToAsc((char *)&frame[12], mac_address[4]);
	frame[14]= ':';
	HexToAsc((char *)&frame[15], mac_address[5]);
	memcpy((uint8_t*)&frame[17], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, 35);
}


void transimit_power_query(void)
{
	char string[4];
	uint8_t string_size = 0;
	uint8_t current_frame_size = 0;
	uint32_t ble_tx_power;
	
	memcpy((uint8_t*)&ble_tx_power, (uint8_t*)&flash_tem[BLE_TX_POWER_OFFSET], BLE_TX_POWER_SIZE);
	
	Int2String(ble_tx_power, string);
	string_size = get_string_size(string, 4);
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	current_frame_size += string_size;
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void transimit_power_set(void)
{
	char valid_data[4];
	uint8_t start_loc;
	uint8_t end_loc;	
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	uint32_t ble_tx_power = String2Int(valid_data);
	
	memcpy((uint8_t*)&flash_tem[BLE_TX_POWER_OFFSET], (uint8_t*)&ble_tx_power, BLE_TX_POWER_SIZE);
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	//aci_hal_set_tx_power_level(0, ble_tx_power);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void password_pair_enable_query(void)
{
	if (flash_tem[BLE_PASSWORD_PAIR_ENABLE_OFFSET] == 0)
	{
		frame[0] = 'O';
		frame[1] = 'F';
		frame[2] = 'F';
		memcpy((uint8_t*)&frame[3], (uint8_t*)&suf[0], 18);

		HAL_UART_Transmit_DMA(&usart_handle, frame, 21);
	}
	else
	{
		frame[0] = 'O';
		frame[1] = 'N';
		memcpy((uint8_t*)&frame[2], (uint8_t*)&suf[0], 18);

		HAL_UART_Transmit_DMA(&usart_handle, frame, 20);
	}
}


void password_pair_enable_set(void)
{
	if (usart_RxBuffer[10] == 'N')
	{
		flash_tem[BLE_PASSWORD_PAIR_ENABLE_OFFSET] = 1;
	}
	else
	{
			flash_tem[BLE_PASSWORD_PAIR_ENABLE_OFFSET] = 0;
	}
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void start_search_device(void)
{
	tBleStatus ret;
	
	if (is_device_connected == 1)
	{
		avtive_disconnect();
	}
	
	current_sn = 0;
	
	ret = aci_gap_start_procedure(0x01, LE_1M_PHY_BIT, 0, 0);
	
	HAL_UART_Transmit(&usart_handle, &ret, 1, 5);
	
	if (ret == BLE_STATUS_SUCCESS)
	{
		HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
	}
}


void direct_connect_by_sn(void)
{
	tBleStatus ret;
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	int sn;

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			usart_RxBuffer[i] = '\0';
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc+1);
	
	token = strtok(valid_data, s);
	
	sn = String2Int(token);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)
		{
			connect_passkey = String2Int(token);
			memcpy((uint8_t*)&flash_tem[LAST_TIME_ADDRESS_PINCODE_OFFSET], (uint8_t*)&connect_passkey, LAST_TIME_ADDRESS_PINCODE_SIZE-4);

			sign++;
		}
  }
	
	frame[0] = 'L';
	frame[1] = 'I';
	frame[2] = 'N';
	frame[3] = 'K';
	frame[4] = ' ';
	
	memcpy((uint8_t*)&frame[5], (uint8_t*)&ret_ok[0], sizeof(ret_ok));
	
	memcpy((uint8_t*)&flash_tem[LAST_TIME_ADDRESS_OFFSET], (uint8_t*)&devices[sn-1].address, LAST_TIME_ADDRESS_SIZE);
	flash_tem[LAST_TIME_ADDRESS_TYPE_OFFSET] = devices[sn-1].address_type;
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	ret = aci_gap_create_connection(LE_1M_PHY_BIT, devices[sn-1].address_type, devices[sn-1].address);
	if (ret == BLE_STATUS_SUCCESS)
	{
		HAL_UART_Transmit_DMA(&usart_handle, frame, 15);
	}
}


void direct_connect_by_mac_address(void)
{
	tBleStatus ret;
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;
	uint8_t sign = 0;
	uint8_t address[6];
	const char s[2] = ",";
	char *token;

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	address[0] = strtol(&token[0], NULL, 16);
	address[1] = strtol(&token[3], NULL, 16);
	address[2] = strtol(&token[6], NULL, 16);
	address[3] = strtol(&token[9], NULL, 16);
	address[4] = strtol(&token[12], NULL, 16);
	address[5] = strtol(&token[15], NULL, 16);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			connect_passkey = String2Int(token);
			memcpy((uint8_t*)&flash_tem[LAST_TIME_ADDRESS_PINCODE_OFFSET], (uint8_t*)&connect_passkey, LAST_TIME_ADDRESS_PINCODE_SIZE-4);
			 
			sign++;
		}
  }
	
	frame[0] = 'L';
	frame[1] = 'I';
	frame[2] = 'N';
	frame[3] = 'K';
	frame[4] = ' ';
	
	memcpy((uint8_t*)&frame[5], (uint8_t*)&ret_ok[0], sizeof(ret_ok));
	
	if (is_device_connected == 1)
	{
		avtive_disconnect();
	}

	memcpy((uint8_t*)&flash_tem[LAST_TIME_ADDRESS_OFFSET], (uint8_t*)&address[0], LAST_TIME_ADDRESS_SIZE);
	flash_tem[LAST_TIME_ADDRESS_TYPE_OFFSET] = 0x00;
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	ret = aci_gap_create_connection(LE_1M_PHY_BIT, 0x00, address);
	if (ret == BLE_STATUS_SUCCESS)
	{
		HAL_UART_Transmit_DMA(&usart_handle, frame, 15);
	}
}


void default_connect_device_params_query(void)
{
	uint8_t default_address[6];
	uint32_t default_address_password;
	uint8_t default_address_enable[1];
	char string[10];
	uint8_t string_size;
	
	memcpy((uint8_t*)&default_address[0], (uint8_t*)&flash_tem[DEFAULT_ADDRESS_OFFSET], 6);
	memcpy((uint8_t*)&default_address_password, (uint8_t*)&flash_tem[DEFAULT_ADDRESS_PINCODE_OFFSET], 4);
	memcpy((uint8_t*)&default_address_enable[0], (uint8_t*)&flash_tem[DEFAULT_ADDRESS_ENABLE_OFFSET], 1);
	
	HexToAsc((char *)&frame[0], default_address[0]);
	frame[2]= ':';
	HexToAsc((char *)&frame[3], default_address[1]);
	frame[5]= ':';
	HexToAsc((char *)&frame[6], default_address[2]);
	frame[8]= ':';
	HexToAsc((char *)&frame[9], default_address[3]);
	frame[11]= ':';
	HexToAsc((char *)&frame[12], default_address[4]);
	frame[14]= ':';
	HexToAsc((char *)&frame[15], default_address[5]);
	frame[17] = ',';
	
	Int2String(default_address_password, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[18], (uint8_t*)&string, string_size);
	frame[24] = ',';

	if (default_address_enable[0] == 1)
	{
		frame[25] = 'O';
		frame[26] = 'N';
		memcpy((uint8_t*)&frame[27], (uint8_t*)&suf[0], 18);

		HAL_UART_Transmit_DMA(&usart_handle, frame, 45);
	}
	else
	{
		frame[25] = 'O';
		frame[26] = 'F';
		frame[27] = 'F';
		memcpy((uint8_t*)&frame[28], (uint8_t*)&suf[0], 18);

		HAL_UART_Transmit_DMA(&usart_handle, frame, 46);
	}
}


void default_connect_device_params_set(void)
{
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	flash_tem[DEFAULT_ADDRESS_OFFSET] = strtol(&token[0], NULL, 16);
	flash_tem[DEFAULT_ADDRESS_OFFSET+1] = strtol(&token[3], NULL, 16);
	flash_tem[DEFAULT_ADDRESS_OFFSET+2] = strtol(&token[6], NULL, 16);
	flash_tem[DEFAULT_ADDRESS_OFFSET+3] = strtol(&token[9], NULL, 16);
	flash_tem[DEFAULT_ADDRESS_OFFSET+4] = strtol(&token[12], NULL, 16);
	flash_tem[DEFAULT_ADDRESS_OFFSET+5] = strtol(&token[15], NULL, 16);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)
		{
			uint32_t pincode = String2Int(token);
			memcpy((uint8_t*)&flash_tem[DEFAULT_ADDRESS_PINCODE_OFFSET], (uint8_t*)&pincode, DEFAULT_ADDRESS_PINCODE_SIZE-4);
			 
			sign++;
		}
		else if (sign == 1)
		{
			if (token[1] == 'N')
			{
				flash_tem[DEFAULT_ADDRESS_ENABLE_OFFSET] = 1;
			}
			else
			{
				flash_tem[DEFAULT_ADDRESS_ENABLE_OFFSET] = 0;
			}
			 
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void role_control_query(void)
{
	if (flash_tem[ADAPTER_MASTER_ROLE_ENABLE_OFFSET] == 1)
	{
		if (flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] == 1)
		{
			frame[0] = 'O';
			frame[1] = 'N';
			frame[2] = ',';
			frame[3] = 'O';
			frame[4] = 'N';

			memcpy((uint8_t*)&frame[5], (uint8_t*)&suf[0], 18);
			HAL_UART_Transmit_DMA(&usart_handle, frame, 23);
		}
		else
		{
			frame[0] = 'O';
			frame[1] = 'N';
			frame[2] = ',';
			frame[3] = 'O';
			frame[4] = 'F';
			frame[5] = 'F';

			memcpy((uint8_t*)&frame[6], (uint8_t*)&suf[0], 18);
			HAL_UART_Transmit_DMA(&usart_handle, frame, 24);
		}
	}
	else
	{
		if (flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] == 1)
		{
			frame[0] = 'O';
			frame[1] = 'F';
			frame[2] = 'F';
			frame[3] = ',';
			frame[4] = 'O';
			frame[5] = 'N';

			memcpy((uint8_t*)&frame[6], (uint8_t*)&suf[0], 18);
			HAL_UART_Transmit_DMA(&usart_handle, frame, 24);
		}
		else
		{
			frame[0] = 'O';
			frame[1] = 'F';
			frame[2] = 'F';
			frame[3] = ',';
			frame[4] = 'O';
			frame[5] = 'F';
			frame[6] = 'F';

			memcpy((uint8_t*)&frame[7], (uint8_t*)&suf[0], 18);
			HAL_UART_Transmit_DMA(&usart_handle, frame, 25);
		}
	}
}


void role_control_set(void)
{
	if (usart_RxBuffer[9] == 'N')
	{
		flash_tem[ADAPTER_MASTER_ROLE_ENABLE_OFFSET] = 1;
		
		if (usart_RxBuffer[12] == 'N')
		{
			flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] = 1;
		}
		else
		{
			flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] = 0;
		}
	}
	else
	{
		flash_tem[ADAPTER_MASTER_ROLE_ENABLE_OFFSET] = 0;
		
		if (usart_RxBuffer[13] == 'N')
		{
			flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] = 1;
		}
		else
		{
			flash_tem[ADAPTER_SLAVE_ROLE_ENABLE_OFFSET] = 0;
		}
	}
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void transparent_transimission_service_info_query(void)
{
	uint8_t current_frame_size = 0;
	uint8_t tem_var;
	UUID_t tran_tran_tx_service_uuid;
	uint8_t tran_tran_tx_service_uuid_size;
	UUID_t tran_tran_tx_char_uuid;
	uint8_t tran_tran_tx_char_uuid_size;
	UUID_t tran_tran_rx_service_uuid;
	uint8_t tran_tran_rx_service_uuid_size;
	UUID_t tran_tran_rx_char_uuid;
	uint8_t tran_tran_rx_char_uuid_size;
	
	tran_tran_tx_service_uuid_size = flash_tem[BLE_TRAN_TRAN_TX_SERV_UUID_LEN_OFFSET];
	memcpy((uint8_t*)&tran_tran_tx_service_uuid.UUID_128[0], (uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_SERV_UUID_OFFSET], tran_tran_tx_service_uuid_size);
	tran_tran_tx_char_uuid_size = flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_OFFSET];
	memcpy((uint8_t*)&tran_tran_tx_char_uuid.UUID_128[0], (uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_OFFSET], tran_tran_tx_char_uuid_size);
	
	tran_tran_rx_service_uuid_size = flash_tem[BLE_TRAN_TRAN_RX_SERV_UUID_LEN_OFFSET];
	memcpy((uint8_t*)&tran_tran_rx_service_uuid.UUID_128[0], (uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_SERV_UUID_OFFSET], tran_tran_rx_service_uuid_size);
	tran_tran_rx_char_uuid_size = flash_tem[BLE_TRAN_TRAN_RX_CHAR_UUID_LEN_OFFSET];
	memcpy((uint8_t*)&tran_tran_rx_char_uuid.UUID_128[0], (uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_CHAR_UUID_OFFSET], tran_tran_rx_char_uuid_size);
	
	if (tran_tran_tx_service_uuid_size == 2)
	{		
		tem_var = (uint8_t)(tran_tran_tx_service_uuid.UUID_16 >> 8);
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
		
		tem_var = (uint8_t)tran_tran_tx_service_uuid.UUID_16;
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
	}
	else
	{
		for (uint8_t i=0; i<tran_tran_tx_service_uuid_size; i++)
		{
			HexToAsc((char *)&frame[current_frame_size], tran_tran_tx_service_uuid.UUID_128[i]);
			current_frame_size += 2;
		}
	}
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	if (tran_tran_tx_char_uuid_size == 2)
	{
		tem_var = (uint8_t)(tran_tran_tx_char_uuid.UUID_16 >> 8);
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
		
		tem_var = (uint8_t)tran_tran_tx_char_uuid.UUID_16;
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
	}
	else
	{
		for (uint8_t i=0; i<tran_tran_tx_char_uuid_size; i++)
		{
			HexToAsc((char *)&frame[current_frame_size], tran_tran_tx_char_uuid.UUID_128[i]);
			current_frame_size += 2;
		}
	}
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	if (tran_tran_rx_service_uuid_size == 2)
	{
		tem_var = (uint8_t)(tran_tran_rx_service_uuid.UUID_16 >> 8);
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
		
		tem_var = (uint8_t)tran_tran_rx_service_uuid.UUID_16;
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
	}
	else
	{
		for (uint8_t i=0; i<tran_tran_rx_service_uuid_size; i++)
		{
			HexToAsc((char *)&frame[current_frame_size], tran_tran_rx_service_uuid.UUID_128[i]);
			current_frame_size += 2;
		}
	}
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	if (tran_tran_rx_char_uuid_size == 2)
	{
		tem_var = (uint8_t)(tran_tran_rx_char_uuid.UUID_16 >> 8);
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
		
		tem_var = (uint8_t)tran_tran_rx_char_uuid.UUID_16;
		HexToAsc((char *)&frame[current_frame_size], tem_var);
		current_frame_size += 2;
	}
	else
	{
		for (uint8_t i=0; i<tran_tran_rx_char_uuid_size; i++)
		{
			HexToAsc((char *)&frame[current_frame_size], tran_tran_rx_char_uuid.UUID_128[i]);
			current_frame_size += 2;
		}
	}

	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void transparent_transimission_service_info_set(void)
{
	char valid_data[128];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	char tem_char[2];
	UUID_t tran_tran_tx_service_uuid;
	uint8_t tran_tran_tx_service_uuid_size;
	UUID_t tran_tran_tx_char_uuid;
	uint8_t tran_tran_tx_char_uuid_size;
	UUID_t tran_tran_rx_service_uuid;
	uint8_t tran_tran_rx_service_uuid_size;
	UUID_t tran_tran_rx_char_uuid;
	uint8_t tran_tran_rx_char_uuid_size;

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc+1);
	
	token = strtok(valid_data, s);
	
	for (uint8_t i=0,k=0; i<end_loc-start_loc; k++,i+=2)
	{
		if (token[i] == '\0')
		{
			break;
		}
		memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[i], 2);
		tran_tran_tx_service_uuid.UUID_128[k] = strtol(&tem_char[0], NULL, 16);
		tran_tran_tx_service_uuid_size = k + 1;
	}
	
	if (tran_tran_tx_service_uuid_size == 2)
	{
		uint8_t tem = tran_tran_tx_service_uuid.UUID_128[1];
		tran_tran_tx_service_uuid.UUID_128[1] = tran_tran_tx_service_uuid.UUID_128[0];
		tran_tran_tx_service_uuid.UUID_128[0] = tem;
	}
	
	memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_SERV_UUID_OFFSET], (uint8_t*)&tran_tran_tx_service_uuid.UUID_128[0], tran_tran_tx_service_uuid_size);
	memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_SERV_UUID_LEN_OFFSET], (uint8_t*)&tran_tran_tx_service_uuid_size, 1);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			for (uint8_t k=0,i=0; i<end_loc-start_loc+1; k++,i+=2)
			{
				if (token[i] == '\0')
				{
					break;
				}
				memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[i], 2);
				tran_tran_tx_char_uuid.UUID_128[k] = strtol(&tem_char[0], NULL, 16);
				tran_tran_tx_char_uuid_size = k+1;
			}
			
			if (tran_tran_tx_char_uuid_size == 2)
			{
				uint8_t tem = tran_tran_tx_char_uuid.UUID_128[1];
				tran_tran_tx_char_uuid.UUID_128[1] = tran_tran_tx_char_uuid.UUID_128[0];
				tran_tran_tx_char_uuid.UUID_128[0] = tem;
			}
			
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_OFFSET], (uint8_t*)&tran_tran_tx_char_uuid.UUID_128[0], tran_tran_tx_char_uuid_size);
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_OFFSET], (uint8_t*)&tran_tran_tx_char_uuid_size, 1);
			
			sign++;
		}
		else if (sign == 1)
		{
			for (uint8_t i=0,k=0; i<end_loc-start_loc; k++,i+=2)
			{
				if (token[i] == '\0')
				{
					break;
				}
				memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[i], 2);
				tran_tran_rx_service_uuid.UUID_128[k] = strtol(&tem_char[0], NULL, 16);
				tran_tran_rx_service_uuid_size = k + 1;
			}
			
			if (tran_tran_rx_service_uuid_size == 2)
			{
				uint8_t tem = tran_tran_rx_service_uuid.UUID_128[1];
				tran_tran_rx_service_uuid.UUID_128[1] = tran_tran_rx_service_uuid.UUID_128[0];
				tran_tran_rx_service_uuid.UUID_128[0] = tem;
			}
			
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_SERV_UUID_OFFSET], (uint8_t*)&tran_tran_rx_service_uuid.UUID_128[0], tran_tran_rx_service_uuid_size);
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_SERV_UUID_LEN_OFFSET], (uint8_t*)&tran_tran_rx_service_uuid_size, 1);
			
			sign++;
		}
		else if (sign == 2)
		{
			for (uint8_t k=0,i=0; i<end_loc-start_loc+1; k++,i+=2)
			{
				if (token[i] == '{')
				{
					break;
				}
				memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[i], 2);
				tran_tran_rx_char_uuid.UUID_128[k] = strtol(&tem_char[0], NULL, 16);
				tran_tran_rx_char_uuid_size = k+1;
			}
			
			if (tran_tran_rx_char_uuid_size == 2)
			{
				uint8_t tem = tran_tran_rx_char_uuid.UUID_128[1];
				tran_tran_rx_char_uuid.UUID_128[1] = tran_tran_rx_char_uuid.UUID_128[0];
				tran_tran_rx_char_uuid.UUID_128[0] = tem;
			}
			
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_CHAR_UUID_OFFSET], (uint8_t*)&tran_tran_rx_char_uuid.UUID_128[0], tran_tran_rx_char_uuid_size);
			memcpy((uint8_t*)&flash_tem[BLE_TRAN_TRAN_RX_CHAR_UUID_LEN_OFFSET], (uint8_t*)&tran_tran_rx_char_uuid_size, 1);
			
			sign++;
		}
  }

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void manufacturer_info_query(void)
{
	uint8_t current_frame_size = 0;
	uint8_t manufacturer_ID[2];
	uint8_t manufacturer_data[MANU_DATA_SIZE];
	uint8_t manufacturer_data_len;
	
	memcpy((uint8_t*)&manufacturer_ID[0], (uint8_t*)&flash_tem[MANU_ID_OFFSET], 2);
	
	HexToAsc((char *)&frame[current_frame_size], manufacturer_ID[0]);
	current_frame_size += 2;
	HexToAsc((char *)&frame[current_frame_size], manufacturer_ID[1]);
	current_frame_size += 2;
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	manufacturer_data_len = flash_tem[MANU_DATA_LEN_OFFSET];
	memcpy((uint8_t*)&manufacturer_data[0], (uint8_t*)&flash_tem[MANU_DATA_OFFSET], manufacturer_data_len);
	
	for (uint8_t i=0; i<manufacturer_data_len; i++)
	{
		frame[current_frame_size] = manufacturer_data[i];
		current_frame_size++;
	}

	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void manufacturer_info_set(void)
{
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	char tem_char[2];
	uint8_t manufacturer_data[MANU_DATA_SIZE];
	uint8_t manufacturer_data_len = 0;
	uint8_t manufacturer_ID[2];

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc+1);
	
	token = strtok(valid_data, s);
	
	memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[0], 2);
	manufacturer_ID[0] = strtol(&tem_char[0], NULL, 16);
	memcpy((uint8_t*)&tem_char[0], (uint8_t*)&token[2], 2);
	manufacturer_ID[1] = strtol(&tem_char[0], NULL, 16);
	
	memcpy((uint8_t*)&flash_tem[MANU_ID_OFFSET], (uint8_t*)&manufacturer_ID[0], 2);
	
	while( token != NULL )
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			for (uint8_t i=0; i<end_loc-start_loc+1; i++)
			{
				if(token[i] == '{')
				{
					break;
				}
				manufacturer_data[i] = token[i];
				manufacturer_data_len++;
			}
			
			memcpy((uint8_t*)&flash_tem[MANU_DATA_OFFSET], (uint8_t*)&manufacturer_data[0], manufacturer_data_len);
			flash_tem[MANU_DATA_LEN_OFFSET] = manufacturer_data_len;
			
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void broadcast_interval_query(void)
{	
	char string[10];
	uint8_t string_size = 0;
	uint8_t current_frame_size = 0;
	uint32_t adv_interval_min;
	uint32_t adv_interval_max;
	
	memcpy((uint8_t*)&adv_interval_min, (uint8_t*)&flash_tem[BLE_ADV_INTER_MIN_OFFSET], BLE_ADV_INTER_MIN_SIZE);
	
	Int2String(adv_interval_min, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	current_frame_size += string_size;
	memset(string, 0, 10);
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&adv_interval_max, (uint8_t*)&flash_tem[BLE_ADV_INTER_MAX_OFFSET], BLE_ADV_INTER_MAX_SIZE);
	
	Int2String(adv_interval_max, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	current_frame_size += string_size;
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);
	
	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void broadcast_interval_set(void)
{
	char valid_data[20];
	uint8_t start_loc;
	uint8_t end_loc;	
	const char s[2] = ",";
	char *token;
	uint8_t sign = 0;
	
	memset(valid_data, 0, 20);
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	uint32_t adv_interval = String2Int(token);
	
	memcpy((uint8_t*)&flash_tem[BLE_ADV_INTER_MIN_OFFSET], (uint8_t*)&adv_interval, BLE_ADV_INTER_MIN_SIZE);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			adv_interval = String2Int(token);
			
			memcpy((uint8_t*)&flash_tem[BLE_ADV_INTER_MAX_OFFSET], (uint8_t*)&adv_interval, BLE_ADV_INTER_MAX_SIZE);
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);
	
	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void scan_interval_query(void)
{
	char string[10];
	uint8_t string_size = 0;
	uint8_t current_frame_size = 0;
	uint32_t scan_interval;
	uint32_t scan_window;
	
	memcpy((uint8_t*)&scan_interval, (uint8_t*)&flash_tem[BLE_SCAN_INTER_OFFSET], BLE_SCAN_INTER_SIZE);
	
	Int2String(scan_interval, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	memset(string, 0, 10);
	current_frame_size += string_size;
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&scan_window, (uint8_t*)&flash_tem[BLE_SCAN_WINDOW_OFFSET], BLE_SCAN_WINDOW_SIZE);
	
	Int2String(scan_window, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	current_frame_size += string_size;
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void scan_interval_set(void)
{
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	
	memset(valid_data, 0, 32);
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	uint32_t scan_interval = String2Int(token);
	
	memcpy((uint8_t*)&flash_tem[BLE_SCAN_INTER_OFFSET], (uint8_t*)&scan_interval, BLE_SCAN_INTER_SIZE);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			uint32_t scan_window = String2Int(token);
			
			memcpy((uint8_t*)&flash_tem[BLE_SCAN_WINDOW_OFFSET], (uint8_t*)&scan_window, BLE_SCAN_WINDOW_SIZE);
			
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void connect_interval_query(void)
{
	char string[10];
	uint8_t string_size = 0;
	uint8_t current_frame_size = 0;
	uint32_t connect_interval_min;
	uint32_t connect_interval_max;
	
	memcpy((uint8_t*)&connect_interval_min, (uint8_t*)&flash_tem[BLE_CONN_INTER_MIN_OFFSET], BLE_CONN_INTER_MIN_SIZE);
	
	Int2String(connect_interval_min, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	memset(string, 0, 10);
	current_frame_size += string_size;
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	memcpy((uint8_t*)&connect_interval_max, (uint8_t*)&flash_tem[BLE_CONN_INTER_MAX_OFFSET], BLE_CONN_INTER_MAX_SIZE);
	
	Int2String(connect_interval_max, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&string, string_size);
	current_frame_size += string_size;
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
}


void connect_interval_set(void)
{
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	
	memset(valid_data, 0, 20);
	
	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	uint32_t connect_interval_min = String2Int(token);
	
	memcpy((uint8_t*)&flash_tem[BLE_CONN_INTER_MIN_OFFSET], (uint8_t*)&connect_interval_min, BLE_CONN_INTER_MIN_SIZE);
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)	
		{
			uint32_t connect_interval_max = String2Int(token);
			
			memcpy((uint8_t*)&flash_tem[BLE_CONN_INTER_MAX_OFFSET], (uint8_t*)&connect_interval_max, BLE_CONN_INTER_MAX_SIZE);
			
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void greetings_query(void)
{
	uint8_t current_frame_size = 0;
	uint8_t greetings_len;
	uint8_t greetings[GREETINGS_SIZE];
	uint8_t greetings_enable;
	
	greetings_len = flash_tem[GREETINGS_LEN_OFFSET];
	memcpy((uint8_t*)&greetings[0], (uint8_t*)&flash_tem[GREETINGS_OFFSET], greetings_len);
	greetings_enable = flash_tem[GREETINGS_ENABLE_OFFSET];
	
	memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&greetings[0], greetings_len);
	current_frame_size += greetings_len;
	
	frame[current_frame_size] = ',';
	current_frame_size++;
	
	if (greetings_enable == 1)
	{
		frame[current_frame_size] = 'O';
		current_frame_size++;
		frame[current_frame_size] = 'N';
		current_frame_size++;
		
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);
		HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
	}
	else
	{
		frame[current_frame_size] = 'O';
		current_frame_size++;
		frame[current_frame_size] = 'F';
		current_frame_size++;
		frame[current_frame_size] = 'F';
		current_frame_size++;
		
		memcpy((uint8_t*)&frame[current_frame_size], (uint8_t*)&suf[0], 18);
		HAL_UART_Transmit_DMA(&usart_handle, frame, current_frame_size+18);
	}
}


void greetings_set(void)
{
	char valid_data[32];
	uint8_t start_loc;
	uint8_t end_loc;	
	uint8_t sign = 0;
	const char s[2] = ",";
	char *token;
	uint8_t greetings[GREETINGS_SIZE];
	uint8_t greetings_len = 0;

	for (uint8_t i=0; i<127; i++)
	{
		if (usart_RxBuffer[i] == '=')
		{
			start_loc = i+1;
		}
		
		if (usart_RxBuffer[i] == '{')
		{
			end_loc = i;
			break;
		}
	}
	
	memcpy((uint8_t*)&valid_data[0], (uint8_t*)&usart_RxBuffer[start_loc], end_loc-start_loc);
	
	token = strtok(valid_data, s);
	
	for (uint8_t i=0; i<end_loc-start_loc; i++)
	{
		if (token[i] == '\0')
		{
			break;
		}
		
		greetings[i] = token[i];
		greetings_len++;
	}
	
	memcpy((uint8_t*)&flash_tem[GREETINGS_OFFSET], (uint8_t*)&greetings[0], greetings_len);
	flash_tem[GREETINGS_LEN_OFFSET] = greetings_len;
	
	while( token != NULL ) 
	{
		token = strtok(NULL, s);

		if (sign == 0)
		{
			if (token[1] == 'N')
			{
				flash_tem[GREETINGS_ENABLE_OFFSET] = 1;
			}
			else
			{
				flash_tem[GREETINGS_ENABLE_OFFSET] = 0;
			}
			
			sign++;
		}
  }
	
	erase_flash(0, TOTAL_SIZE);
	program_flash(0, flash_tem, TOTAL_SIZE);

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}


void device_filter_info_query(void)
{
	uint8_t current_size = 0;
	char string[10];
	uint8_t string_size = 0;
	
	memcpy((uint8_t*)&frame[0], (uint8_t*)&filter_name_keyword[0], filter_name_keyword_size);
	current_size += filter_name_keyword_size;
	frame[current_size] = ',';
	current_size++;
	if (filter_name_keyword_enable == 1)
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'N';
		current_size += 2;
	}
	else
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'F';
		frame[current_size+2] = 'F';
		current_size += 3;
	}
	frame[current_size] = ',';
	current_size++;
	
	for (uint8_t i=0; i<filter_phy_address_keyword_size; i++)
	{
		HexToAsc((char *)&frame[current_size], filter_phy_address_keyword[i]);
		current_size += 2;
	}
	
	frame[current_size] = ',';
	current_size++;
	if (filter_phy_address_keyword_enable == 1)
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'N';
		current_size += 2;
	}
	else
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'F';
		frame[current_size+2] = 'F';
		current_size += 3;
	}
	frame[current_size] = ',';
	current_size++;

	Int2String(filter_signal_strength, string);
	string_size = get_string_size(string, 10);
	memcpy((uint8_t*)&frame[current_size], (uint8_t*)&string, string_size);
	current_size += string_size;

	frame[current_size] = ',';
	current_size++;
	
	if (filter_signal_strength_enable == 1)
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'N';
		current_size += 2;
	}
	else
	{
		frame[current_size] = 'O';
		frame[current_size+1] = 'F';
		frame[current_size+2] = 'F';
		current_size += 3;
	}

	memcpy((uint8_t*)&frame[current_size], (uint8_t*)&suf[0], 18);

	HAL_UART_Transmit(&usart_handle, frame, current_size+18, 50);
}


void device_filter_info_set(void)
{
	uint8_t len_split_list[6];
	uint8_t current_size= 0;
	uint8_t current_loc = 0;
	
	for (int i=10; current_loc<6; i++)
	{
		if (usart_RxBuffer[i] == ',')
		{
			len_split_list[current_loc] = current_size;
			current_size = 0;
			current_loc++;
			usart_RxBuffer[i] = '\0';
		}
		else
		{
			current_size++;
		}
	}
	
	filter_name_keyword_size = len_split_list[0];
	memcpy((uint8_t*)&filter_name_keyword[0], (uint8_t*)&usart_RxBuffer[10], len_split_list[0]);
	if (len_split_list[1] == 2)
	{
		filter_name_keyword_enable = 1;
	}
	else
	{
		filter_name_keyword_enable = 0;
	}
	
	filter_phy_address_keyword_size = 0;
	for (int i=0, j=0; i<len_split_list[2]; i+=2,j++)
	{
		uint8_t tem;
		tem = AscToHex(&usart_RxBuffer[len_split_list[0]+len_split_list[1]+12+i]);
		filter_phy_address_keyword[j] = tem;
		filter_phy_address_keyword_size++;
	}
	if (len_split_list[3] == 2)
	{
		filter_phy_address_keyword_enable = 1;
	}
	else
	{
		filter_phy_address_keyword_enable = 0;
	}
	
	filter_signal_strength_size = len_split_list[4];
	filter_signal_strength = String2Int((char*)&usart_RxBuffer[len_split_list[0]+len_split_list[1]+len_split_list[2]+len_split_list[3]+14]);
	if (len_split_list[5] == 2)
	{
		filter_signal_strength_enable = 1;
	}
	else
	{
		filter_signal_strength_enable = 0;
	}

	HAL_UART_Transmit_DMA(&usart_handle, ret_ok, sizeof(ret_ok));
}
