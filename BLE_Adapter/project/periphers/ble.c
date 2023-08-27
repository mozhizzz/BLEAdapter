#include "ble_const.h"
#include "bluenrg_lp_stack.h"
#include "rf_driver_hal_power_manager.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_evb_com.h"
#include "gap_profile.h"
#include "bleplat.h"
#include "nvm_db.h"
#include "pka_manager.h"
#include "rng_manager.h"
#include "aes_manager.h"
#include "ble_controller.h"
#include "bluenrg_lp_stack.h"
#include "rf_driver_hal_def.h"

#include "ble.h"
#include "ble_service.h"
#include "ble_config.h"


uint16_t update_rate;
uint8_t advertising_filter;
VTIMER_HandleType peripheralTimerHandle;

static uint8_t Timer_expired;


static void PeripheralUpdateTimeoutCB(void *param);


extern tBleStatus ble_init( void )
{
  tBleStatus ret;
	uint16_t service_handle;
	uint16_t dev_name_char_handle;
	uint16_t appearance_char_handle;
	
	uint8_t ble_tx_power = TX_POWER_LEVEL;
	char name[] = { PERIPHERAL_DEVICE_NAME };
	uint8_t role = GAP_PERIPHERAL_ROLE | GAP_CENTRAL_ROLE;

  	ret = aci_hal_set_tx_power_level(0, (uint8_t)ble_tx_power);
  	if(ret != BLE_STATUS_SUCCESS)
		{
        return ret;
  	}

  	ret = aci_gatt_srv_init();
  	if (ret != BLE_STATUS_SUCCESS)
	{
    	return ret;
  	}

  	ret = aci_gap_init(role, 0x00, sizeof(name), IDENTITY_ADDRESS, &service_handle,  
                     &dev_name_char_handle, &appearance_char_handle);
  	if (ret != BLE_STATUS_SUCCESS)
	{
    	return ret;
  	}

  	ret = Gap_profile_set_dev_name(0, sizeof(name), (uint8_t*)&name);
  	if (ret != BLE_STATUS_SUCCESS)
	{
    	return ret;
  	}

  	ret = aci_gap_clear_security_db();
	if (ret != BLE_STATUS_SUCCESS)
	{
		return ret;
  	}

  	ret = aci_gap_set_io_capability(IO_CAPABILITY);
  	if (ret != BLE_STATUS_SUCCESS)
    {
		return ret;
  	}

	ret = aci_gap_set_authentication_requirement(SLAVE_BONDING_USAGE,
												MITM_MODE,
												SECURITY_SUPPORTED,
												KEYPRESS_NOTIFICATION,
												MIN_KEY_SIZE, 
												MAX_KEY_SIZE,
												FIXED_PIN_POLICY,
												PERIPHERAL_SECURITY_KEY);
	if(ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
	
	ret = aci_gap_set_advertising_configuration(0, 
												GAP_MODE_GENERAL_DISCOVERABLE,
												ADV_PROP_CONNECTABLE|ADV_PROP_SCANNABLE|ADV_PROP_LEGACY,
												MIN_ADV_INTERVAL, MAX_ADV_INTERVAL,
												ADV_CH_ALL,
												0,NULL,
												advertising_filter,
												0,
												LE_1M_PHY,
												0,
												LE_1M_PHY,
												0,
												0);
	if (ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
	
	ret = service_init();
	if (ret != BLE_STATUS_SUCCESS) {
		return ret;
	}

	ret = aci_gap_set_scan_configuration(DUPLICATE_FILTER_ENABLED,
                                        SCAN_ACCEPT_ALL,
                                        LE_1M_PHY, 
                                        ACTIVE_SCAN, 
                                        SCAN_INTERVAL,
                                        SCAN_WINDOW);
	if(ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
	
	ret = aci_gap_set_connection_configuration(LE_1M_PHY_BIT, MIN_CONNECT_INTERVAL, MAX_CONNECT_INTERVAL, 9, 60, 2000, 2000);
	if(ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
		
	peripheralTimerHandle.callback = PeripheralUpdateTimeoutCB;  
	ret = HAL_VTIMER_StartTimerMs(&peripheralTimerHandle, update_rate);
	if (ret != BLE_STATUS_SUCCESS) 
	{
    	return ret;
  	}
	else
	{
    	Timer_expired = FALSE;
  	}
  
  	return BLE_STATUS_SUCCESS;
}


static void PeripheralUpdateTimeoutCB(void *param)
{
  Timer_expired = TRUE;
}
