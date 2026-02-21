// Generated DBC Pack/Unpack Functions
// Generated from: Unknown

#include "yolpiya.h"
#include "dbc_pack_unpack.h"

// Message pack functions
#include "dbc_messages.h"

// Pack Diagnose_Communication message
uint8_t diagnose_communication_pack(uint8_t* data, const diagnose_communication_t* msg, uint8_t size) {
    if (size < 64) return 0;
    
    memset(data, 0, 64);
    
    // Pack Diagnose_CAN_1
    uint64_t raw_diagnose_can_1 = (uint64_t)(msg->diagnose_can_1);
    raw_diagnose_can_1 &= 0xFFULL;
    data[0] |= ((raw_diagnose_can_1 << 0) & 0xFF);
    
    // Pack Diagnose_CAN_2
    uint64_t raw_diagnose_can_2 = (uint64_t)(msg->diagnose_can_2);
    raw_diagnose_can_2 &= 0xFFULL;
    data[1] |= ((raw_diagnose_can_2 << 0) & 0xFF);
    
    // Pack Diagnose_CAN_3
    uint64_t raw_diagnose_can_3 = (uint64_t)(msg->diagnose_can_3);
    raw_diagnose_can_3 &= 0xFFULL;
    data[2] |= ((raw_diagnose_can_3 << 0) & 0xFF);
    
    // Pack Diagnose_Eth100_1
    uint64_t raw_diagnose_eth100_1 = (uint64_t)(msg->diagnose_eth100_1);
    raw_diagnose_eth100_1 &= 0xFFULL;
    data[3] |= ((raw_diagnose_eth100_1 << 0) & 0xFF);
    
    // Pack Diagnose_Eth100_2
    uint64_t raw_diagnose_eth100_2 = (uint64_t)(msg->diagnose_eth100_2);
    raw_diagnose_eth100_2 &= 0xFFULL;
    data[4] |= ((raw_diagnose_eth100_2 << 0) & 0xFF);
    
    // Pack Diagnose_Eth100_3
    uint64_t raw_diagnose_eth100_3 = (uint64_t)(msg->diagnose_eth100_3);
    raw_diagnose_eth100_3 &= 0xFFULL;
    data[5] |= ((raw_diagnose_eth100_3 << 0) & 0xFF);
    
    // Pack Diagnose_Eth10_1
    uint64_t raw_diagnose_eth10_1 = (uint64_t)(msg->diagnose_eth10_1);
    raw_diagnose_eth10_1 &= 0xFFULL;
    data[6] |= ((raw_diagnose_eth10_1 << 0) & 0xFF);
    
    // Pack Diagnose_Eth10_2
    uint64_t raw_diagnose_eth10_2 = (uint64_t)(msg->diagnose_eth10_2);
    raw_diagnose_eth10_2 &= 0xFFULL;
    data[7] |= ((raw_diagnose_eth10_2 << 0) & 0xFF);
    
    // Pack Diagnose_Eth2_5G_1
    uint64_t raw_diagnose_eth2_5g_1 = (uint64_t)(msg->diagnose_eth2_5g_1);
    raw_diagnose_eth2_5g_1 &= 0xFFULL;
    data[8] |= ((raw_diagnose_eth2_5g_1 << 0) & 0xFF);
    
    // Pack Diagnose_Eth2_5G_2
    uint64_t raw_diagnose_eth2_5g_2 = (uint64_t)(msg->diagnose_eth2_5g_2);
    raw_diagnose_eth2_5g_2 &= 0xFFULL;
    data[9] |= ((raw_diagnose_eth2_5g_2 << 0) & 0xFF);
    
    // Pack Diagnose_Eth2_5G_3
    uint64_t raw_diagnose_eth2_5g_3 = (uint64_t)(msg->diagnose_eth2_5g_3);
    raw_diagnose_eth2_5g_3 &= 0xFFULL;
    data[10] |= ((raw_diagnose_eth2_5g_3 << 0) & 0xFF);
    
    // Pack Diagnose_LIN_1
    uint64_t raw_diagnose_lin_1 = (uint64_t)(msg->diagnose_lin_1);
    raw_diagnose_lin_1 &= 0xFFULL;
    data[11] |= ((raw_diagnose_lin_1 << 0) & 0xFF);
    
    // Pack Diagnose_LIN_2
    uint64_t raw_diagnose_lin_2 = (uint64_t)(msg->diagnose_lin_2);
    raw_diagnose_lin_2 &= 0xFFULL;
    data[12] |= ((raw_diagnose_lin_2 << 0) & 0xFF);
    
    // Pack Diagnose_LIN_3
    uint64_t raw_diagnose_lin_3 = (uint64_t)(msg->diagnose_lin_3);
    raw_diagnose_lin_3 &= 0xFFULL;
    data[13] |= ((raw_diagnose_lin_3 << 0) & 0xFF);
    
    // Pack Diagnose_LIN_4
    uint64_t raw_diagnose_lin_4 = (uint64_t)(msg->diagnose_lin_4);
    raw_diagnose_lin_4 &= 0xFFULL;
    data[14] |= ((raw_diagnose_lin_4 << 0) & 0xFF);
    
    // Pack Diagnose_PSI5_1
    uint64_t raw_diagnose_psi5_1 = (uint64_t)(msg->diagnose_psi5_1);
    raw_diagnose_psi5_1 &= 0xFFULL;
    data[15] |= ((raw_diagnose_psi5_1 << 0) & 0xFF);
    
    // Pack Diagnose_PSI5_2
    uint64_t raw_diagnose_psi5_2 = (uint64_t)(msg->diagnose_psi5_2);
    raw_diagnose_psi5_2 &= 0xFFULL;
    data[16] |= ((raw_diagnose_psi5_2 << 0) & 0xFF);
    
    // printf( "diagnose_communication_pack\n\r");
    
    return 64;
}

