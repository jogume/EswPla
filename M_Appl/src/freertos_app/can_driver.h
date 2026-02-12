// CAN Driver Abstraction Header
#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

// CAN frame structure
typedef struct {
    uint32_t id;
    uint8_t data[64];
    uint8_t dlc;
    bool is_extended;
    uint32_t timestamp;
} can_frame_t;

// CAN statistics
typedef struct {
    uint32_t tx_count;
    uint32_t rx_count;
    uint32_t error_count;
    uint32_t tx_queue_full;
    uint32_t rx_queue_full;
} can_statistics_t;

// Function declarations
int can_init(void);
int can_send_message(uint32_t id, const uint8_t* data, uint8_t dlc);
can_statistics_t* can_get_statistics(void);

// Task function
void can_drv_task(void *pvParameters);

#endif // CAN_DRIVER_H
