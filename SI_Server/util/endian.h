unsigned char* endian_pack_int(unsigned char* buffer, int value);
unsigned char* endian_pack_char(unsigned char* buffer, char value);
unsigned char* endian_pack_string(unsigned char* buffer, char* value, int length);
int endian_unpack_int(unsigned char* buffer);
void endian_unpack_string(unsigned char* buffer, char* dest, int length);
