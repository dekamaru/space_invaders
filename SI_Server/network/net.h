int* net_socket, net_new_socket, net_c;
int* net_new_sock;

int net_port_bind();
int net_server_start(int port);
void *net_connection_handler(void *);
