typedef enum {CONNECTED, DISCONNECTED} net_state;
net_state net_status;

int* net_socket, net_new_socket, net_c;
int* net_new_sock;

int net_port_bind(int port);
int net_server_start(int port);
void *net_connection_handler(void *);

int net_client_connect(char* addr, int port);
int net_client_receive(char* buffer, int length);
int net_client_send(char* message, int length);
