#include "read.h"

uint8_t read_u8(uint8_t *bytes, int *index) { return bytes[(*index)++]; }

uint16_t read_u16(uint8_t *bytes, int *index) {
    uint16_t value = bytes[(*index)++] << 8;
    value |= bytes[(*index)++];
    return value;
}

uint32_t read_u32(uint8_t *bytes, int *index) {
    uint32_t value = bytes[(*index)++] << 24;
    value |= bytes[(*index)++] << 16;
    value |= bytes[(*index)++] << 8;
    value |= bytes[(*index)++];
    return value;
}

uint64_t read_u64(uint8_t *bytes, int *index) {
    uint64_t value = bytes[(*index)++] << 56;
    value |= bytes[(*index)++] << 48;
    value |= bytes[(*index)++] << 40;
    value |= bytes[(*index)++] << 32;
    value |= bytes[(*index)++] << 24;
    value |= bytes[(*index)++] << 16;
    value |= bytes[(*index)++] << 8;
    value |= bytes[(*index)++];
    return value;
}