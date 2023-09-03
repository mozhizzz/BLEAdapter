#ifndef _BLE_H
#define _BLE_H


#include "ble_status.h"

#define PERIPHERAL_TIMER                                                    1
#define SECURITY_SUPPORTED  												SC_IS_SUPPORTED
#define PERIPHERAL_SECURITY_KEY 										    123456
#define MIN_KEY_SIZE 														0x07
#define MAX_KEY_SIZE 														0x10
#define SECURITY_MODE_NAME  												"PassKey Random Pin"
#define PERIPHERAL_PUBLIC_ADDRESS 									        0xe0, 0x01, 0x00, 0xE1, 0x80, 0x02
#define PERIPHERAL_DEVICE_NAME 											    'B','L','E','a','d','a','p','t','e','r'
#define MITM_MODE 															MITM_PROTECTION_REQUIRED
#define FIXED_PIN_POLICY  													DONOT_USE_FIXED_PIN_FOR_PAIRING 
#define SLAVE_BONDING_USAGE 												NO_BONDING
#define IO_CAPABILITY  														IO_CAP_KEYBOARD_ONLY
#define SECURE_CONNECTION_SUPPORT  									        SECURITY_SUPPORTED
#define KEYPRESS_NOTIFICATION  											    KEYPRESS_IS_NOT_SUPPORTED 
#define RX_CHAR_SECURITY_PERMISSIONS                                        (ATTR_PERMISSION_ENCRY_READ|ATTR_PERMISSION_AUTHEN_READ)
#define IDENTITY_ADDRESS  													0x00
#define MAX_NUM_BONDED_DEVICES 											    3
#define BLE_APPLICATION_VERSION_STRING 							            "1.0.0" 
#define BlE_ADVERTISE_CONTENT_SIZE 									        17
#define BLE_VIRTUAL_SERIAL_PORT_BUFF_SIZE 					                1024
#define BLE_NAME_SIZE 														12
#define TX_POWER_LEVEL														30


extern uint16_t update_rate;
extern uint8_t advertising_filter;
extern VTIMER_HandleType peripheralTimerHandle;


extern tBleStatus ble_init( void );

#endif
