#include "bluenrg_lp_api.h"


#define AT_COMMAND_SERVICE_UUID   0x93,0xbe,0xa2,0xe9,0x22,0x85,0x0e,0xb2,0xa4,0xc1,0x7b,0x92,0xdd,0xbc,0x33,0xb2
#define TRAN_TRAN_SERVICE_UUID    0xFF,0xE0
#define TRAN_TRAN_CHAR_UUID       0xFF,0xE1
#define AT_COMMAND_CHAR_UUID   		0x93,0xbe,0xa3,0xe9,0x22,0x85,0x0e,0xb2,0xa4,0xc1,0x7b,0x92,0xdd,0xbc,0x33,0xb2


extern uint16_t at_command_handle;
extern uint16_t tran_tran_handle;
extern const uint16_t tran_tran_service_uuid;
extern const uint16_t tran_tran_char_uuid;


BLE_GATT_SRV_CCCD_DECLARE(at_command,
                          1,
                          BLE_GATT_SRV_CCCD_PERM_DEFAULT,
                          BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG);

BLE_GATT_SRV_CCCD_DECLARE(tran_tran,
                          1,
                          BLE_GATT_SRV_CCCD_PERM_DEFAULT,
                          BLE_GATT_SRV_OP_MODIFIED_EVT_ENABLE_FLAG);
													
													
static ble_gatt_chr_def_t at_command_chars[] = {
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_NOTIFY | BLE_GATT_SRV_CHAR_PROP_WRITE | BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_128(AT_COMMAND_CHAR_UUID),
				.descrs = {
            .descrs_p = &BLE_GATT_SRV_CCCD_DEF_NAME(at_command),
            .descr_count = 1U,
        },
    },
};


static ble_gatt_chr_def_t tran_tran_chars[] = {
    {
        .properties = BLE_GATT_SRV_CHAR_PROP_READ | BLE_GATT_SRV_CHAR_PROP_NOTIFY | BLE_GATT_SRV_CHAR_PROP_WRITE | BLE_GATT_SRV_CHAR_PROP_WRITE_NO_RESP,
        .permissions = BLE_GATT_SRV_PERM_NONE,
        .min_key_size = BLE_GATT_SRV_MAX_ENCRY_KEY_SIZE,
        .uuid = BLE_UUID_INIT_16(TRAN_TRAN_CHAR_UUID),
				.descrs = {
            .descrs_p = &BLE_GATT_SRV_CCCD_DEF_NAME(tran_tran),
            .descr_count = 1U,
        },
    },
};


static ble_gatt_srv_def_t at_command_service = {
   .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
   .uuid = BLE_UUID_INIT_128(AT_COMMAND_SERVICE_UUID),
   .chrs = {
       .chrs_p = at_command_chars,
       .chr_count = 1U,
   },
};


static ble_gatt_srv_def_t tran_tran_service = {
   .type = BLE_GATT_SRV_PRIMARY_SRV_TYPE,
   .uuid = BLE_UUID_INIT_16(TRAN_TRAN_SERVICE_UUID),
   .chrs = {
       .chrs_p = tran_tran_chars,
       .chr_count = 1U,
   },
};


tBleStatus Add_Service(void)
{
	tBleStatus ret;
	
  ret = aci_gatt_srv_add_service(&at_command_service);
	if (ret != BLE_STATUS_SUCCESS)
	{
			return ret;
	}
  ret = aci_gatt_srv_add_service(&tran_tran_service);
	if (ret != BLE_STATUS_SUCCESS)
	{
			return ret;
	}
	
	at_command_handle = aci_gatt_srv_get_char_decl_handle(&at_command_chars[0]);
  tran_tran_handle = aci_gatt_srv_get_char_decl_handle(&tran_tran_chars[0]);
	
  return BLE_STATUS_SUCCESS;
}
