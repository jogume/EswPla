// DBC Pack/Unpack Function Declarations
#ifndef DBC_PACK_UNPACK_H
#define DBC_PACK_UNPACK_H

#include "dbc_messages.h"

// Pack function declarations
uint8_t diagnose_communication_pack(uint8_t* data, const diagnose_communication_t* msg, uint8_t size);
uint8_t diagnose_audio_pack(uint8_t* data, const diagnose_audio_t* msg, uint8_t size);

// Unpack function declarations
int requests_cm30_roomlamp1_unpack(requests_cm30_roomlamp1_t* msg, const uint8_t* data, uint8_t dlc);
int requests_load1_reverse5_unpack(requests_load1_reverse5_t* msg, const uint8_t* data, uint8_t dlc);

#endif // DBC_PACK_UNPACK_H
