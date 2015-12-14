#include "packet.h"
#include <math.h>
#include <string.h>

//TODO: use outsided buffer, no creating one
char* packet_create(uint32_t packet_id, uint32_t data_length, char* data) {
    char* buffer = malloc(1024);
    Packet *p = (Packet*) buffer;
    p->packet_id = packet_id;
    p->data_length = data_length;
    strcpy(p->data, data);
    return buffer;
}

void packet_write_int(char* buffer, int value) {
    int start = 0; while(buffer[start] != 0) start++; // finding free space to write
    if (value == 0) {
        buffer[start] = 48;
        buffer[start + 1] = ':';
        return;
    }
    int digits = floor(log10(abs(value))) + 1; // check num of digits

    for(int i = start + digits - 1; i >= start; i--) {
        buffer[i] = (value % 10) + 48;
        value /= 10;
    }
    buffer[start + digits] = ':';
}

int packet_read_int(char** buffer) {
    int readed = 0;
    int result = 0;
    while(*(*buffer + readed) != ':') {
        result *= 10;
        result += *(*buffer + readed) - 48;
        readed++;
    }
    *(buffer) += readed + 1;
    return result;
}
