/**
 * @file    tle92104.c
 * @brief   TLE92104 High-Side Switch Driver Implementation
 * @details Uses M_hal SPI abstraction for all hardware communication.
 *          Initial version: default settings, all outputs OFF, watchdog + device ID.
 * @author  EswPla Team
 * @date    2026-02-21
 */

#include "yolpiya.h"
#include "tle92104.h"
#include "tle92104_regs.h"
#include "hal_spi.h"

/*============================================================================*/
/* Private Definitions                                                        */
/*============================================================================*/

/** @brief SPI device index used for TLE92104 */
#define TLE92104_SPI_DEVICE         (0u)

/** @brief SPI clock speed for TLE92104 (4 MHz max per datasheet) */
#define TLE92104_SPI_BAUDRATE       (4000000u)

/*============================================================================*/
/* Private Variables                                                          */
/*============================================================================*/

/** @brief Driver initialization state */
static bool g_tle92104_initialized = false;

/** @brief Watchdog toggle state (alternates each service call) */
static uint8_t g_wdg_toggle = 0u;

/*============================================================================*/
/* Private Function Prototypes                                                */
/*============================================================================*/

static uint16_t tle92104_calc_parity(uint16_t frame);
static tle92104_status_t tle92104_spi_transfer(uint16_t tx_frame, uint16_t* p_rx_frame);
static tle92104_status_t tle92104_write_reg(uint8_t addr, uint8_t data);
static tle92104_status_t tle92104_read_reg(uint8_t addr, uint8_t* p_data);

/*============================================================================*/
/* Private Functions                                                          */
/*============================================================================*/

/**
 * @brief Calculate even parity for SPI frame
 * @param frame 16-bit frame (parity bit position should be 0)
 * @return Frame with parity bit set in bit 1
 */
static uint16_t tle92104_calc_parity(uint16_t frame)
{
    uint16_t temp = frame;
    uint16_t parity = 0u;
    uint8_t i;

    /* Calculate parity over bits 15:2 */
    temp = (frame >> 2u) & 0x3FFFu;
    for (i = 0u; i < 14u; i++)
    {
        parity ^= (temp & 0x0001u);
        temp >>= 1u;
    }

    /* Set even parity in bit 1 */
    frame = (frame & ~TLE92104_PARITY_MASK) | (parity << TLE92104_PARITY_SHIFT);

    return frame;
}

/**
 * @brief Perform a single 16-bit SPI transfer with the TLE92104
 * @param tx_frame  16-bit frame to transmit
 * @param p_rx_frame Pointer to receive the 16-bit response
 * @return TLE92104_OK on success, TLE92104_ERROR_SPI on failure
 */
static tle92104_status_t tle92104_spi_transfer(uint16_t tx_frame, uint16_t* p_rx_frame)
{
    hal_status_t hal_ret;
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];

    /* Add parity to frame */
    tx_frame = tle92104_calc_parity(tx_frame);

    /* MSB first: byte 0 = high byte, byte 1 = low byte */
    tx_buf[0] = (uint8_t)(tx_frame >> 8u);
    tx_buf[1] = (uint8_t)(tx_frame & 0xFFu);

    /* Assert CS */
    hs_cs_assert();

    /* Perform SPI transfer */
    hal_ret = hal_spi_transfer(TLE92104_SPI_DEVICE, tx_buf, rx_buf, 2u, 100u);

    /* Deassert CS */
    hs_cs_deassert();

    if (hal_ret != HAL_OK)
    {
        return TLE92104_ERROR_SPI;
    }

    if (p_rx_frame != NULL)
    {
        *p_rx_frame = ((uint16_t)rx_buf[0] << 8u) | (uint16_t)rx_buf[1];
    }

    return TLE92104_OK;
}

/**
 * @brief Write a register on the TLE92104
 * @param addr Register address (4-bit)
 * @param data Data byte to write
 * @return TLE92104_OK on success, TLE92104_ERROR_SPI on failure
 */
static tle92104_status_t tle92104_write_reg(uint8_t addr, uint8_t data)
{
    uint16_t frame;
    uint16_t rx_frame;

    frame = TLE92104_BUILD_WRITE_FRAME(addr, data);
    return tle92104_spi_transfer(frame, &rx_frame);
}

/**
 * @brief Read a register from the TLE92104
 * @param addr Register address (4-bit)
 * @param p_data Pointer to store the read data byte
 * @return TLE92104_OK on success, TLE92104_ERROR_SPI on failure
 */
static tle92104_status_t tle92104_read_reg(uint8_t addr, uint8_t* p_data)
{
    uint16_t frame;
    uint16_t rx_frame;
    tle92104_status_t status;

    /* First transfer: send read command (response contains previous register data) */
    frame = TLE92104_BUILD_READ_FRAME(addr);
    status = tle92104_spi_transfer(frame, &rx_frame);
    if (status != TLE92104_OK)
    {
        return status;
    }

    /* Second transfer: dummy read to clock out the response for our address */
    frame = TLE92104_BUILD_READ_FRAME(addr);
    status = tle92104_spi_transfer(frame, &rx_frame);
    if (status != TLE92104_OK)
    {
        return status;
    }

    if (p_data != NULL)
    {
        *p_data = TLE92104_EXTRACT_DATA(rx_frame);
    }

    return TLE92104_OK;
}

/*============================================================================*/
/* Public Functions                                                           */
/*============================================================================*/

