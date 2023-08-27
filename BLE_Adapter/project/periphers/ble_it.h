#ifndef _BLE_IT_H
#define _BLE_IT_H

void scan_handle(void);
void connection_complete_event_handle(void);
void pairing_complete_event_handle(void);
void disconnection_complete_event_handle(void);
void disc_read_char_by_uuid_resp_event_handle(void);
void clt_error_resp_event_handle(void);
void notification_event_handle(void);
void pairing_completed_handle(void);

#endif
