#ifndef _FLASH_H
#define _FLASH_H

#include "rf_driver_hal.h"

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define FLASH_USER_START_ADDR   (FLASH_END_ADDR - FLASH_PAGE_SIZE - 0xF)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     (FLASH_END_ADDR - 0xF)  /* End @ of user Flash area */

#define ADAPTER_MODE_SIZE												4
#define ADAPTER_MASTER_ROLE_ENABLE_SIZE					4
#define ADAPTER_SLAVE_ROLE_ENABLE_SIZE					8
#define DEFAULT_ADDRESS_SIZE	     							8
#define DEFAULT_ADDRESS_TYPE_SIZE	     					4
#define DEFAULT_ADDRESS_PINCODE_SIZE	 					8
#define DEFAULT_ADDRESS_ENABLE_SIZE             4
#define LAST_TIME_ADDRESS_SIZE									8
#define LAST_TIME_ADDRESS_TYPE_SIZE							4
#define LAST_TIME_ADDRESS_PINCODE_SIZE					8
#define USART_BAUD_RATE_SIZE										4
#define USART_DATA_LEN_SIZE											4
#define USART_STOP_BITS_LEN_SIZE								4
#define USART_PARITY_SIZE												4
#define BLE_TX_POWER_SIZE												4
#define	BLE_PASSWORD_PAIR_ENABLE_SIZE						4
#define BLE_ADV_INTER_MIN_SIZE									4
#define BLE_ADV_INTER_MAX_SIZE									4
#define BLE_SCAN_INTER_SIZE											4
#define BLE_SCAN_WINDOW_SIZE										4
#define	BLE_CONN_INTER_MIN_SIZE								 	4
#define	BLE_CONN_INTER_MAX_SIZE								 	4
#define BLE_TRAN_TRAN_TX_SERV_UUID_SIZE					16
#define BLE_TRAN_TRAN_TX_SERV_UUID_LEN_SIZE			4
#define BLE_TRAN_TRAN_TX_CHAR_UUID_SIZE					16
#define BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_SIZE			4
#define BLE_TRAN_TRAN_RX_SERV_UUID_SIZE					16
#define BLE_TRAN_TRAN_RX_SERV_UUID_LEN_SIZE			4
#define BLE_TRAN_TRAN_RX_CHAR_UUID_SIZE					16
#define BLE_TRAN_TRAN_RX_CHAR_UUID_LEN_SIZE			4
#define MANU_DATA_SIZE													16
#define MANU_DATA_LEN_SIZE											4
#define MANU_ID_SIZE														4
#define GREETINGS_SIZE													20
#define GREETINGS_LEN_SIZE											4
#define GREETINGS_ENABLE_SIZE										4
#define BLE_NAME_SIZE														12
#define BLE_NAME_LEN_SIZE												4

#define ADAPTER_MODE_OFFSET											16
#define ADAPTER_MASTER_ROLE_ENABLE_OFFSET				20
#define ADAPTER_SLAVE_ROLE_ENABLE_OFFSET				24
#define DEFAULT_ADDRESS_OFFSET     							32
#define DEFAULT_ADDRESS_TYPE_OFFSET     				40

