/**
 * @file    tle92104.h
 * @brief   TLE92104 High-Side Switch Driver - Public API
 * @details High-level driver for the Infineon TLE92104 4-channel high-side switch.
 *          Initial version supports:
 *          - Device initialization (default settings, all outputs OFF)
 *          - Watchdog servicing (must be called every ~100 ms)
 *          - Device ID reading
 *          - Error flag reading
 *          - Dummy CS / Enable pin control (stubs for simulation)
 *
 *          Uses M_hal SPI abstraction for hardware communication.
 *
 * @author  EswPla Team
 * @date    2026-02-21
 */

#ifndef TLE92104_H
#define TLE92104_H

#include "yolpiya.h"
#include "hal_types.h"

/*============================================================================*/
/* Type Definitions                                                           */
/*============================================================================*/

/**
 * @brief TLE92104 driver return codes
 */
typedef enum
{
    TLE92104_OK             = 0,     /**< Operation successful */
    TLE92104_ERROR_SPI      = 1,     /**< SPI communication error */
    TLE92104_ERROR_INIT     = 2,     /**< Initialization error */
    TLE92104_ERROR_DEVID    = 3,     /**< Device ID mismatch */
    TLE92104_ERROR_PARAM    = 4      /**< Invalid parameter */
} tle92104_status_t;

/**
 * @brief TLE92104 diagnostic flags (read from DIAG register)
 */
typedef struct
{
    bool over_temperature;            /**< Over-temperature detected */
    bool over_current_ch1;            /**< Over-current on channel 1 */
    bool over_current_ch2;            /**< Over-current on channel 2 */
    bool over_current_ch3;            /**< Over-current on channel 3 */
    bool over_current_ch4;            /**< Over-current on channel 4 */
    bool under_voltage;               /**< Under-voltage detected */
    bool temp_warning;                /**< Temperature warning */
} tle92104_diag_t;

/*============================================================================*/
/* Public Function Prototypes                                                 */
/*============================================================================*/

/**
 * @brief Initialize the TLE92104 device
 * @details Performs the following sequence:
 *          1. Assert CS (dummy)
 *          2. Initialize SPI via HAL
 *          3. Read and verify device ID
 *          4. Set default configuration (all outputs OFF, watchdog enabled)
 *          5. Deassert CS (dummy)
 * @return TLE92104_OK on success, error code otherwise
 */
tle92104_status_t hs_init(void);

/**
 * @brief Service the TLE92104 watchdog
 * @details Must be called periodically (every ~100 ms) to prevent
 *          the TLE92104 internal watchdog from triggering a reset.
 *          Writes the watchdog trigger bit via SPI.
 * @return TLE92104_OK on success, TLE92104_ERROR_SPI on failure
 */
tle92104_status_t hs_service_watchdog(void);

/**
 * @brief Read the TLE92104 device ID
 * @param[out] p_device_id  Pointer to store the device ID value
 * @return TLE92104_OK on success, error code otherwise
 */
tle92104_status_t hs_get_device_id(uint8_t* p_device_id);

/**
 * @brief Read the TLE92104 diagnostic flags
 * @param[out] p_diag  Pointer to diagnostic structure to fill
 * @return TLE92104_OK on success, TLE92104_ERROR_SPI on failure
 */
tle92104_status_t hs_get_error_flags(tle92104_diag_t* p_diag);

/**
 * @brief Assert CS line (dummy - for simulation / placeholder)
 * @details On real hardware, this would drive the SPI chip-select LOW.
 *          In simulation, just prints a debug message.
 */
void hs_cs_assert(void);

/**
 * @brief Deassert CS line (dummy - for simulation / placeholder)
 * @details On real hardware, this would drive the SPI chip-select HIGH.
 *          In simulation, just prints a debug message.
 */
void hs_cs_deassert(void);

/**
 * @brief Assert Enable pin (dummy - for simulation / placeholder)
 * @details On real hardware, this would drive the TLE92104 enable pin HIGH.
 *          In simulation, just prints a debug message.
 */
void hs_enable_assert(void);

/**
 * @brief Deassert Enable pin (dummy - for simulation / placeholder)
 * @details On real hardware, this would drive the TLE92104 enable pin LOW.
 *          In simulation, just prints a debug message.
 */
void hs_enable_deassert(void);

#endif /* TLE92104_H */
