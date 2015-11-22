#include "endian.h"

unsigned char* endian_pack_int(unsigned char* buffer, int value) {
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

int endian_unpack_int(unsigned char* buffer) {
    int result;
    result = buffer[0] << 24;
    result |= buffer[1] << 16;
    result |= buffer[2] << 8;
    result |= buffer[3];
    return result;
}

unsigned char* endian_pack_char(unsigned char* buffer, char value) {
    buffer[0] = value;
    return buffer + 1;
}

unsigned char* endian_pack_string(unsigned char* buffer, int size, char* value) {
    int i;
    for (i = 0; i < size; i++) {
        buffer[i] = value[i];
    }
    return buffer + size;
}
