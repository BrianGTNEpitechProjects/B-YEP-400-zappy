/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy_world.h
*/

#ifndef PSU_ZAPPY_2018_ZAPPY_WORLD_H
#define PSU_ZAPPY_2018_ZAPPY_WORLD_H

#include "network_manager.h"
#include "zposition.h"
#include "zcommand_proto.h"

#define ZAPPY_DELIM "\n"
#define ZAPPY_DELIM_SIZE 1

#define COMMAND_QUEUE_LEN (10)

/*
 * ITEM
 */
typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    TOT_ITEM_NB
} e_item_t;

typedef struct {
    e_item_t id;
    const uint8_t *name;
} item_t;

/*
 * CHARACTERS
 */
typedef struct {
    char *name;
} team_t;

typedef struct trantorian_s trantorian_t;
typedef struct tile_s tile_t;

typedef pos_t dim_t;
typedef struct {
    dim_t map_size;
    tile_t **map;
    network_manager_t *nm;
    id_t classic_id;
    id_t websocket_id;
    trantorian_t *players;
    team_t *teams;
    int default_slots_teams;
    int time_scale;
} zappy_t;

struct trantorian_s {
    user_base_t base;
    bool is_egg;
    zappy_t *zappy;
    unsigned char command_ind;
    command_t queue[COMMAND_QUEUE_LEN];
    team_t team;
    unsigned int life_unit;
    unsigned int lvl;
    tile_t *pos;
    trantorian_t *neighbour;
    trantorian_t *next;
    e_cardinal_t orientation;
    uint inventory[TOT_ITEM_NB];
};

struct tile_s {
    unsigned int content[TOT_ITEM_NB];
    trantorian_t *first;
    tile_t *north;
    tile_t *south;
    tile_t *west;
    tile_t *east;
    unsigned long long broadcasted;
};

/* zappy_run.c */
bool run_zappy(zappy_t *zap);

/* zappy.c */
bool zappy(int ac, char **av);

/*  map.c   */
tile_t **create_map(int x, int y);

/* new.c */
trantorian_t *accept_player(zappy_t *zap);

/* teams.c */
int count_unused_slot(zappy_t *zap, char *team_name);
int count_players_team(zappy_t *zap, char *team_name);

/* neighbour.c */
void trantorian_place_on_tile(trantorian_t *trantorian, tile_t *tile);
int tile_population_size(tile_t *tile);
trantorian_t *first_neighbour(trantorian_t *self);
trantorian_t *last_neighbour(trantorian_t *self);

/* move.c */
int trantorian_move(trantorian_t *trantorian, tile_t *tile);
int trantorian_move_dir(trantorian_t *trantorian, e_cardinal_t dir);
int trantorian_move_forward(trantorian_t *trantorian);
tile_t *tile_forward(tile_t *tile, e_cardinal_t dir);

/* cardinal_utils.c */
e_cardinal_t cardinal_rotate_right(e_cardinal_t dir);
e_cardinal_t cardinal_rotate_left(e_cardinal_t dir);
char *cardinal_to_string(e_cardinal_t dir);

extern const item_t item_map[];

#endif //PSU_ZAPPY_2018_ZAPPY_WORLD_H
