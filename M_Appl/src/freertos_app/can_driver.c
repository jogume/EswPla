// CAN Driver Abstraction Layer
// Adapt this to your specific MCU and CAN peripheral

#include "can_driver.h"

#include "can_dbc_generated.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include <string.h>
#include <stdio.h>

// CAN driver configuration
#define CAN_RX_QUEUE_SIZE 32
#define CAN_TX_QUEUE_SIZE 16

// Function prototypes
extern void can_message_received(uint32_t id, const uint8_t* data, uint8_t dlc, uint32_t timestamp);
extern can_result_t can_scheduler_task(uint32_t current_time_ms);

// Internal structures
static QueueHandle_t can_rx_queue = NULL;
static QueueHandle_t can_tx_queue = NULL;
static SemaphoreHandle_t can_tx_semaphore = NULL;

// Statistics
static can_statistics_t can_stats = {0};

// Initialize CAN driver
int can_init(void) {
    // Create queues and semaphores
    can_rx_queue = xQueueCreate(CAN_RX_QUEUE_SIZE, sizeof(can_frame_t));
    can_tx_queue = xQueueCreate(CAN_TX_QUEUE_SIZE, sizeof(can_frame_t));
    can_tx_semaphore = xSemaphoreCreateBinary();
    
    if (!can_rx_queue || !can_tx_queue || !can_tx_semaphore) {
        printf("Error: CAN driver NOT initialized\n");
        return -1;
    }
    
    printf("CAN driver initialized\n");
    return 0;
}

// Send CAN message
int can_send_message(uint32_t id, const uint8_t* data, uint8_t dlc) {
    can_frame_t frame;
    frame.id = id;
    frame.dlc = dlc;
    frame.is_extended = (id > 0x7FF);
    frame.timestamp = xTaskGetTickCount();
    memcpy(frame.data, data, dlc);
    
    // Add to TX queue
    if (xQueueSend(can_tx_queue, &frame, pdMS_TO_TICKS(10)) != pdPASS) {
        can_stats.tx_queue_full++;
        return -1;
    }
    
    // TODO: Trigger hardware transmission
    // This would typically involve writing to CAN peripheral registers
    /*
    CAN_TransmitMessage(CAN0, &frame);
    */
    
    can_stats.tx_count++;
    return 0;
}


// Get received CAN message (blocking with timeout)
int can_receive_message_timeout(can_frame_t* frame, uint32_t timeout_ms) {
    if (xQueueReceive(can_rx_queue, frame, pdMS_TO_TICKS(timeout_ms)) == pdPASS) {
        return 0;
    }

    can_stats.rx_count++;
    return -1;
}



// Get CAN statistics
can_statistics_t* can_get_statistics(void) {
    return &can_stats;
}

can_frame_t req_load1 = 
{
    .id =  0x000,
    .data = {5U, 0U, 5U},
    .dlc = 64U,
    .is_extended = 0U,
};

can_frame_t req_cm30 = 
{
    .id =  0x001,
    // .data[30] = 1U,
    .dlc = 48U,
    .is_extended = 0U,
};


// CAN interrupt handler (adapt to your MCU)
void CAN0_RxIRQHandler( TimerHandle_t xTimerHandle ) {
    static uint8_t rx_idx = 0;
    ( void ) xTimerHandle;

    can_frame_t rx_frame[] = {
        req_load1,
        req_cm30
    };

    rx_frame[rx_idx].timestamp = xTaskGetTickCount();
    xQueueSend( can_rx_queue, &rx_frame[rx_idx], 0U );
    // printf( "Rx [%llu] ", xTaskGetTickCount() );
    // for(uint8_t i = 0; i <rx_frame[rx_idx].dlc; i++) printf( "%u ,", rx_frame[rx_idx].data[i]);

    rx_idx ^= 1U;
 }

 void CAN0_TxIRQHandler( TimerHandle_t xTimerHandle )
 {
    can_frame_t tx_frame;

    if (xQueueReceive(can_tx_queue, &tx_frame, pdMS_TO_TICKS(100)) == pdPASS) {
        // printf( "Tx [%llu]: ", xTaskGetTickCount() );
        // for(uint8_t i = 0; i <tx_frame.dlc; i++)  printf(" [%u],", tx_frame.data[i]);

        // printf( "\r\n");
    }

 }

// CAN RX TX processing task
void can_drv_task(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(1); // 1ms tick
    uint32_t current_time_ms = 0;
    can_frame_t frame;
    
    (void)pvParameters;

    printf("CAN RX task started\n");
    
    for (;;) {
        // Wait for received message
        if (can_receive_message_timeout(&frame, 100) == 0) {
            // Process received message using generated handler
            can_message_received(frame.id, frame.data, frame.dlc, frame.timestamp);
        }
        current_time_ms = xTaskGetTickCount();
        // Send message
        can_scheduler_task(current_time_ms);

        // Wait for next tick
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
