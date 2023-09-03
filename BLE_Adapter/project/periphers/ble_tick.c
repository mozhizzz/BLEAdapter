#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_stack.h"
#include "nvm_db.h"
#include "link_layer.h"
#include "bluenrg_lp_gap.h"

#include "ble_state.h"
#include "ble_init.h"


extern int app_flags;
extern uint8_t advertising_filter;
extern uint8_t adv_data[BlE_ADVERTISE_CONTENT_SIZE];
extern Advertising_Set_Parameters_t Advertising_Set_Parameters[2];
extern uint8_t Timer_expired;
extern VTIMER_HandleType peripheralTimerHandle;
extern uint16_t update_rate;


void ModulesTick(void)
{
  HAL_VTIMER_Tick();
  BLE_STACK_Tick();
  NVMDB_Tick();
}


void Make_Connection(uint8_t filter)
{  
  tBleStatus ret;
  
  if (filter == ADV_NO_WHITE_LIST_USE)
  {
		ret = aci_gap_set_advertising_data(0, ADV_COMPLETE_DATA, sizeof(adv_data), adv_data);
		if (ret != BLE_STATUS_SUCCESS)
		{}

		ret = aci_gap_set_advertising_enable(ENABLE, 1, Advertising_Set_Parameters);
  }
}


void APP_Tick(void)
{
  if(APP_FLAG(SET_CONNECTABLE))
  {
    Make_Connection(advertising_filter);
    APP_FLAG_CLEAR(SET_CONNECTABLE);
  }
	
	if (Timer_expired) 
  {    
    Timer_expired = FALSE;
    if (HAL_VTIMER_StartTimerMs(&peripheralTimerHandle, update_rate) != BLE_STATUS_SUCCESS)
        Timer_expired = TRUE;
  }
}
