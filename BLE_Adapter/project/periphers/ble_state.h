#ifndef __BLE_STATE_H
#define __BLE_STATE_H

#ifdef __cplusplus
 extern "C" {
#endif

#define CONNECTED               0x01
#define SET_CONNECTABLE         0x02
#define NOTIFICATIONS_ENABLED   0x04
#define CONN_PARAM_UPD_SENT     0x08
#define L2CAP_PARAM_UPD_SENT    0x10
#define TX_BUFFER_FULL          0x20

#define START_GAP_SLAVE_SECURITY_REQUEST    0x100
#define HCI_ENCRYPTION_CHANGE_EVENT_FLAG    0x200 
#define ACI_GAP_PASS_KEY_REQ_EVENT_FLAG     0x400
#define ACI_GAP_PAIRING_COMPLETE_EVENT_FLAG 0x800
#define START_TERMINATE_LINK_FLAG           0x1000
#define PRINT_CONNECTED_DATA                0x2000
#define DO_NOTIFICATIONS_FLAG               0x4000

#define START_CONFIRM_NUMERIC_VALUE         0x4000

#define APP_FLAG(flag) (app_flags & flag)

#define APP_FLAG_SET(flag) (app_flags |= flag)
#define APP_FLAG_CLEAR(flag) (app_flags &= ~flag)

#ifdef __cplusplus
}
#endif

#endif
