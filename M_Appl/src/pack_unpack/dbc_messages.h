// Message structure definitions
#ifndef DBC_MESSAGES_H
#define DBC_MESSAGES_H

#include <stdint.h>
#include <stdbool.h>

// Diagnose_Communication (ID: 0x370, DLC: 64)
typedef struct {
    uint8_t diagnose_can_1; // LE01-1103 + LE01-1104, Range: 0 to 255
    uint8_t diagnose_can_2; // LE01-1105 + LE01-1106, Range: 0 to 255
    uint8_t diagnose_can_3; // LE01-1107 + LE01-1108, Range: 0 to 255
    uint8_t diagnose_eth100_1; // LE01-1143 + LE01-1144, Range: 0 to 255
    uint8_t diagnose_eth100_2; // LE01-1145 + LE01-1146, Range: 0 to 255
    uint8_t diagnose_eth100_3; // LE01-1147 + LE01-1148, Range: 0 to 255
    uint8_t diagnose_eth10_1; // LE01-1139 + LE01-1140, Range: 0 to 255
    uint8_t diagnose_eth10_2; // LE01-1141 + LE01-1142, Range: 0 to 255
    uint8_t diagnose_eth2_5g_1; // LE01-1130 + LE01-1131 + LE01-1132, Range: 0 to 255
    uint8_t diagnose_eth2_5g_2; // LE01-1133 + LE01-1134 + LE01-1135, Range: 0 to 255
    uint8_t diagnose_eth2_5g_3; // LE01-1136 + LE01-1137 + LE01-1138, Range: 0 to 255
    uint8_t diagnose_lin_1; // LE01-1099, Range: 0 to 255
    uint8_t diagnose_lin_2; // LE01-1100, Range: 0 to 255
    uint8_t diagnose_lin_3; // LE01-1101, Range: 0 to 255
    uint8_t diagnose_lin_4; // LE01-1102, Range: 0 to 255
    uint8_t diagnose_psi5_1; // LE01-1109 + LE01-1110, Range: 0 to 255
    uint8_t diagnose_psi5_2; // LE01-1111 + LE01-1112, Range: 0 to 255
} diagnose_communication_t;

// Diagnose_Audio (ID: 0x350, DLC: 4)
typedef struct {
    uint8_t diagnose_audio_channel1; // Range: 0 to 255
    uint8_t diagnose_audio_channel2; // Range: 0 to 255
    uint8_t diagnose_audio_channel3; // Range: 0 to 255
    uint8_t diagnose_audio_channel4; // Range: 0 to 255
} diagnose_audio_t;

// States_CMC1_ROOMLAMP1 (ID: 0x340, DLC: 64)
typedef struct {
    int16_t lm00_output_current; // Unit: A, Range: -327.68 to 327.67
    uint8_t lm00_output_errorstate; // Range: 0 to 255
    int8_t lm00_output_request; // Range: -101 to 101
    int8_t lm00_output_state; // Range: -101 to 101
    uint8_t roomlamp1_output_errorstate; // Range: 0 to 255
    uint16_t lm00_output_temp; // Unit: °C, Range: 0 to 6553.5
    uint16_t lm00_output_voltage; // Unit: V, Range: 0 to 655.35
    int16_t roomlamp1_output_current; // Unit: A, Range: -327.68 to 327.67
    int8_t roomlamp1_output_state; // Range: -101 to 101
    uint16_t roomlamp1_output_temp; // Unit: °C, Range: 0 to 6553.5
    uint16_t roomlamp1_output_voltage; // Unit: V, Range: 0 to 655.35
} states_cmc1_roomlamp1_t;

// Requests_CM30_ROOMLAMP1 (ID: 0x001, DLC: 48)
typedef struct {
    int8_t lm00_output_request; // Range: -101 to 101
    int8_t roomlamp1_output_request; // Range: -101 to 101
    bool retry_control_reset;
} requests_cm30_roomlamp1_t;

