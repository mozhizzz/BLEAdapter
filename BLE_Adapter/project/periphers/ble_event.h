#ifndef _BLE_EVENT_H
#define _BLE_EVENT_H


enum {
    BLE_EVENT_CONNECTED,
    BLE_EVENT_DISCONNECTED,
};

typedef struct
{
    uint16_t connectHandle;
    uint8_t status;
    uint8_t role;
} ble_event_info_t;

#endif
