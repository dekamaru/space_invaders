//
// Created by dekamaru on 10.01.16.
//

#ifndef SI_CLIENT_CONNECT_H
#define SI_CLIENT_CONNECT_H

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "26000"

void connect_init();
void connect_draw(void* renderer);
void connect_event(void* event);
void connect_update();

#endif //SI_CLIENT_CONNECT_H
