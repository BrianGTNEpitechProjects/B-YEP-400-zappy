/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zserver.h
*/

/* Created the 28/05/2019 at 17:54 by brian */

#ifndef PSU_ZAPPY_2018_ZSERVER_H
#define PSU_ZAPPY_2018_ZSERVER_H

#include <regex.h>
#include "network_client.h"
#include "network_user_base.h"
#include "network_manager.h"

enum socket_type {
    UNDEFINED,
    CLASSIC,
    WEBSOCKET_INIT,
    WEBSOCKET
};

struct websocket_header {
    char *http_version;
    char *upgrade;
    char *connection;
    char *key;
};

typedef struct zuser_websocket {
    user_base_t base;
    enum socket_type sock_type;
    struct websocket_header *websocket_hdr;
} zuser_ws_t;

struct websocket_header_line {
    const char *line_regex;
    void (*func)(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
};

void parse_websocket_protocol(char *, zuser_ws_t *, network_client_t *);
void header_start(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
void set_upgrade(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
void set_connection(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
void set_key(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
void header_end(char *, zuser_ws_t *, regmatch_t *, network_client_t *);
char *base64_encode(unsigned char *, size_t);
unsigned int get_base64_size(size_t);
void send_websocket(network_client_t *, uint8_t *, size_t, uint8_t);
void read_ws_clients_data(network_server_t *server);

#endif //PSU_ZAPPY_2018_ZSERVER_H
