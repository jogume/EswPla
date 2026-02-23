/**
 * @file    tle92104_regs.h
 * @brief   TLE92104 Register Map and Bit Definitions
 * @details Based on Infineon TLE92104 datasheet - 4-channel high-side switch
 *          SPI frame: 16-bit, MSB first, Mode 1 or 3, max 4 MHz
 *          Frame format: [CMD(2) | ADDR(4) | DATA(8) | PARITY(1) | RESERVED(1)]
 * @author  EswPla Team
 * @date    2026-02-21
 */

#ifndef TLE92104_REGS_H
#define TLE92104_REGS_H

/*============================================================================*/
/* SPI Frame Format                                                           */
/*============================================================================*/

/**
 * @brief SPI Command Bits (bits 15:14)
 */
#define TLE92104_CMD_READ           (0x00u)  /**< Read register */
#define TLE92104_CMD_WRITE          (0x01u)  /**< Write register */
#define TLE92104_CMD_SHIFT          (14u)
#define TLE92104_CMD_MASK           (0xC000u)

/**
 * @brief SPI Address Bits (bits 13:10)
 */
#define TLE92104_ADDR_SHIFT         (10u)
#define TLE92104_ADDR_MASK          (0x3C00u)

/**
 * @brief SPI Data Bits (bits 9:2)
 */
#define TLE92104_DATA_SHIFT         (2u)
#define TLE92104_DATA_MASK          (0x03FCu)

/**
 * @brief Parity bit (bit 1) - even parity over bits 15:2
 */
#define TLE92104_PARITY_SHIFT       (1u)
#define TLE92104_PARITY_MASK        (0x0002u)

/*============================================================================*/
/* Register Addresses                                                         */
/*============================================================================*/

#define TLE92104_REG_CTRL1          (0x00u)  /**< Control Register 1 - Channel enable/disable */
#define TLE92104_REG_CTRL2          (0x01u)  /**< Control Register 2 - Slew rate / config */
#define TLE92104_REG_CTRL3          (0x02u)  /**< Control Register 3 - Additional config */
#define TLE92104_REG_CFG            (0x03u)  /**< Configuration Register */
#define TLE92104_REG_DIAG           (0x04u)  /**< Diagnosis Register */
#define TLE92104_REG_WDG            (0x05u)  /**< Watchdog Register */
#define TLE92104_REG_ICR            (0x06u)  /**< Interrupt Control Register */
#define TLE92104_REG_HWCR           (0x07u)  /**< Hardware Config Register */
#define TLE92104_REG_DEVID          (0x08u)  /**< Device Identification Register */

/*============================================================================*/
/* CTRL1 Register Bit Definitions                                             */
/*============================================================================*/

#define TLE92104_CTRL1_OUT1_EN      (0x01u)  /**< Output 1 enable */
#define TLE92104_CTRL1_OUT2_EN      (0x02u)  /**< Output 2 enable */
#define TLE92104_CTRL1_OUT3_EN      (0x04u)  /**< Output 3 enable */
#define TLE92104_CTRL1_OUT4_EN      (0x08u)  /**< Output 4 enable */
#define TLE92104_CTRL1_ALL_OFF      (0x00u)  /**< All outputs off */

/*============================================================================*/
/* WDG Register Bit Definitions                                               */
/*============================================================================*/

#define TLE92104_WDG_TRIGGER        (0x01u)  /**< Watchdog trigger bit */
#define TLE92104_WDG_EN             (0x80u)  /**< Watchdog enable */

/*============================================================================*/
/* DIAG Register Bit Definitions                                              */
/*============================================================================*/

#define TLE92104_DIAG_OT            (0x01u)  /**< Over-temperature flag */
#define TLE92104_DIAG_OC1           (0x02u)  /**< Over-current channel 1 */
#define TLE92104_DIAG_OC2           (0x04u)  /**< Over-current channel 2 */
#define TLE92104_DIAG_OC3           (0x08u)  /**< Over-current channel 3 */
#define TLE92104_DIAG_OC4           (0x10u)  /**< Over-current channel 4 */
#define TLE92104_DIAG_UV            (0x20u)  /**< Under-voltage flag */
#define TLE92104_DIAG_TW            (0x40u)  /**< Temperature warning */

/*============================================================================*/
/* Device ID                                                                  */
/*============================================================================*/

#define TLE92104_DEVICE_ID          (0x5Au)  /**< Expected Device ID value */

/*============================================================================*/
/* Helper Macros                                                              */
/*============================================================================*/

/**
 * @brief Build a 16-bit SPI write frame
 * @param addr Register address (4-bit)
 * @param data Data byte (8-bit)
 * @return 16-bit SPI frame (parity not yet set)
 */
#define TLE92104_BUILD_WRITE_FRAME(addr, data) \
    (uint16_t)(((uint16_t)(TLE92104_CMD_WRITE) << TLE92104_CMD_SHIFT) | \
               ((uint16_t)((addr) & 0x0Fu) << TLE92104_ADDR_SHIFT) | \
               ((uint16_t)((data) & 0xFFu) << TLE92104_DATA_SHIFT))

/**
 * @brief Build a 16-bit SPI read frame
 * @param addr Register address (4-bit)
 * @return 16-bit SPI frame (parity not yet set)
 */
#define TLE92104_BUILD_READ_FRAME(addr) \
    (uint16_t)(((uint16_t)(TLE92104_CMD_READ) << TLE92104_CMD_SHIFT) | \
               ((uint16_t)((addr) & 0x0Fu) << TLE92104_ADDR_SHIFT))

/**
 * @brief Extract data byte from SPI response frame
 * @param frame 16-bit SPI response frame
 * @return Extracted 8-bit data value
 */
#define TLE92104_EXTRACT_DATA(frame) \
    (uint8_t)(((frame) & TLE92104_DATA_MASK) >> TLE92104_DATA_SHIFT)

/**
 * @brief Extract address from SPI frame
 * @param frame 16-bit SPI frame
 * @return Extracted 4-bit address
 */
#define TLE92104_EXTRACT_ADDR(frame) \
    (uint8_t)(((frame) & TLE92104_ADDR_MASK) >> TLE92104_ADDR_SHIFT)

#endif /* TLE92104_REGS_H */
