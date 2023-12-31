#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "tasks.h"
#include "log.h"
#include "ble_event.h"


QueueHandle_t bleEventQueue;


static void ble_evt_handle_task( void *pvParameters );
static void usart1_receive_handle_task( void *pvParameters );
static void ble_event_handle( ble_event_info_t ble_event_info );


static void ble_event_handle( ble_event_info_t ble_event_info )
{

}


static void ble_evt_handle_task( void *pvParameters )
{
    BaseType_t xStatus;
    ble_event_info_t ble_event_info;

    printLog( "ble event handle task start!\n" );
    bleEventQueue = xQueueCreate(BLE_EVENT_QUEUE_LENGTH, sizeof(ble_event_info_t));
    if ( bleEventQueue == 0 ) {
      printLog( "ble event queue created fail. " );
    }

    while(1)
    {
        xStatus = xQueueReceive(bleEventQueue, &ble_event_info, portMAX_DELAY);
        if (xStatus == pdPASS) {
            // TODO ble event handle
            ble_event_handle( ble_event_info );
        } 
    }
}

static void usart1_receive_handle_task( void *pvParameters )
{
	printLog( "usart receive handle task start!\n" );
	
	while(1)
	{
			//vTaskDelay(1);
	}
}

void vApplicationMallocFailedHook( void )
{
  /* vApplicationMallocFailedHook() will only be called if
  configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
  function that will get called if a call to pvPortMalloc() fails.
  pvPortMalloc() is called internally by the kernel whenever a task, queue,
  timer or semaphore is created.  It is also called by various parts of the
  demo application.  If heap_1.c or heap_2.c are used, then the size of the
  heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
  FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
  to query the size of free heap space that remains (although it does not
  provide information on how the remaining heap might be fragmented). */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
  /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
  to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
  task.  It is essential that code added to this hook function never attempts
  to block in any way (for example, call xQueueReceive() with a block time
  specified, or call vTaskDelay()).  If the application makes use of the
  vTaskDelete() API function (as this demo application does) then it is also
  important that vApplicationIdleHook() is permitted to return to its calling
  function, because it is the responsibility of the idle task to clean up
  memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
  ( void ) pcTaskName;
  ( void ) pxTask;
  
  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
  /* This function will be called by each tick interrupt if
  configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
  added here, but the tick hook is called from an interrupt context, so
  code must not attempt to block, and only the interrupt safe FreeRTOS API
  functions can be used (those that end in FromISR()). */
}

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

extern void System_Task_Init(void)
{
  //   BaseType_t ret;

	// ret = xTaskCreate( ble_evt_handle_task, "bleEvtTask", 650, NULL, BLE_EVT_HANDLE_TASK_PRIORITY, NULL );
  //   if ( ret != pdPASS) {
	// 		printLog("BLE evt handle task create fail: 0x%x.", ret);
  //   }

	// ret = xTaskCreate( usart1_receive_handle_task, "usart1ReceiveTask", 350, NULL, USART1_RECEIVE_HANDLE_PRIORITY, NULL );
  //   if ( ret != pdPASS) {
  //       printLog("usart1 receive handle task create fail: 0x%x.", ret);
  //   }
    

  //   vTaskStartScheduler();
}
