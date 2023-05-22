#ifndef READ_H
#define READ_H
#endif

#include <stdint.h>

uint8_t read_u8(uint8_t *bytes, int *index);

uint16_t read_u16(uint8_t *bytes, int *index);

uint32_t read_u32(uint8_t *bytes, int *index);

uint64_t read_u64(uint8_t *bytes, int *index);

uint8_t *read_file(char *filename);