// Pack Diagnose_Audio message
uint8_t diagnose_audio_pack(uint8_t* data, const diagnose_audio_t* msg, uint8_t size) {
    if (size < 4) return 0;
    
    memset(data, 0, 4);
    
    // Pack Diagnose_Audio_channel1
    uint64_t raw_diagnose_audio_channel1 = (uint64_t)(msg->diagnose_audio_channel1);
    raw_diagnose_audio_channel1 &= 0xFFULL;
    data[0] |= ((raw_diagnose_audio_channel1 << 0) & 0xFF);
    
    // Pack Diagnose_Audio_channel2
    uint64_t raw_diagnose_audio_channel2 = (uint64_t)(msg->diagnose_audio_channel2);
    raw_diagnose_audio_channel2 &= 0xFFULL;
    data[1] |= ((raw_diagnose_audio_channel2 << 0) & 0xFF);
    
    // Pack Diagnose_Audio_channel3
    uint64_t raw_diagnose_audio_channel3 = (uint64_t)(msg->diagnose_audio_channel3);
    raw_diagnose_audio_channel3 &= 0xFFULL;
    data[2] |= ((raw_diagnose_audio_channel3 << 0) & 0xFF);
    
    // Pack Diagnose_Audio_channel4
    uint64_t raw_diagnose_audio_channel4 = (uint64_t)(msg->diagnose_audio_channel4);
    raw_diagnose_audio_channel4 &= 0xFFULL;
    data[3] |= ((raw_diagnose_audio_channel4 << 0) & 0xFF);
    
    
    return 4;
}
// Pack Sample_Array message

// Pack States_Load36_Load42 message

// Pack States_CMC1_ROOMLAMP1 message

// Pack Digital_IO message

// Pack Requests_CM30_ROOMLAMP1 message

// Pack Requests_Load1_Reverse5 message

// Pack SW_Version message

// Pack Analog_inputs message

// Pack Voltage message

// Pack States_HB7_Reserve5 message

// Message unpack functions

// Unpack Diagnose_Communication message

