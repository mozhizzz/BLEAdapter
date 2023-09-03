#ifndef _IWDG_INIT_H
#define _IWDG_INIT_H

#define IWDG_WINDOW IWDG_WINDOW_DISABLE

#define IWDG_PRESCALER IWDG_PRESCALER_8
#define IWDG_RELOAD 0x1FFF // 1024ms 

void IWDG_Init(void);

#endif
