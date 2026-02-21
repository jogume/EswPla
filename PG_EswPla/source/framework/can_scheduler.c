/*
 * CAN Message Scheduler Task Implementation
 * MISRA C:2012 compliant with automotive safety features
 * 
 * @brief Manages transmission and reception of CAN messages
 * @requirements ISO 26262 ASIL-D compatible design
 * @misra_rules 17.7, 1.3, 8.7, 2.2
 */

#include "yolpiya.h"
#include "can_dbc_generated.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

// CAN message reception callback (called from CAN ISR or polling)
void can_message_received(uint32_t id, const uint8_t* data, uint8_t dlc, uint32_t timestamp) {
    // Find matching RX configuration
    for (int i = 0; i < NUM_RX_MESSAGES; i++) {
        can_rx_config_t* config = &can_rx_message_configs[i];
        
        if (config->id == id) {
            // Validate DLC if required
            if (config->validate_dlc && dlc != config->expected_dlc) {
                printf("DLC mismatch for %s: expected %d, got %d\n", 
                       config->name, config->expected_dlc, dlc);
                config->error_count++;
                return;
            }
            
            // Update reception statistics
            config->last_received_time = timestamp;
            config->rx_count++;
            config->timeout_flag = false;
            
            // Create message structure
            can_message_t msg = {
                .id = id,
                .dlc = dlc,
                .timestamp = timestamp
            };
            memcpy(msg.data, data, dlc);
            
            // Call message handler
            if (config->handler) {
                config->handler(&msg);
            }
            
            // printf("Received %s (ID: 0x%03X, DLC: %d)\n", 
            //        config->name, id, dlc);
            return;
        }
    }
    
    printf("Unknown CAN message received: ID 0x%03X\n", id);
}

/*
 * @brief Main CAN scheduler task for automotive application
 * @param[in] current_time_ms Current system time in milliseconds
 * @return can_result_t Operation result status
 * @pre System clock must be initialized
 * @post All scheduled messages processed according to timing requirements
 * @note MISRA C:2012 Rule 17.7 - Return value must be checked
 */
