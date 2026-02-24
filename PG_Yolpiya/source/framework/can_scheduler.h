#ifndef CAN_SCHEDULER_H
#define CAN_SCHEDULER_H

#include "can_dbc_generated.h"
#ifdef FREERTOS_ENABLED
#include "FreeRTOS.h"
#include "task.h"
#endif

void can_message_received(uint32_t id, const uint8_t* data, uint8_t dlc, uint32_t timestamp);

#endif // CAN_SCHEDULER_H