tle92104_status_t hs_init(void)
{
    hal_spi_config_t spi_cfg;
    hal_status_t hal_ret;
    tle92104_status_t status;
    uint8_t dev_id = 0u;

    printf("[TLE92104] Initializing...\n");

    /* Enable the device (dummy) */
    hs_enable_assert();

    /* Configure SPI: Mode 1, 16-bit, MSB first, 4 MHz */
    spi_cfg.baudrate   = TLE92104_SPI_BAUDRATE;
    spi_cfg.mode       = HAL_SPI_MODE_1;
    spi_cfg.bit_order  = HAL_SPI_BIT_ORDER_MSB_FIRST;
    spi_cfg.data_bits  = 16u;

    hal_ret = hal_spi_init(TLE92104_SPI_DEVICE, &spi_cfg);
    if (hal_ret != HAL_OK)
    {
        printf("[TLE92104] ERROR: SPI init failed (%d)\n", (int)hal_ret);
        return TLE92104_ERROR_INIT;
    }

    /* Read device ID to verify communication */
    status = tle92104_read_reg(TLE92104_REG_DEVID, &dev_id);
    if (status != TLE92104_OK)
    {
        printf("[TLE92104] ERROR: Cannot read device ID\n");
        return TLE92104_ERROR_SPI;
    }

    printf("[TLE92104] Device ID: 0x%02X (expected 0x%02X)\n",
           (unsigned)dev_id, (unsigned)TLE92104_DEVICE_ID);

    if (dev_id != TLE92104_DEVICE_ID)
    {
        printf("[TLE92104] WARNING: Device ID mismatch (continuing anyway)\n");
        /* Don't fail - socket sim may return different ID initially */
    }

    /* Set default config: all outputs OFF */
    status = tle92104_write_reg(TLE92104_REG_CTRL1, TLE92104_CTRL1_ALL_OFF);
    if (status != TLE92104_OK)
    {
        printf("[TLE92104] ERROR: Cannot write CTRL1\n");
        return TLE92104_ERROR_SPI;
    }

    /* Enable watchdog */
    status = tle92104_write_reg(TLE92104_REG_WDG, TLE92104_WDG_EN);
    if (status != TLE92104_OK)
    {
        printf("[TLE92104] ERROR: Cannot enable watchdog\n");
        return TLE92104_ERROR_SPI;
    }

    g_tle92104_initialized = true;
    g_wdg_toggle = 0u;

    printf("[TLE92104] Initialized successfully (all outputs OFF, WDG enabled)\n");

    return TLE92104_OK;
}

tle92104_status_t hs_service_watchdog(void)
{
    tle92104_status_t status;
    uint8_t wdg_val;

    if (!g_tle92104_initialized)
    {
        return TLE92104_ERROR_INIT;
    }

    /* Toggle watchdog trigger bit */
    g_wdg_toggle ^= TLE92104_WDG_TRIGGER;
    wdg_val = TLE92104_WDG_EN | g_wdg_toggle;

    status = tle92104_write_reg(TLE92104_REG_WDG, wdg_val);
    if (status != TLE92104_OK)
    {
        printf("[TLE92104] ERROR: Watchdog service failed\n");
        return TLE92104_ERROR_SPI;
    }

    printf("[TLE92104] Watchdog serviced (toggle=0x%02X)\n", (unsigned)g_wdg_toggle);

    return TLE92104_OK;
}

tle92104_status_t hs_get_device_id(uint8_t* p_device_id)
{
    if (p_device_id == NULL)
    {
        return TLE92104_ERROR_PARAM;
    }

    if (!g_tle92104_initialized)
    {
        return TLE92104_ERROR_INIT;
    }

    return tle92104_read_reg(TLE92104_REG_DEVID, p_device_id);
}

tle92104_status_t hs_get_error_flags(tle92104_diag_t* p_diag)
{
    uint8_t diag_raw = 0u;
    tle92104_status_t status;

    if (p_diag == NULL)
    {
        return TLE92104_ERROR_PARAM;
    }

    if (!g_tle92104_initialized)
    {
        return TLE92104_ERROR_INIT;
    }

    status = tle92104_read_reg(TLE92104_REG_DIAG, &diag_raw);
    if (status != TLE92104_OK)
    {
        return TLE92104_ERROR_SPI;
    }

    p_diag->over_temperature = (bool)((diag_raw & TLE92104_DIAG_OT) != 0u);
    p_diag->over_current_ch1 = (bool)((diag_raw & TLE92104_DIAG_OC1) != 0u);
    p_diag->over_current_ch2 = (bool)((diag_raw & TLE92104_DIAG_OC2) != 0u);
    p_diag->over_current_ch3 = (bool)((diag_raw & TLE92104_DIAG_OC3) != 0u);
    p_diag->over_current_ch4 = (bool)((diag_raw & TLE92104_DIAG_OC4) != 0u);
    p_diag->under_voltage    = (bool)((diag_raw & TLE92104_DIAG_UV) != 0u);
    p_diag->temp_warning     = (bool)((diag_raw & TLE92104_DIAG_TW) != 0u);

    printf("[TLE92104] Diag: raw=0x%02X (OT=%d, UV=%d, TW=%d)\n",
           (unsigned)diag_raw,
           (int)p_diag->over_temperature,
           (int)p_diag->under_voltage,
           (int)p_diag->temp_warning);

    return TLE92104_OK;
}

void hs_cs_assert(void)
{
    /* Dummy CS assert - on real HW: drive GPIO low */
    /* printf("[TLE92104] CS asserted (LOW)\n"); */
}

void hs_cs_deassert(void)
{
    /* Dummy CS deassert - on real HW: drive GPIO high */
    /* printf("[TLE92104] CS deasserted (HIGH)\n"); */
}

void hs_enable_assert(void)
{
    /* Dummy Enable assert - on real HW: drive enable pin high */
    printf("[TLE92104] Enable pin ASSERTED (device active)\n");
}

void hs_enable_deassert(void)
{
    /* Dummy Enable deassert - on real HW: drive enable pin low */
    printf("[TLE92104] Enable pin DEASSERTED (device inactive)\n");
}
