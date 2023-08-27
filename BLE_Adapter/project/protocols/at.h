#ifndef _AT_H
#define _AT_H

#define AT_MODE          0
#define TRAN_TRAN_MODE   1

#define MASTER_ROLE      0
#define SLAVE_ROLE       1

#define ENTER_AT_MODE    				"AT..."
#define EXIT_AT_MODE		 				"AT+EXIT"
#define AT_RESET				 				"AT+RESET"
#define COM_INFO_QUERY   				"AT+UART?"
#define COM_INFO_CONFIG  				"AT+UART="
#define LOCAL_BLE_NAME_QUERY  	"AT+NAME?"
#define LOCAL_BLE_NAME_CONFIG  	"AT+NAME="
#define LOCAL_MAC_QUERY					"AT+MAC?"
#define TX_POWER_QUERY					"AT+TPL?"
#define TX_POWER_CONFIG					"AT+TPL="
#define PASSWORD_ENABLE_QUERY		"AT+PASEN?"
#define PASSWORD_ENABLE_CONFIG	"AT+PASEN="
#define START_SCAN_CONFIG				"AT+SCAN="
#define SN_CONNECT_CONFIG				"AT+LINK="
#define MAC_CONNECT_CONFIG			"AT+CONN="
#define DEFAULT_DEVICE_QUERY		"AT+CONADD?"
#define DEFAULT_DEVICE_CONFIG		"AT+CONADD="
#define ROLE_QUERY							"AT+ROLE?"
#define ROLE_CONFIG							"AT+ROLE="
#define TRAN_TRAN_QUERY					"AT+SERVICE?"
#define TRAN_TRAN_CONFIG				"AT+SERVICE="
#define MANUFACTURER_QUERY			"AT+MANU?"
#define MANUFACTURER_CONFIG			"AT+MANU="
#define ADV_INTERVAL_QUERY			"AT+ADVINTER?"
#define ADV_INTERVAL_CONFIG			"AT+ADVINTER="
#define SCAN_INTERVAL_QUERY			"AT+SCANTIME?"
#define SCAN_INTERVAL_CONFIG		"AT+SCANTIME="
#define CONNECT_INTERVAL_QUERY	"AT+CONNINTER?"
#define CONNECT_INTERVAL_CONFIG	"AT+CONNINTER="
#define HELLO_QUERY							"AT+HELLO?"
#define HELLO_CONFIG						"AT+HELLO="
#define DEVICE_FILTER_QUERY			"AT+FILTER?"
#define DEVICE_FILTER_CONFIG		"AT+FILTER="

#define GREETINGS_SIZE				20
uint8_t get_string_size(char* string, uint8_t string_len);
int String2Int(char *p);
char* Int2String(int num,char *str);
void HexToAsc(char *string, uint8_t num);
void enter_AT_command_mode(void);
void exit_AT_command_mode(void);
void soft_reset(void);
void serial_port_info_query(void);
void serial_port_info_set(void);
void local_ble_name_query(void);
void local_ble_name_set(void);
void local_mac_address_query(void);
void transimit_power_query(void);
void transimit_power_set(void);
void password_pair_enable_query(void);
void password_pair_enable_set(void);
void start_search_device(void);
void direct_connect_by_sn(void);
void direct_connect_by_mac_address(void);
void default_connect_device_params_query(void);
void default_connect_device_params_set(void);
void role_control_query(void);
void role_control_set(void);
void transparent_transimission_service_info_query(void);
void transparent_transimission_service_info_set(void);
void manufacturer_info_query(void);
void manufacturer_info_set(void);
void broadcast_interval_query(void);
void broadcast_interval_set(void);
void scan_interval_query(void);
void scan_interval_set(void);
void connect_interval_query(void);
void connect_interval_set(void);
void greetings_query(void);
void greetings_set(void);
void device_filter_info_query(void);
void device_filter_info_set(void);

#endif
