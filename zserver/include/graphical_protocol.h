/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** graphical_protocol.h
*/

/* Created the 17/06/2019 at 16:40 by jfrabel */

#ifndef PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H
#define PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H

#include "zworld.h"
#include "zserver.h"

typedef enum incantation_result {
    GP_INCANTATION_RESULT_SUCCESS,
    GP_INCANTATION_RESULT_FAILURE
} incantation_result_t;

typedef struct graphical_user {
    zuser_ws_t base;
    zappy_t *world_infos;
} graphical_user_t;

typedef struct guser_possible_cmds {
    const char *cmd;
    bool (*func)(graphical_user_t *, network_client_t *, uint8_t *, size_t);
} guser_possible_cmds_t;

graphical_user_t *create_new_graphical_user(zappy_t *world_data);
void delete_graphical_user(graphical_user_t *user);

void update_ws_server(zappy_t *zap);

void send_to_all_ws_clients(zappy_t *world, uint8_t *msg, size_t len);

void handle_graphical_user_cmd(graphical_user_t *user,
    network_client_t *client, uint8_t *data, size_t data_size);

trantorian_t *find_trantorian_egg_by_owner_id(zappy_t *world, id_t id);
trantorian_t *find_trantorian_egg_by_id(zappy_t *world, id_t id);
trantorian_t *find_trantorian_by_id(zappy_t *world, id_t id);
trantorian_t *find_trantorian_by_parent_id(zappy_t *world, id_t id);

int cardinal_to_int(e_cardinal_t cardinal);
int item_to_int(e_item_t item);

bool msz(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool bct(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool pia(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool tna(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool ppo(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool plv(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool pin(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sgt(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sst(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool suc(graphical_user_t *, network_client_t *, uint8_t *, size_t);
bool sbp(graphical_user_t *, network_client_t *, uint8_t *, size_t);

void pnw(zappy_t *world, trantorian_t *new_player);
void pex(zappy_t *world, trantorian_t *player_expulsing);
void pbc(zappy_t *world, trantorian_t *player, const char *msg);
void pic(zappy_t *world, trantorian_t *player_incanting);
void pie(zappy_t *world, int x, int y, incantation_result_t result);
void pfk(zappy_t *world, trantorian_t *player_laying);
void pdr(zappy_t *world, trantorian_t *player_dropping, e_item_t item);
void pgt(zappy_t *world, trantorian_t *player_getting, e_item_t item);
void pdi(zappy_t *world, trantorian_t *player_dying);
void enw(zappy_t *world, trantorian_t *egg);
void eht(zappy_t *world, trantorian_t *egg);
void smg(zappy_t *world, const char *msg);
void seg(zappy_t *world, const char *team);

#endif //PSU_ZAPPY_2018_GRAPHICAL_PROTOCOL_H