// Unpack Diagnose_Audio message

// Unpack Sample_Array message

// Unpack States_Load36_Load42 message

// Unpack States_CMC1_ROOMLAMP1 message

// Unpack Digital_IO message

// Unpack Requests_CM30_ROOMLAMP1 message
int requests_cm30_roomlamp1_unpack(requests_cm30_roomlamp1_t* msg, const uint8_t* data, uint8_t dlc) {
    if (dlc != 48) return -1;
    
    // Unpack LM00_Output_Request
    uint64_t raw_lm00_output_request = 0;
    raw_lm00_output_request |= ((uint64_t)((data[30] >> 0) & 0xFF) << 0);
    if (raw_lm00_output_request & 0x80ULL) {
        raw_lm00_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->lm00_output_request = (int64_t)raw_lm00_output_request;
    
    // Unpack ROOMLAMP1_Output_Request
    uint64_t raw_roomlamp1_output_request = 0;
    raw_roomlamp1_output_request |= ((uint64_t)((data[31] >> 0) & 0xFF) << 0);
    if (raw_roomlamp1_output_request & 0x80ULL) {
        raw_roomlamp1_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->roomlamp1_output_request = (int64_t)raw_roomlamp1_output_request;
    
    // Unpack Retry_Control_Reset
    uint64_t raw_retry_control_reset = 0;
    raw_retry_control_reset |= ((uint64_t)((data[32] >> 0) & 0x01) << 0);
    if (raw_retry_control_reset & 0x1ULL) {
        raw_retry_control_reset |= ~((1ULL << 1) - 1); // Sign extend
    }
    msg->retry_control_reset = (int64_t)raw_retry_control_reset;
    
    
    return 0;
}

// Unpack Requests_Load1_Reverse5 message
int requests_load1_reverse5_unpack(requests_load1_reverse5_t* msg, const uint8_t* data, uint8_t dlc) {
    if (dlc != 64) return -1;
    
    // Unpack Load1_Output_Request
    uint64_t raw_load1_output_request = 0;
    raw_load1_output_request |= ((uint64_t)((data[0] >> 0) & 0xFF) << 0);
    if (raw_load1_output_request & 0x80ULL) {
        raw_load1_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load1_output_request = (int64_t)raw_load1_output_request;
    
    // Unpack Load2_Output_Request
    uint64_t raw_load2_output_request = 0;
    raw_load2_output_request |= ((uint64_t)((data[1] >> 0) & 0xFF) << 0);
    if (raw_load2_output_request & 0x80ULL) {
        raw_load2_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load2_output_request = (int64_t)raw_load2_output_request;
    
    // Unpack Load3_Output_Request
    uint64_t raw_load3_output_request = 0;
    raw_load3_output_request |= ((uint64_t)((data[2] >> 0) & 0xFF) << 0);
    if (raw_load3_output_request & 0x80ULL) {
        raw_load3_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load3_output_request = (int64_t)raw_load3_output_request;
    
    // Unpack Load4_Output_Request
    uint64_t raw_load4_output_request = 0;
    raw_load4_output_request |= ((uint64_t)((data[3] >> 0) & 0xFF) << 0);
    if (raw_load4_output_request & 0x80ULL) {
        raw_load4_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load4_output_request = (int64_t)raw_load4_output_request;
    
    // Unpack Load5_Output_Request
    uint64_t raw_load5_output_request = 0;
    raw_load5_output_request |= ((uint64_t)((data[4] >> 0) & 0xFF) << 0);
    if (raw_load5_output_request & 0x80ULL) {
        raw_load5_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load5_output_request = (int64_t)raw_load5_output_request;
    
    // Unpack Load6_Output_Request
    uint64_t raw_load6_output_request = 0;
    raw_load6_output_request |= ((uint64_t)((data[5] >> 0) & 0xFF) << 0);
    if (raw_load6_output_request & 0x80ULL) {
        raw_load6_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load6_output_request = (int64_t)raw_load6_output_request;
    
    // Unpack Load7_Output_Request
    uint64_t raw_load7_output_request = 0;
    raw_load7_output_request |= ((uint64_t)((data[6] >> 0) & 0xFF) << 0);
    if (raw_load7_output_request & 0x80ULL) {
        raw_load7_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load7_output_request = (int64_t)raw_load7_output_request;
    
    // Unpack Load8_Output_Request
    uint64_t raw_load8_output_request = 0;
    raw_load8_output_request |= ((uint64_t)((data[7] >> 0) & 0xFF) << 0);
    if (raw_load8_output_request & 0x80ULL) {
        raw_load8_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load8_output_request = (int64_t)raw_load8_output_request;
    
    // Unpack Load9_Output_Request
    uint64_t raw_load9_output_request = 0;
    raw_load9_output_request |= ((uint64_t)((data[8] >> 0) & 0xFF) << 0);
    if (raw_load9_output_request & 0x80ULL) {
        raw_load9_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load9_output_request = (int64_t)raw_load9_output_request;
    
    // Unpack Load10_Output_Request
    uint64_t raw_load10_output_request = 0;
    raw_load10_output_request |= ((uint64_t)((data[9] >> 0) & 0xFF) << 0);
    if (raw_load10_output_request & 0x80ULL) {
        raw_load10_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load10_output_request = (int64_t)raw_load10_output_request;
    
    // Unpack Load11_Output_Request
    uint64_t raw_load11_output_request = 0;
    raw_load11_output_request |= ((uint64_t)((data[10] >> 0) & 0xFF) << 0);
    if (raw_load11_output_request & 0x80ULL) {
        raw_load11_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load11_output_request = (int64_t)raw_load11_output_request;
    
    // Unpack Load12_Output_Request
    uint64_t raw_load12_output_request = 0;
    raw_load12_output_request |= ((uint64_t)((data[11] >> 0) & 0xFF) << 0);
    if (raw_load12_output_request & 0x80ULL) {
        raw_load12_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load12_output_request = (int64_t)raw_load12_output_request;
    
    // Unpack Load13_Output_Request
    uint64_t raw_load13_output_request = 0;
    raw_load13_output_request |= ((uint64_t)((data[12] >> 0) & 0xFF) << 0);
    if (raw_load13_output_request & 0x80ULL) {
        raw_load13_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load13_output_request = (int64_t)raw_load13_output_request;
    
    // Unpack Load14_Output_Request
    uint64_t raw_load14_output_request = 0;
    raw_load14_output_request |= ((uint64_t)((data[13] >> 0) & 0xFF) << 0);
    if (raw_load14_output_request & 0x80ULL) {
        raw_load14_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load14_output_request = (int64_t)raw_load14_output_request;
    
    // Unpack Load15_Output_Request
    uint64_t raw_load15_output_request = 0;
    raw_load15_output_request |= ((uint64_t)((data[14] >> 0) & 0xFF) << 0);
    if (raw_load15_output_request & 0x80ULL) {
        raw_load15_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load15_output_request = (int64_t)raw_load15_output_request;
    
    // Unpack Load16_Output_Request
    uint64_t raw_load16_output_request = 0;
    raw_load16_output_request |= ((uint64_t)((data[15] >> 0) & 0xFF) << 0);
    if (raw_load16_output_request & 0x80ULL) {
        raw_load16_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load16_output_request = (int64_t)raw_load16_output_request;
    
    // Unpack Load17_Output_Request
    uint64_t raw_load17_output_request = 0;
    raw_load17_output_request |= ((uint64_t)((data[16] >> 0) & 0xFF) << 0);
    if (raw_load17_output_request & 0x80ULL) {
        raw_load17_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load17_output_request = (int64_t)raw_load17_output_request;
    
    // Unpack Load18_Output_Request
    uint64_t raw_load18_output_request = 0;
    raw_load18_output_request |= ((uint64_t)((data[17] >> 0) & 0xFF) << 0);
    if (raw_load18_output_request & 0x80ULL) {
        raw_load18_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load18_output_request = (int64_t)raw_load18_output_request;
    
    // Unpack Load19_Output_Request
    uint64_t raw_load19_output_request = 0;
    raw_load19_output_request |= ((uint64_t)((data[18] >> 0) & 0xFF) << 0);
    if (raw_load19_output_request & 0x80ULL) {
        raw_load19_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load19_output_request = (int64_t)raw_load19_output_request;
    
    // Unpack Load20_Output_Request
    uint64_t raw_load20_output_request = 0;
    raw_load20_output_request |= ((uint64_t)((data[19] >> 0) & 0xFF) << 0);
    if (raw_load20_output_request & 0x80ULL) {
        raw_load20_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load20_output_request = (int64_t)raw_load20_output_request;
    
    // Unpack Load21_Output_Request
    uint64_t raw_load21_output_request = 0;
    raw_load21_output_request |= ((uint64_t)((data[20] >> 0) & 0xFF) << 0);
    if (raw_load21_output_request & 0x80ULL) {
        raw_load21_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load21_output_request = (int64_t)raw_load21_output_request;
    
    // Unpack Load22_Output_Request
    uint64_t raw_load22_output_request = 0;
    raw_load22_output_request |= ((uint64_t)((data[21] >> 0) & 0xFF) << 0);
    if (raw_load22_output_request & 0x80ULL) {
        raw_load22_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load22_output_request = (int64_t)raw_load22_output_request;
    
    // Unpack Load23_Output_Request
    uint64_t raw_load23_output_request = 0;
    raw_load23_output_request |= ((uint64_t)((data[22] >> 0) & 0xFF) << 0);
    if (raw_load23_output_request & 0x80ULL) {
        raw_load23_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load23_output_request = (int64_t)raw_load23_output_request;
    
    // Unpack Load24_Output_Request
    uint64_t raw_load24_output_request = 0;
    raw_load24_output_request |= ((uint64_t)((data[23] >> 0) & 0xFF) << 0);
    if (raw_load24_output_request & 0x80ULL) {
        raw_load24_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load24_output_request = (int64_t)raw_load24_output_request;
    
    // Unpack Load25_Output_Request
    uint64_t raw_load25_output_request = 0;
    raw_load25_output_request |= ((uint64_t)((data[24] >> 0) & 0xFF) << 0);
    if (raw_load25_output_request & 0x80ULL) {
        raw_load25_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load25_output_request = (int64_t)raw_load25_output_request;
    
    // Unpack Load26_Output_Request
    uint64_t raw_load26_output_request = 0;
    raw_load26_output_request |= ((uint64_t)((data[25] >> 0) & 0xFF) << 0);
    if (raw_load26_output_request & 0x80ULL) {
        raw_load26_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load26_output_request = (int64_t)raw_load26_output_request;
    
    // Unpack Load27_Output_Request
    uint64_t raw_load27_output_request = 0;
    raw_load27_output_request |= ((uint64_t)((data[26] >> 0) & 0xFF) << 0);
    if (raw_load27_output_request & 0x80ULL) {
        raw_load27_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load27_output_request = (int64_t)raw_load27_output_request;
    
    // Unpack Load28_Output_Request
    uint64_t raw_load28_output_request = 0;
    raw_load28_output_request |= ((uint64_t)((data[27] >> 0) & 0xFF) << 0);
    if (raw_load28_output_request & 0x80ULL) {
        raw_load28_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load28_output_request = (int64_t)raw_load28_output_request;
    
    // Unpack Load29_Output_Request
    uint64_t raw_load29_output_request = 0;
    raw_load29_output_request |= ((uint64_t)((data[28] >> 0) & 0xFF) << 0);
    if (raw_load29_output_request & 0x80ULL) {
        raw_load29_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load29_output_request = (int64_t)raw_load29_output_request;
    
    // Unpack Load30_Output_Request
    uint64_t raw_load30_output_request = 0;
    raw_load30_output_request |= ((uint64_t)((data[29] >> 0) & 0xFF) << 0);
    if (raw_load30_output_request & 0x80ULL) {
        raw_load30_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load30_output_request = (int64_t)raw_load30_output_request;
    
    // Unpack Load31_Output_Request
    uint64_t raw_load31_output_request = 0;
    raw_load31_output_request |= ((uint64_t)((data[30] >> 0) & 0xFF) << 0);
    if (raw_load31_output_request & 0x80ULL) {
        raw_load31_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load31_output_request = (int64_t)raw_load31_output_request;
    
    // Unpack Load32_Output_Request
    uint64_t raw_load32_output_request = 0;
    raw_load32_output_request |= ((uint64_t)((data[31] >> 0) & 0xFF) << 0);
    if (raw_load32_output_request & 0x80ULL) {
        raw_load32_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load32_output_request = (int64_t)raw_load32_output_request;
    
    // Unpack Load33_Output_Request
    uint64_t raw_load33_output_request = 0;
    raw_load33_output_request |= ((uint64_t)((data[32] >> 0) & 0xFF) << 0);
    if (raw_load33_output_request & 0x80ULL) {
        raw_load33_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load33_output_request = (int64_t)raw_load33_output_request;
    
    // Unpack Load34_Output_Request
    uint64_t raw_load34_output_request = 0;
    raw_load34_output_request |= ((uint64_t)((data[33] >> 0) & 0xFF) << 0);
    if (raw_load34_output_request & 0x80ULL) {
        raw_load34_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load34_output_request = (int64_t)raw_load34_output_request;
    
    // Unpack Load35_Output_Request
    uint64_t raw_load35_output_request = 0;
    raw_load35_output_request |= ((uint64_t)((data[34] >> 0) & 0xFF) << 0);
    if (raw_load35_output_request & 0x80ULL) {
        raw_load35_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load35_output_request = (int64_t)raw_load35_output_request;
    
    // Unpack Load36_Output_Request
    uint64_t raw_load36_output_request = 0;
    raw_load36_output_request |= ((uint64_t)((data[35] >> 0) & 0xFF) << 0);
    if (raw_load36_output_request & 0x80ULL) {
        raw_load36_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load36_output_request = (int64_t)raw_load36_output_request;
    
    // Unpack Load37_Output_Request
    uint64_t raw_load37_output_request = 0;
    raw_load37_output_request |= ((uint64_t)((data[36] >> 0) & 0xFF) << 0);
    if (raw_load37_output_request & 0x80ULL) {
        raw_load37_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load37_output_request = (int64_t)raw_load37_output_request;
    
    // Unpack Load38_Output_Request
    uint64_t raw_load38_output_request = 0;
    raw_load38_output_request |= ((uint64_t)((data[37] >> 0) & 0xFF) << 0);
    if (raw_load38_output_request & 0x80ULL) {
        raw_load38_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load38_output_request = (int64_t)raw_load38_output_request;
    
    // Unpack Load39_Output_Request
    uint64_t raw_load39_output_request = 0;
    raw_load39_output_request |= ((uint64_t)((data[38] >> 0) & 0xFF) << 0);
    if (raw_load39_output_request & 0x80ULL) {
        raw_load39_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load39_output_request = (int64_t)raw_load39_output_request;
    
    // Unpack Load40_Output_Request
    uint64_t raw_load40_output_request = 0;
    raw_load40_output_request |= ((uint64_t)((data[39] >> 0) & 0xFF) << 0);
    if (raw_load40_output_request & 0x80ULL) {
        raw_load40_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load40_output_request = (int64_t)raw_load40_output_request;
    
    // Unpack Load41_Output_Request
    uint64_t raw_load41_output_request = 0;
    raw_load41_output_request |= ((uint64_t)((data[40] >> 0) & 0xFF) << 0);
    if (raw_load41_output_request & 0x80ULL) {
        raw_load41_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load41_output_request = (int64_t)raw_load41_output_request;
    
    // Unpack Load42_Output_Request
    uint64_t raw_load42_output_request = 0;
    raw_load42_output_request |= ((uint64_t)((data[41] >> 0) & 0xFF) << 0);
    if (raw_load42_output_request & 0x80ULL) {
        raw_load42_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load42_output_request = (int64_t)raw_load42_output_request;
    
    // Unpack Load43_Output_Request
    uint64_t raw_load43_output_request = 0;
    raw_load43_output_request |= ((uint64_t)((data[42] >> 0) & 0xFF) << 0);
    if (raw_load43_output_request & 0x80ULL) {
        raw_load43_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load43_output_request = (int64_t)raw_load43_output_request;
    
    // Unpack Load44_Output_Request
    uint64_t raw_load44_output_request = 0;
    raw_load44_output_request |= ((uint64_t)((data[43] >> 0) & 0xFF) << 0);
    if (raw_load44_output_request & 0x80ULL) {
        raw_load44_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load44_output_request = (int64_t)raw_load44_output_request;
    
    // Unpack Load45_Output_Request
    uint64_t raw_load45_output_request = 0;
    raw_load45_output_request |= ((uint64_t)((data[44] >> 0) & 0xFF) << 0);
    if (raw_load45_output_request & 0x80ULL) {
        raw_load45_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load45_output_request = (int64_t)raw_load45_output_request;
    
    // Unpack Load46_Output_Request
    uint64_t raw_load46_output_request = 0;
    raw_load46_output_request |= ((uint64_t)((data[45] >> 0) & 0xFF) << 0);
    if (raw_load46_output_request & 0x80ULL) {
        raw_load46_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load46_output_request = (int64_t)raw_load46_output_request;
    
    // Unpack Load47_Output_Request
    uint64_t raw_load47_output_request = 0;
    raw_load47_output_request |= ((uint64_t)((data[46] >> 0) & 0xFF) << 0);
    if (raw_load47_output_request & 0x80ULL) {
        raw_load47_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load47_output_request = (int64_t)raw_load47_output_request;
    
    // Unpack Load48_Output_Request
    uint64_t raw_load48_output_request = 0;
    raw_load48_output_request |= ((uint64_t)((data[47] >> 0) & 0xFF) << 0);
    if (raw_load48_output_request & 0x80ULL) {
        raw_load48_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load48_output_request = (int64_t)raw_load48_output_request;
    
    // Unpack Load49_Output_Request
    uint64_t raw_load49_output_request = 0;
    raw_load49_output_request |= ((uint64_t)((data[48] >> 0) & 0xFF) << 0);
    if (raw_load49_output_request & 0x80ULL) {
        raw_load49_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load49_output_request = (int64_t)raw_load49_output_request;
    
    // Unpack Load50_Output_Request
    uint64_t raw_load50_output_request = 0;
    raw_load50_output_request |= ((uint64_t)((data[49] >> 0) & 0xFF) << 0);
    if (raw_load50_output_request & 0x80ULL) {
        raw_load50_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->load50_output_request = (int64_t)raw_load50_output_request;
    
    // Unpack HB1_Output_Request
    uint64_t raw_hb1_output_request = 0;
    raw_hb1_output_request |= ((uint64_t)((data[50] >> 0) & 0xFF) << 0);
    if (raw_hb1_output_request & 0x80ULL) {
        raw_hb1_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb1_output_request = (int64_t)raw_hb1_output_request;
    
    // Unpack HB2_Output_Request
    uint64_t raw_hb2_output_request = 0;
    raw_hb2_output_request |= ((uint64_t)((data[51] >> 0) & 0xFF) << 0);
    if (raw_hb2_output_request & 0x80ULL) {
        raw_hb2_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb2_output_request = (int64_t)raw_hb2_output_request;
    
    // Unpack HB3_Output_Request
    uint64_t raw_hb3_output_request = 0;
    raw_hb3_output_request |= ((uint64_t)((data[52] >> 0) & 0xFF) << 0);
    if (raw_hb3_output_request & 0x80ULL) {
        raw_hb3_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb3_output_request = (int64_t)raw_hb3_output_request;
    
    // Unpack HB4_Output_Request
    uint64_t raw_hb4_output_request = 0;
    raw_hb4_output_request |= ((uint64_t)((data[53] >> 0) & 0xFF) << 0);
    if (raw_hb4_output_request & 0x80ULL) {
        raw_hb4_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb4_output_request = (int64_t)raw_hb4_output_request;
    
    // Unpack HB5_Output_Request
    uint64_t raw_hb5_output_request = 0;
    raw_hb5_output_request |= ((uint64_t)((data[54] >> 0) & 0xFF) << 0);
    if (raw_hb5_output_request & 0x80ULL) {
        raw_hb5_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb5_output_request = (int64_t)raw_hb5_output_request;
    
    // Unpack HB6_Output_Request
    uint64_t raw_hb6_output_request = 0;
    raw_hb6_output_request |= ((uint64_t)((data[55] >> 0) & 0xFF) << 0);
    if (raw_hb6_output_request & 0x80ULL) {
        raw_hb6_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb6_output_request = (int64_t)raw_hb6_output_request;
    
    // Unpack HB7_Output_Request
    uint64_t raw_hb7_output_request = 0;
    raw_hb7_output_request |= ((uint64_t)((data[56] >> 0) & 0xFF) << 0);
    if (raw_hb7_output_request & 0x80ULL) {
        raw_hb7_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb7_output_request = (int64_t)raw_hb7_output_request;
    
    // Unpack HB8_Output_Request
    uint64_t raw_hb8_output_request = 0;
    raw_hb8_output_request |= ((uint64_t)((data[57] >> 0) & 0xFF) << 0);
    if (raw_hb8_output_request & 0x80ULL) {
        raw_hb8_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->hb8_output_request = (int64_t)raw_hb8_output_request;
    
    // Unpack Reserve1_Output_Request
    uint64_t raw_reserve1_output_request = 0;
    raw_reserve1_output_request |= ((uint64_t)((data[58] >> 0) & 0xFF) << 0);
    if (raw_reserve1_output_request & 0x80ULL) {
        raw_reserve1_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->reserve1_output_request = (int64_t)raw_reserve1_output_request;
    
    // Unpack Reserve2_Output_Request
    uint64_t raw_reserve2_output_request = 0;
    raw_reserve2_output_request |= ((uint64_t)((data[59] >> 0) & 0xFF) << 0);
    if (raw_reserve2_output_request & 0x80ULL) {
        raw_reserve2_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->reserve2_output_request = (int64_t)raw_reserve2_output_request;
    
    // Unpack Reserve3_Output_Request
    uint64_t raw_reserve3_output_request = 0;
    raw_reserve3_output_request |= ((uint64_t)((data[60] >> 0) & 0xFF) << 0);
    if (raw_reserve3_output_request & 0x80ULL) {
        raw_reserve3_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->reserve3_output_request = (int64_t)raw_reserve3_output_request;
    
    // Unpack Reserve4_Output_Request
    uint64_t raw_reserve4_output_request = 0;
    raw_reserve4_output_request |= ((uint64_t)((data[61] >> 0) & 0xFF) << 0);
    if (raw_reserve4_output_request & 0x80ULL) {
        raw_reserve4_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->reserve4_output_request = (int64_t)raw_reserve4_output_request;
    
    // Unpack Reserve5_Output_Request
    uint64_t raw_reserve5_output_request = 0;
    raw_reserve5_output_request |= ((uint64_t)((data[62] >> 0) & 0xFF) << 0);
    if (raw_reserve5_output_request & 0x80ULL) {
        raw_reserve5_output_request |= ~((1ULL << 8) - 1); // Sign extend
    }
    msg->reserve5_output_request = (int64_t)raw_reserve5_output_request;
    
    
    return 0;
}
