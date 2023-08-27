#ifndef _TASKS_H
#define _TASKS_H

#define BLE_EVT_HANDLE_TASK_PRIORITY  	( tskIDLE_PRIORITY + 2 )
#define USART1_RECEIVE_HANDLE_PRIORITY	( tskIDLE_PRIORITY + 2 )

extern void System_Task_Init(void);

#endif
