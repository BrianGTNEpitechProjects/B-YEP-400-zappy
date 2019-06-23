/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zserver.h
*/

/* Created the 28/05/2019 at 17:54 by brian */

#ifndef PSU_ZAPPY_2018_ZSERVER_H
#define PSU_ZAPPY_2018_ZSERVER_H

#include <stdio.h>
#include <regex.h>
#include "common.h"
#include "network_client.h"
#include "network_user_base.h"
#include "network_manager.h"
#include "zworld.h"

#define MAX_TEAMS 50
#define MAX_TEAM_NAME 50
#define MAX_PLAYERS_PER_TEAM 50

#define MAX_TEAMS_MSG "Maximum number of teams allowed: %i\n"
#define MAX_TEAM_NAME_MSG "Maximum length of a team name: %i, %s not valid\n"
#define MAX_PLAYERS_PER_TEAM_MSG "Maximum number of players per team: %i\n"

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
void send_websocket_header(network_client_t *, size_t, uint8_t);
void send_websocket(network_client_t *, uint8_t *, size_t, uint8_t);
void read_ws_clients_data(network_server_t *server);

#define DEFAULT_ARGS {0, 0, 0, 0, 100, NULL, 0, 0, false, false}

typedef struct {
    int port;
    int x;
    int y;
    int ppt;
    int freq;
    char **teams;
    int tc;
    int wsport;
    bool set_ws;
    bool interactive_mode;
} args_t;

/* utils.c */
int handle_error_return(char *s, int ret);

/* on_events */
void on_disconnect(user_base_t *base, network_client_t *client);
void on_extract_not_connected(user_base_t*, network_client_t*, \
uint8_t*, size_t);
void on_extract_connected(user_base_t *, network_client_t *, uint8_t *, size_t);

/*  arguments.c */
bool parse_args(args_t *arguments, int ac, char **av);

/*  remove_signals.c  */
bool remove_sig_catch(void);

/*  server_running.c    */
bool setup_catch_signals(void);
bool running(void);
void shutdown_server(void);

/* new.c */
trantorian_t *accept_player(zappy_t *zap);
void set_position_relative(trantorian_t *to_place, tile_t *tile, pos_t pos);
tile_t *get_tile_relative(tile_t *tile, pos_t pos);
trantorian_t *create_player(void);

/* connection.c */
void response_success_connection(trantorian_t *tranto, network_client_t *nc);
trantorian_t * add_user_to_team(client_user_pair_t *pair, team_t *team);

/* process_command.c */
void process_command_on_users(zappy_t *z, network_client_user_map_t *m);

/* resources.c */
void spawn_resource(zappy_t *world, tile_t *tile, e_item_t type);
void process_spawn_resources(zappy_t *zap);
void init_spawn_timeouts(zappy_t *res);

/* starve.c */
void starve(client_user_pair_t *c);


static inline bool write_to_client(\
    client_user_pair_t *client, \
    const uint8_t *data, \
    size_t sz\
)
{
    return (write_to_buffer(&client->client->cb_out, data, sz));
}


#endif //PSU_ZAPPY_2018_ZSERVER_H
