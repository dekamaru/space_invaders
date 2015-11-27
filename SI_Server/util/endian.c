#include "endian.h"

unsigned char* endian_pack_int(unsigned char* buffer, int value) {
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

unsigned char* endian_pack_char(unsigned char* buffer, char value) {
    buffer[0] = value;
    return buffer + 1;
}

unsigned char* endian_pack_string(unsigned char* buffer, char* value, int length) {
    int i;
    for(i = 0; i < length; i++) {
        buffer[i] = value[i];
    }
    return buffer + length;
}

void endian_unpack_string(unsigned char* buffer, char* dest, int length) {
    int i;
    for(i = 0; i < length; i++) {
        dest[i] = buffer[i];
    }
}

int endian_unpack_int(unsigned char* buffer) {
    int result;
    result = buffer[0] << 24;
    result |= buffer[1] << 16;
    result |= buffer[2] << 8;
    result |= buffer[3];
    return result;
}

