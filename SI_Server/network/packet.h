typedef struct Packet {
    int packet_id;
    int data_length;
    char* data;
} Packet;

void packet_serialize(unsigned char* buffer, Packet *p);
int packet_size(Packet *p);
unsigned char* packet_create(int packet_id, int data_length, char* data);
Packet* packet_deserialize(unsigned char* buffer);
int packet_buffer_size(int data_length);
