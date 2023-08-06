#ifndef _BLE_INIT_H
#define _BLE_INIT_H

#define PERIPHERAL_TIMER 1

#define SECURITY_SUPPORTED  												SC_IS_SUPPORTED

#define PERIPHERAL_SECURITY_KEY 										123456

#define MIN_KEY_SIZE 																0x07
   
#define MAX_KEY_SIZE 																0x10

#define SECURITY_MODE_NAME  												"PassKey Random Pin"

#define PERIPHERAL_PUBLIC_ADDRESS 									0xe0, 0x01, 0x00, 0xE1, 0x80, 0x02

#define PERIPHERAL_DEVICE_NAME 											'B','L','E','a','d','a','p','t','e','r'

#define MITM_MODE 																	MITM_PROTECTION_REQUIRED

#define FIXED_PIN_POLICY  													DONOT_USE_FIXED_PIN_FOR_PAIRING 

#define SLAVE_BONDING_USAGE 												NO_BONDING

#define IO_CAPABILITY  															IO_CAP_KEYBOARD_ONLY

#define SECURE_CONNECTION_SUPPORT  									SECURITY_SUPPORTED

#define KEYPRESS_NOTIFICATION  											KEYPRESS_IS_NOT_SUPPORTED 

#define RX_CHAR_SECURITY_PERMISSIONS (ATTR_PERMISSION_ENCRY_READ|ATTR_PERMISSION_AUTHEN_READ)

#define IDENTITY_ADDRESS  													0x00

#define MAX_NUM_BONDED_DEVICES 											3

#define BLE_APPLICATION_VERSION_STRING 							"1.0.0" 

#define BlE_ADVERTISE_CONTENT_SIZE 									17

#define BLE_VIRTUAL_SERIAL_PORT_BUFF_SIZE 					1024

#define BLE_NAME_SIZE 															12

#define BLE_MASTER_ROLE										0
#define BLE_SLAVE_ROLE										1

#define MANUFACTURER_DATA_MAX_SIZE 				11
#define MANUFACTURER_ID_SIZE   						2
#define FILTER_NAME_KEYWORD_SIZE					10
#define FILTER_PHY_ADDRESS_KEYWORD_SIZE		10
#define FILRER_SIGNAL_STRENGTH_SIZE				10
#define MAX_DEVICE_SIZE										256
#define MAX_SCAN_SIZE											400	

#include "bluenrg_lp_events.h"

typedef struct
{
	uint32_t serial_num;
	uint8_t address_type;
	int8_t RSSI;
	uint8_t device_name_len;
	uint8_t address[6];
	uint8_t device_name[32];
} Device_InfoDef;

typedef struct
{
	uint8_t address_type;
	int8_t RSSI;
	uint8_t dev_info_len;
	uint8_t address[6];
	uint8_t dev_info[64];
} Scan_InfoDef;

void BLE_Init(void);
void Clear_Security_Database(void);
void PeripheralUpdateTimeoutCB(void *param);

#endif