// Requests_Load1_Reverse5 (ID: 0x000, DLC: 64)
typedef struct {
    int8_t load1_output_request; // LE01-1001, Range: -101 to 101
    int8_t load2_output_request; // LE01-1002, Range: -101 to 101
    int8_t load3_output_request; // LE01-1003, Range: -101 to 101
    int8_t load4_output_request; // LE01-1004, Range: -101 to 101
    int8_t load5_output_request; // LE01-1005, Range: -101 to 101
    int8_t load6_output_request; // LE01-1006, Range: -101 to 101
    int8_t load7_output_request; // LE01-1007, Range: -101 to 101
    int8_t load8_output_request; // LE01-1008, Range: -101 to 101
    int8_t load9_output_request; // LE01-1009, Range: -101 to 101
    int8_t load10_output_request; // LE01-1010, Range: -101 to 101
    int8_t load11_output_request; // LE01-1011, Range: -101 to 101
    int8_t load12_output_request; // LE01-1012, Range: -101 to 101
    int8_t load13_output_request; // LE01-1013, Range: -101 to 101
    int8_t load14_output_request; // LE01-1014, Range: -101 to 101
    int8_t load15_output_request; // LE01-1015, Range: -101 to 101
    int8_t load16_output_request; // LE01-1016, Range: -101 to 101
    int8_t load17_output_request; // LE01-1017, Range: -101 to 101
    int8_t load18_output_request; // LE01-1018, Range: -101 to 101
    int8_t load19_output_request; // LE01-1019, Range: -101 to 101
    int8_t load20_output_request; // LE01-1020, Range: -101 to 101
    int8_t load21_output_request; // LE01-1021, Range: -101 to 101
    int8_t load22_output_request; // LE01-1022, Range: -101 to 101
    int8_t load23_output_request; // LE01-1023, Range: -101 to 101
    int8_t load24_output_request; // LE01-1024, Range: -101 to 101
    int8_t load25_output_request; // LE01-1025, Range: -101 to 101
    int8_t load26_output_request; // LE01-1026, Range: -101 to 101
    int8_t load27_output_request; // LE01-1027, Range: -101 to 101
    int8_t load28_output_request; // LE01-1028, Range: -101 to 101
    int8_t load29_output_request; // LE01-1029, Range: -101 to 101
    int8_t load30_output_request; // LE01-1030, Range: -101 to 101
    int8_t load31_output_request; // LE01-1031, Range: -101 to 101
    int8_t load32_output_request; // LE01-1032, Range: -101 to 101
    int8_t load33_output_request; // LE01-1033, Range: -101 to 101
    int8_t load34_output_request; // LE01-1034, Range: -101 to 101
    int8_t load35_output_request; // LE01-1035, Range: -101 to 101
    int8_t load36_output_request; // LE01-1036, Range: -101 to 101
    int8_t load37_output_request; // LE01-1037, Range: -101 to 101
    int8_t load38_output_request; // LE01-1038, Range: -101 to 101
    int8_t load39_output_request; // LE01-1039, Range: -101 to 101
    int8_t load40_output_request; // LE01-1040, Range: -101 to 101
    int8_t load41_output_request; // LE01-1041, Range: -101 to 101
    int8_t load42_output_request; // LE01-1042, Range: -101 to 101
    int8_t load43_output_request; // LE01-1043, Range: -101 to 101
    int8_t load44_output_request; // LE01-1044, Range: -101 to 101
    int8_t load45_output_request; // LE01-1045, Range: -101 to 101
    int8_t load46_output_request; // LE01-1046, Range: -101 to 101
    int8_t load47_output_request; // LE01-1047, Range: -101 to 101
    int8_t load48_output_request; // LE01-1048, Range: -101 to 101
    int8_t load49_output_request; // LE01-1049, Range: -101 to 101
    int8_t load50_output_request; // LE01-1050, Range: -101 to 101
    int8_t hb1_output_request; // LE01-1051, Range: -101 to 101
    int8_t hb2_output_request; // LE01-1052, Range: -101 to 101
    int8_t hb3_output_request; // LE01-1053, Range: -101 to 101
    int8_t hb4_output_request; // LE01-1054, Range: -101 to 101
    int8_t hb5_output_request; // LE01-1055, Range: -101 to 101
    int8_t hb6_output_request; // LE01-1056, Range: -101 to 101
    int8_t hb7_output_request; // LE01-1057, Range: -101 to 101
    int8_t hb8_output_request; // LE01-1058, Range: -101 to 101
    int8_t reserve1_output_request; // Range: -101 to 101
    int8_t reserve2_output_request; // Range: -101 to 101
    int8_t reserve3_output_request; // Range: -101 to 101
    int8_t reserve4_output_request; // Range: -101 to 101
    int8_t reserve5_output_request; // Range: -101 to 101
} requests_load1_reverse5_t;

#endif // DBC_MESSAGES_H
