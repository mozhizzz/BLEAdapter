#include <string.h>

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

#include "ble_init.h"
#include "ble_state.h"
#include "ble_config.h"
#include "ble_db.h"
#include "flash.h"


extern int app_flags;
extern uint8_t advertising_filter;
extern uint8_t adv_data[30];
extern Advertising_Set_Parameters_t Advertising_Set_Parameters[1];
extern VTIMER_HandleType peripheralTimerHandle;
extern uint16_t update_rate;
extern uint8_t Timer_expired;
NO_INIT(uint32_t dyn_alloc_a[DYNAMIC_MEMORY_SIZE>>2]);
extern uint16_t advertisiting_handle;

extern uint8_t flash_tem[TOTAL_SIZE];


void ModulesInit(void)
{
  BLE_STACK_InitTypeDef BLE_STACK_InitParams = BLE_STACK_INIT_PARAMETERS;
  
  LL_AHB_EnableClock(LL_AHB_PERIPH_PKA|LL_AHB_PERIPH_RNG);
  
  if(BLE_STACK_Init(&BLE_STACK_InitParams) != HAL_OK)
	{}
  
  BLECNTR_InitGlobal();
  
  HAL_VTIMER_InitType VTIMER_InitStruct = {HS_STARTUP_TIME, INITIAL_CALIBRATION, CALIBRATION_INTERVAL};
  HAL_VTIMER_Init(&VTIMER_InitStruct);
  
  BLEPLAT_Init();
  
  if (PKAMGR_Init() == PKAMGR_ERROR)
  {
      while(1);
  }
  if (RNGMGR_Init() != RNGMGR_SUCCESS)
  {
      while(1);
  }
  
  AESMGR_Init();
}


tBleStatus DeviceInit(void)
{
	tBleStatus ret;
	uint16_t service_handle;
	uint16_t dev_name_char_handle;
	uint16_t appearance_char_handle;
	uint8_t name[] = {PERIPHERAL_DEVICE_NAME};
	uint8_t role = GAP_PERIPHERAL_ROLE|GAP_CENTRAL_ROLE;
	uint8_t bdaddr[] = {PERIPHERAL_PUBLIC_ADDRESS};
	uint32_t ble_tx_power;
	uint32_t adv_interval_min;
	uint32_t adv_interval_max;
	uint32_t scan_interval;
	uint32_t scan_window;
	uint32_t connect_interval_min;
	uint32_t connect_interval_max;
	static uint8_t ServiceUUID_Scan[18]= {0x11,0x06,0x8a,0x97,0xf7,0xc0,0x85,0x06,0x11,0xe3,0xba,0xa7,0x08,0x00,0x2,0x0c,0x9a,0x66};

  	ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, bdaddr);
  	if(ret != BLE_STATUS_SUCCESS)
	{
    return ret;
  	}
	
	memcpy((uint8_t*)&ble_tx_power, (uint8_t*)&flash_tem[BLE_TX_POWER_OFFSET], BLE_TX_POWER_SIZE);
	
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

  	ret = Gap_profile_set_dev_name(0, sizeof(name), name);
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
	
	memcpy((uint8_t*)&adv_interval_min, (uint8_t*)&flash_tem[BLE_ADV_INTER_MIN_OFFSET], BLE_ADV_INTER_MIN_SIZE);
	memcpy((uint8_t*)&adv_interval_max, (uint8_t*)&flash_tem[BLE_ADV_INTER_MAX_OFFSET], BLE_ADV_INTER_MAX_SIZE);
	
	ret = aci_gap_set_advertising_configuration(0, 
												GAP_MODE_GENERAL_DISCOVERABLE,
												ADV_PROP_CONNECTABLE|ADV_PROP_SCANNABLE|ADV_PROP_LEGACY,
												adv_interval_min, adv_interval_max,
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
	
	ret = Add_Service();
	if (ret != BLE_STATUS_SUCCESS) {
		return ret;
	}
	  
	ret = aci_gap_set_scan_response_data(advertisiting_handle, 18, ServiceUUID_Scan);
	if(ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
	
	memcpy((uint8_t*)&scan_interval, (uint8_t*)&flash_tem[BLE_SCAN_INTER_OFFSET], BLE_SCAN_INTER_SIZE);
	memcpy((uint8_t*)&scan_window, (uint8_t*)&flash_tem[BLE_SCAN_WINDOW_OFFSET], BLE_SCAN_WINDOW_SIZE);
	
	ret = aci_gap_set_scan_configuration(DUPLICATE_FILTER_ENABLED,
																			 SCAN_ACCEPT_ALL,
																			 LE_1M_PHY, 
																			 ACTIVE_SCAN, 
																			 scan_interval,
																			 scan_window);
	if(ret != BLE_STATUS_SUCCESS)
	{
		return ret;
	}
	
	memcpy((uint8_t*)&connect_interval_min, (uint8_t*)&flash_tem[BLE_CONN_INTER_MIN_OFFSET], BLE_CONN_INTER_MIN_SIZE);
	memcpy((uint8_t*)&connect_interval_max, (uint8_t*)&flash_tem[BLE_CONN_INTER_MAX_OFFSET], BLE_CONN_INTER_MAX_SIZE);
	
	ret = aci_gap_set_connection_configuration(LE_1M_PHY_BIT, connect_interval_min, connect_interval_max, 9, 60, 2000, 2000);
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


void PeripheralUpdateTimeoutCB(void *param)
{
  Timer_expired = TRUE;
}


void BLE_Init(void)
{
	tBleStatus ret;

	ModulesInit();

	ret = DeviceInit();
	if (ret != BLE_STATUS_SUCCESS) {}
}
