#ifndef _BLE_CONFIG_H
#define _BLE_CONFIG_H

#include "bluenrg_lp_stack.h"
#include "stack_user_cfg.h"

#define MIN_NUM_LINK_CONF             3
#define NUM_APP_GATT_SERVICES_CONF   3  
#define NUM_APP_GATT_ATTRIBUTES_CONF 7 

#define NUM_LINKS               (MIN_NUM_LINK_CONF)

#define NUM_ADV_SETS_CONF                       (2U) 
#define NUM_AUX_SCAN_SLOTS_CONF                 (0U)
#define NUM_SYNC_SLOTS_CONF                     (0U)
#define WHITE_LIST_SIZE_LOG2_CONF               (3U)
#define L2CAP_MPS_CONF                          (247U)
#define NUM_L2CAP_COCS_CONF                     (0U)
#define MAX_NUM_CTE_ANTENNA_IDS                 (0U)
#define MAX_NUM_CTE_IQ_SAMPLES                  (0U)

#define ISR0_FIFO_SIZE   (1024)
#define ISR1_FIFO_SIZE   (1024)
#define USER_FIFO_SIZE   (1024)

#define NUM_GATT_ATTRIBUTES     (NUM_APP_GATT_SERVICES_CONF + NUM_APP_GATT_ATTRIBUTES_CONF)

#define MAX_ATT_MTU_CONF        (BLE_STACK_DEFAULT_ATT_MTU) 

#define OPT_MBLOCKS_CONF		(100)  

#define MBLOCKS_COUNT           (BLE_STACK_MBLOCKS_CALC(MAX_ATT_MTU_CONF, NUM_LINKS) + OPT_MBLOCKS_CONF)

#define NUM_OF_CONCURRENT_GATT_CLIENT_PROC_CONF              (1)

#define DYNAMIC_MEMORY_SIZE (BLE_STACK_TOTAL_BUFFER_SIZE(NUM_LINKS,NUM_GATT_ATTRIBUTES,NUM_OF_CONCURRENT_GATT_CLIENT_PROC_CONF,MBLOCKS_COUNT,\
                                                         NUM_ADV_SETS_CONF,NUM_AUX_SCAN_SLOTS_CONF,WHITE_LIST_SIZE_LOG2_CONF,NUM_L2CAP_COCS_CONF,\
                                                         NUM_SYNC_SLOTS_CONF, MAX_NUM_CTE_ANTENNA_IDS, MAX_NUM_CTE_IQ_SAMPLES, \
                                                         ISR0_FIFO_SIZE, ISR1_FIFO_SIZE, USER_FIFO_SIZE)) 

#define MAX_CONN_EVENT_LENGTH_CONF 0xFFFFFFFF

#define CALIBRATION_INTERVAL_CONF   10000

#if defined CONFIG_HW_LS_RO  

#define SLEEP_CLOCK_ACCURACY        500

#define INITIAL_CALIBRATION         TRUE
#define CALIBRATION_INTERVAL        CALIBRATION_INTERVAL_CONF

#elif defined CONFIG_HW_LS_XTAL

#define SLEEP_CLOCK_ACCURACY        100

#define INITIAL_CALIBRATION         FALSE
#define CALIBRATION_INTERVAL        0

#endif

#define HS_STARTUP_TIME 320

#define TX_POWER                    0
#define MIN_ADV_INTERVAL            120
#define MAX_ADV_INTERVAL            160
#define SCAN_INTERVAL               120
#define SCAN_WINDOW                 160
#define MIN_CONNECT_INTERVAL        120
#define MAX_CONNECT_INTERVAL        160


extern uint8_t hot_table_radio_config[];

#define BLE_STACK_INIT_PARAMETERS {                                             \
    .BLEStartRamAddress = (uint8_t*)dyn_alloc_a,                                \
    .TotalBufferSize = DYNAMIC_MEMORY_SIZE,                                     \
    .NumAttrRecords = NUM_GATT_ATTRIBUTES,                                      \
    .MaxNumOfClientProcs = NUM_OF_CONCURRENT_GATT_CLIENT_PROC_CONF,             \
    .NumOfLinks = NUM_LINKS,                                                    \
    .NumBlockCount = MBLOCKS_COUNT,                                             \
    .ATT_MTU = MAX_ATT_MTU_CONF,                                                \
    .MaxConnEventLength = MAX_CONN_EVENT_LENGTH_CONF,                           \
    .SleepClockAccuracy = SLEEP_CLOCK_ACCURACY,                                 \
    .NumOfAdvDataSet = NUM_ADV_SETS_CONF,                                       \
    .NumOfAuxScanSlots = NUM_AUX_SCAN_SLOTS_CONF,                               \
    .WhiteListSizeLog2 = WHITE_LIST_SIZE_LOG2_CONF,                             \
    .L2CAP_MPS = L2CAP_MPS_CONF,                                                \
    .L2CAP_NumChannels = NUM_L2CAP_COCS_CONF,                                   \
    .NumOfSyncSlots = NUM_SYNC_SLOTS_CONF,                                      \
    .CTE_MaxNumAntennaIDs = MAX_NUM_CTE_ANTENNA_IDS,                            \
    .CTE_MaxNumIQSamples = MAX_NUM_CTE_IQ_SAMPLES , 		         	\
    .isr0_fifo_size = ISR0_FIFO_SIZE,                                           \
    .isr1_fifo_size = ISR1_FIFO_SIZE,                                           \
    .user_fifo_size = USER_FIFO_SIZE                                            \
}

#endif
