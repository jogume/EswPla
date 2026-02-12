// System Signal Interface Header
#ifndef SYSTEM_SIGNALS_H
#define SYSTEM_SIGNALS_H

#include <stdint.h>
#include <stdbool.h>

// System data structure containing all signals
typedef struct {
    uint8_t diagnose_can_1; // LE01-1103 + LE01-1104
    uint8_t diagnose_can_2; // LE01-1105 + LE01-1106
    uint8_t diagnose_can_3; // LE01-1107 + LE01-1108
    uint8_t diagnose_eth100_1; // LE01-1143 + LE01-1144
    uint8_t diagnose_eth100_2; // LE01-1145 + LE01-1146
    uint8_t diagnose_eth100_3; // LE01-1147 + LE01-1148
    uint8_t diagnose_eth10_1; // LE01-1139 + LE01-1140
    uint8_t diagnose_eth10_2; // LE01-1141 + LE01-1142
    uint8_t diagnose_eth2_5g_1; // LE01-1130 + LE01-1131 + LE01-1132
    uint8_t diagnose_eth2_5g_2; // LE01-1133 + LE01-1134 + LE01-1135
    uint8_t diagnose_eth2_5g_3; // LE01-1136 + LE01-1137 + LE01-1138
    uint8_t diagnose_lin_1; // LE01-1099
    uint8_t diagnose_lin_2; // LE01-1100
    uint8_t diagnose_lin_3; // LE01-1101
    uint8_t diagnose_lin_4; // LE01-1102
    uint8_t diagnose_psi5_1; // LE01-1109 + LE01-1110
    uint8_t diagnose_psi5_2; // LE01-1111 + LE01-1112
    uint8_t diagnose_audio_channel1;
    uint8_t diagnose_audio_channel2;
    uint8_t diagnose_audio_channel3;
    uint8_t diagnose_audio_channel4;
	int8_t lm00_output_request;
    int8_t load1_output_request; // LE01-1001
} system_data_t;

// Function declarations
void system_signals_init(void);
int get_system_data(system_data_t* data);
int set_system_data(const system_data_t* data);


void process_lm00_output_request(int8_t value);
void process_load1_output_request(int8_t value);

#endif // SYSTEM_SIGNALS_H