#define DEFAULT_ADDRESS_ENABLE_OFFSET           48
#define LAST_TIME_ADDRESS_OFFSET								56
#define LAST_TIME_ADDRESS_TYPE_OFFSET						64
#define LAST_TIME_ADDRESS_PINCODE_OFFSET				68
#define DEFAULT_ADDRESS_PINCODE_OFFSET  				76
#define USART_BAUD_RATE_OFFSET									84
#define USART_DATA_LEN_OFFSET										88
#define USART_STOP_BITS_LEN_OFFSET							92
#define USART_PARITY_OFFSET											96
#define BLE_TX_POWER_OFFSET											100
#define	BLE_PASSWORD_PAIR_ENABLE_OFFSET					104
#define BLE_ADV_INTER_MIN_OFFSET								108
#define BLE_ADV_INTER_MAX_OFFSET								112
#define BLE_SCAN_INTER_OFFSET										116
#define BLE_SCAN_WINDOW_OFFSET									116+4
#define	BLE_CONN_INTER_MIN_OFFSET								116+8
#define	BLE_CONN_INTER_MAX_OFFSET								116+8+4
#define BLE_TRAN_TRAN_TX_SERV_UUID_OFFSET				120+8+4
#define BLE_TRAN_TRAN_TX_SERV_UUID_LEN_OFFSET		136+8+4
#define BLE_TRAN_TRAN_TX_CHAR_UUID_OFFSET				140+8+4
#define BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_OFFSET		156+8+4
#define BLE_TRAN_TRAN_RX_SERV_UUID_OFFSET				160+8+4
#define BLE_TRAN_TRAN_RX_SERV_UUID_LEN_OFFSET		176+8+4
#define BLE_TRAN_TRAN_RX_CHAR_UUID_OFFSET				180+8+4
#define BLE_TRAN_TRAN_RX_CHAR_UUID_LEN_OFFSET		196+8+4
#define MANU_DATA_OFFSET												200+8+4
#define MANU_DATA_LEN_OFFSET										208+16+4
#define MANU_ID_OFFSET													208+16+4+4
#define GREETINGS_OFFSET												216+8+4+4+4
#define GREETINGS_LEN_OFFSET										216+8+4+4+20+4
#define GREETINGS_ENABLE_OFFSET									244+4+4+4+4
#define BLE_NAME_OFFSET													236+12+4+4+4+4
#define BLE_NAME_LEN_OFFSET											236+12+4+4+4+4+12

#define TOTAL_SIZE (ADAPTER_MODE_SIZE \
										+ADAPTER_MASTER_ROLE_ENABLE_SIZE \
										+ADAPTER_SLAVE_ROLE_ENABLE_SIZE \
										+DEFAULT_ADDRESS_SIZE \
										+DEFAULT_ADDRESS_TYPE_SIZE \
										+DEFAULT_ADDRESS_PINCODE_SIZE \
										+DEFAULT_ADDRESS_ENABLE_SIZE \
										+LAST_TIME_ADDRESS_SIZE \
										+LAST_TIME_ADDRESS_TYPE_SIZE \
										+LAST_TIME_ADDRESS_PINCODE_SIZE \
										+USART_BAUD_RATE_SIZE \
										+USART_DATA_LEN_SIZE \
										+USART_STOP_BITS_LEN_SIZE \
										+USART_PARITY_SIZE \
										+BLE_TX_POWER_SIZE \
										+BLE_PASSWORD_PAIR_ENABLE_SIZE \
										+BLE_ADV_INTER_MIN_SIZE \
										+BLE_ADV_INTER_MAX_SIZE \
										+BLE_SCAN_INTER_SIZE \
										+BLE_SCAN_WINDOW_SIZE \
										+BLE_CONN_INTER_MIN_SIZE \
										+BLE_CONN_INTER_MAX_SIZE \
										+BLE_TRAN_TRAN_TX_SERV_UUID_SIZE \
										+BLE_TRAN_TRAN_TX_SERV_UUID_LEN_SIZE \
										+BLE_TRAN_TRAN_TX_CHAR_UUID_SIZE \
										+BLE_TRAN_TRAN_TX_CHAR_UUID_LEN_SIZE \
										+BLE_TRAN_TRAN_RX_SERV_UUID_SIZE \
										+BLE_TRAN_TRAN_RX_SERV_UUID_LEN_SIZE \
										+BLE_TRAN_TRAN_RX_CHAR_UUID_SIZE \
										+BLE_TRAN_TRAN_RX_CHAR_UUID_LEN_SIZE \
										+MANU_DATA_SIZE \
										+MANU_DATA_LEN_SIZE \
										+GREETINGS_SIZE \
										+GREETINGS_ENABLE_SIZE \
										+BLE_NAME_SIZE \
										+MANU_ID_SIZE \
										+GREETINGS_LEN_SIZE \
										+BLE_NAME_LEN_SIZE \
										+24)

void read_flash(uint32_t start_address_offset, uint8_t *read_buff, uint32_t buff_size);
void erase_flash(uint32_t start_address_offset, uint32_t buff_len);
void program_flash(uint32_t start_address_offset, uint8_t *program_buff, uint32_t buff_size);
uint32_t GetPage(uint32_t Addr);

#endif
