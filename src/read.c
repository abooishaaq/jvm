#include "read.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t read_u8(uint8_t *bytes, int *index) { return bytes[(*index)++]; }

uint16_t read_u16(uint8_t *bytes, int *index) {
    uint16_t value = bytes[(*index)++] << 8;
    value |= bytes[(*index)++];
    return value;
}

uint32_t read_u32(uint8_t *bytes, int *index) {
    uint32_t value = (uint32_t)bytes[(*index)++] << 24;
    value |= (uint32_t)bytes[(*index)++] << 16;
    value |= (uint32_t)bytes[(*index)++] << 8;
    value |= (uint32_t)bytes[(*index)++];
    return value;
}

uint64_t read_u64(uint8_t *bytes, int *index) {
    uint64_t value = (uint64_t)bytes[(*index)++] << 56;
    value |= (uint64_t)bytes[(*index)++] << 48;
    value |= (uint64_t)bytes[(*index)++] << 40;
    value |= (uint64_t)bytes[(*index)++] << 32;
    value |= (uint64_t)bytes[(*index)++] << 24;
    value |= (uint64_t)bytes[(*index)++] << 16;
    value |= (uint64_t)bytes[(*index)++] << 8;
    value |= (uint64_t)bytes[(*index)++];
    return value;
}

uint8_t *read_file(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *buffer = malloc(length);
    fread(buffer, 1, length, file);
    fclose(file);
    return buffer;
}