can_result_t can_scheduler_task(uint32_t current_time_ms)
{
    can_result_t result = CAN_RESULT_OK;
    uint32_t messages_processed = 0U;  /* MISRA C:2012 Rule 7.2 - U suffix */
    can_fault_state_t fault_state = CAN_FAULT_NONE;
    
    /* MISRA C:2012 Rule 1.3 - Check for undefined behavior */
    if ((current_time_ms == 0U) || (current_time_ms > MAX_SYSTEM_TIME_MS))
    {
        // can_report_fault(CAN_FAULT_INVALID_PARAMETER, __FILE__, __LINE__);
        return CAN_RESULT_ERROR_INVALID_PARAM;
    }
    
    /* Process transmission messages - MISRA C:2012 Rule 8.7 */
    for (uint32_t msg_idx = 0U; msg_idx < NUM_TX_MESSAGES; msg_idx++)
    {
        can_schedule_entry_t *const p_entry = &can_tx_message_schedule[msg_idx];
        
        /* MISRA C:2012 Rule 1.3 - Validate pointer before use */
        if (p_entry == NULL)
        {
            fault_state = CAN_FAULT_NULL_POINTER;
            result = CAN_RESULT_ERROR_NULL_POINTER;
            break;  /* Early exit on fault */
        }
        
        /* Skip disabled messages */
        if (!p_entry->enabled)
        {
            continue;
        }
        
        /* Check if message is due for transmission */
        const uint32_t time_since_last = current_time_ms - p_entry->last_sent_time;
        const uint32_t adjusted_cycle = p_entry->cycle_time_ms + p_entry->offset_ms;
        
        /* MISRA C:2012 Rule 1.3 - Prevent overflow in time calculation */
        if ((current_time_ms < p_entry->last_sent_time) || (time_since_last >= adjusted_cycle))
        {
            /* Call pack function - MISRA C:2012 Rule 17.7 */
            if (p_entry->pack_function != NULL)
            {
                const can_result_t pack_result = p_entry->pack_function();
                if (pack_result != CAN_RESULT_OK)
                {
                    // can_report_fault(CAN_FAULT_TX_PACK_ERROR, __FILE__, __LINE__);
                    result = pack_result;  /* Preserve error */
                }
                else
                {
                    p_entry->last_sent_time = current_time_ms;
                    messages_processed++;
                }
            }
            else
            {
                fault_state = CAN_FAULT_NULL_FUNCTION_POINTER;
                result = CAN_RESULT_ERROR_NULL_POINTER;
            }
        }
    }

    
    /* Process reception message timeouts - MISRA C:2012 Rule 8.7 */
    for (uint32_t msg_idx = 0U; msg_idx < NUM_RX_MESSAGES; msg_idx++)
    {
        can_rx_config_t *const p_config = &can_rx_message_configs[msg_idx];
        
        /* MISRA C:2012 Rule 1.3 - Validate pointer */
        if (p_config == NULL)
        {
            fault_state = CAN_FAULT_NULL_POINTER;
            result = CAN_RESULT_ERROR_NULL_POINTER;
            break;
        }
        
        /* Calculate timeout threshold */
        const uint32_t timeout_ms = p_config->expected_cycle_ms * p_config->timeout_multiplier;
        const uint32_t time_since_rx = current_time_ms - p_config->last_received_time;
        
        /* Check for message timeout - MISRA C:2012 Rule 1.3 overflow protection */
        if ((current_time_ms >= p_config->last_received_time) && (time_since_rx > timeout_ms))
        {
            if (!p_config->timeout_flag)
            {
                p_config->timeout_flag = true;
                p_config->timeout_count++;
                
                /* Call timeout callback if available */
                if (p_config->timeout_callback != NULL)
                {
                    p_config->timeout_callback();
                }
                
                /* Report critical message timeouts */
                if (p_config->is_critical)
                {
                    // can_report_fault(CAN_FAULT_CRITICAL_MSG_TIMEOUT, __FILE__, __LINE__);
                    fault_state = CAN_FAULT_CRITICAL_MSG_TIMEOUT;
                }
            }
        }
    }

    
    /* Update global fault state - MISRA C:2012 Rule 8.7 */
    if (fault_state != CAN_FAULT_NONE)
    {
        // can_update_global_fault_state(fault_state);
    }
    
    /* MISRA C:2012 Rule 17.7 - Always return status */
    return result;
}

/*
 * @brief Get CAN scheduler diagnostic information
 * @param[out] p_diag_info Pointer to diagnostic structure to fill
 * @return can_result_t Operation result
 * @pre p_diag_info must be valid pointer
 * @post Diagnostic information populated with current status
 */
can_result_t can_get_scheduler_diagnostics(can_scheduler_diag_t *const p_diag_info)
{
    /* MISRA C:2012 Rule 1.3 - Input validation */
    if (p_diag_info == NULL)
    {
        return CAN_RESULT_ERROR_NULL_POINTER;
    }
    
    /* Initialize structure - MISRA C:2012 Rule 9.1 */
    p_diag_info->tx_message_count = NUM_TX_MESSAGES;
    p_diag_info->rx_message_count = NUM_RX_MESSAGES;
    // p_diag_info->total_faults = can_get_total_fault_count();
    p_diag_info->critical_timeouts = 0U;
    
    /* Count critical message timeouts */
#if NUM_RX_MESSAGES > 0
    for (uint32_t i = 0U; i < NUM_RX_MESSAGES; i++)
    {
        if ((can_rx_message_configs[i].is_critical) && (can_rx_message_configs[i].timeout_flag))
        {
            p_diag_info->critical_timeouts++;
        }
    }
#endif
    
    return CAN_RESULT_OK;
}
