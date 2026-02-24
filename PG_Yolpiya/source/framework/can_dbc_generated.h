/*
 * @file can_dbc_generated.h
 * @brief MISRA C:2012 compliant CAN DBC generated header file
 * @details Generated from DBC file for automotive-grade embedded systems
 * 
 * Generated from DBC file
 * Node: nZC_test_bench_1
 * Generated on: 2025-08-27 10:59:50
 * 
 * Protocol Support:
 * - Standard IDs (11-bit): OK
 * - Extended IDs (29-bit): NO
 * - Classic CAN: OK
 * - CAN FD: OK
 * - Max Data Length: 64 bytes
 * 
 * MISRA C:2012 Compliance:
 * - Rule 8.2: Function types in prototype form with named parameters
 * - Rule 8.7: Objects defined at appropriate scope
 * - Rule 9.2: Designated initializers used
 * - Rule 17.7: Return values shall be used
 */

#ifndef CAN_DBC_GENERATED_H
#define CAN_DBC_GENERATED_H

/* MISRA C:2012 compliant includes */
#include "yolpiya.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CAN Protocol Constants - MISRA C:2012 Rule 7.2: U suffix for unsigned */
#define CAN_ID_STD_MASK     0x7FFU       /* 11-bit standard ID mask */
#define CAN_ID_EXT_MASK     0x1FFFFFFFU  /* 29-bit extended ID mask */
#define CAN_CLASSIC_MAX_DLC 8U           /* Classic CAN max data length */
#define CAN_FD_MAX_DLC      64U          /* CAN FD max data length */
#define CAN_INVALID_MSG_ID  0xFFFFFFFFU  /* Invalid message ID marker */
#define MAX_SYSTEM_TIME_MS  0xFFFFFFFEU  /* Maximum valid system time */

/* Message structure - CAN FD compatible - MISRA C:2012 Rule 8.2 compliant */
typedef struct can_message_tag
{
    uint32_t id;           /* CAN ID (11-bit or 29-bit) */
    uint8_t dlc;           /* Data Length Code (0-15 for CAN FD) */
    uint8_t len;           /* Actual data length in bytes (0-64) */
    uint8_t data[CAN_FD_MAX_DLC];  /* Data payload */
    uint8_t fd_format;     /* 1U for CAN FD, 0U for classic CAN */
    uint8_t brs;           /* Bit Rate Switch (CAN FD feature) */
    uint8_t esi;           /* Error State Indicator (CAN FD feature) */
    uint8_t is_extended;   /* 1U for 29-bit Extended ID, 0U for 11-bit Standard ID */
    uint32_t timestamp;    /* Message timestamp */
} can_message_t;

/* Result enumeration - MISRA C:2012 Rule 7.2 compliant */
typedef enum can_result_tag
{
    CAN_RESULT_OK = 0U,
    CAN_RESULT_ERROR_NULL_POINTER = 1U,
    CAN_RESULT_ERROR_INVALID_PARAM = 2U,
    CAN_RESULT_ERROR_TX_PACK = 3U,
    CAN_RESULT_ERROR_RX_TIMEOUT = 4U,
    CAN_RESULT_ERROR_SYSTEM_FAULT = 5U
} can_result_t;

/* Function pointer types - MISRA C:2012 Rule 8.2: Named parameters */
typedef can_result_t (*can_pack_function_t)(void);
typedef void (*can_message_handler_t)(const can_message_t* const msg);
typedef void (*can_timeout_callback_t)(void);

/* Fault state enumeration - MISRA C:2012 Rule 7.2 compliant */
typedef enum can_fault_state_tag
{
    CAN_FAULT_NONE = 0U,
    CAN_FAULT_NULL_POINTER = 1U,
    CAN_FAULT_INVALID_PARAMETER = 2U,
    CAN_FAULT_TX_PACK_ERROR = 3U,
    CAN_FAULT_NULL_FUNCTION_POINTER = 4U,
    CAN_FAULT_CRITICAL_MSG_TIMEOUT = 5U,
    CAN_FAULT_OVERFLOW_PROTECTION = 6U
} can_fault_state_t;

/* TX Schedule entry structure */
typedef struct can_schedule_entry_tag
{
    uint32_t id;                     /* CAN ID */
    uint32_t cycle_time_ms;          /* Cycle time in milliseconds */
    uint32_t last_sent_time;         /* Last transmission timestamp */
    uint32_t offset_ms;              /* Transmission offset */
    can_pack_function_t pack_function; /* Message packing function */
    bool enabled;                    /* Transmission enabled flag */
    uint8_t priority;                /* Message priority (0-7) */
    uint8_t is_extended;             /* Extended ID flag */
    uint8_t is_can_fd;               /* CAN FD format flag */
} can_schedule_entry_t;

/* RX Configuration structure */
typedef struct can_rx_config_tag
{
    uint32_t id;                        /* CAN ID */
    const char* const name;             /* Message name (const string) */
    uint32_t expected_cycle_ms;         /* Expected cycle time */
    uint8_t timeout_multiplier;         /* Timeout multiplier factor */
    uint32_t last_received_time;        /* Last reception timestamp */
    uint32_t rx_count;                  /* Reception counter */
    uint32_t timeout_count;             /* Timeout counter */
    uint32_t error_count;               /* Error counter */
    bool is_critical;                   /* Critical message flag */
    bool timeout_flag;                  /* Timeout status flag */
    can_message_handler_t handler;      /* Message handler function */
    can_timeout_callback_t timeout_callback; /* Timeout callback function */
    uint8_t expected_dlc;               /* Expected DLC value */
    bool validate_dlc;                  /* DLC validation enabled flag */
} can_rx_config_t;

/* Scheduler diagnostics structure */
typedef struct can_scheduler_diag_tag
{
    uint32_t tx_message_count;      /* Number of TX messages configured */
    uint32_t rx_message_count;      /* Number of RX messages configured */
    uint32_t total_faults;          /* Total fault count */
    uint32_t critical_timeouts;     /* Critical message timeouts */
} can_scheduler_diag_t;

/* System fault definitions - MISRA C:2012 Rule 7.2 compliant */
typedef enum system_fault_tag
{
    SYSTEM_FAULT_NONE = 0U,
    SYSTEM_FAULT_CAN_BUS_OFF = 1U,
    SYSTEM_FAULT_CAN_ERROR_PASSIVE = 2U,
    SYSTEM_FAULT_MESSAGE_TIMEOUT = 3U,
    SYSTEM_FAULT_MAX = 255U  /* Maximum fault value */
} system_fault_t;

/* Fault reporting functions - MISRA C:2012 Rule 8.4 compliant */

/* Function declarations - MISRA C:2012 Rule 8.4 compliant */
extern void can_set_system_fault(system_fault_t fault);
extern void can_increment_message_error_count(uint32_t msg_id);

/* Configuration tables - MISRA C:2012 Rule 8.11: Array size specified */
extern can_schedule_entry_t can_tx_message_schedule[2U];
extern can_rx_config_t can_rx_message_configs[2U];

// Message counts
#define NUM_TX_MESSAGES 2U
#define NUM_RX_MESSAGES 2U

#endif // CAN_DBC_GENERATED_H
