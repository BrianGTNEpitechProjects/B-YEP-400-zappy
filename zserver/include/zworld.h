/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy_world.h
*/

#ifndef PSU_ZAPPY_2018_ZAPPY_WORLD_H
#define PSU_ZAPPY_2018_ZAPPY_WORLD_H

#include "zcommands.h"

#define ZAPPY_DELIM "\n"
#define ZAPPY_DELIM_SIZE 1

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} cardinal_t;

typedef union {
    struct {
        int x;
        int y;
    };
    int arr[2];
} pos_t;

typedef enum {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    TOT_ITEM_NB
} e_item_t;

typedef struct {
    char *name;
} team_t;

typedef struct trantorian_s trantorian_t;
typedef struct tile_s tile_t;

struct trantorian_s {
    user_base_t base;
    command_t queue[10];
    team_t team;
    unsigned int life_unit;
    unsigned int lvl;
    tile_t *pos;
    trantorian_t *neighbour;
    cardinal_t orientation;
    unsigned int inventory[TOT_ITEM_NB];
};

struct tile_s {
    unsigned int content[TOT_ITEM_NB];
    trantorian_t *first;
    tile_t *north;
    tile_t *south;
    tile_t *west;
    tile_t *east;
};

typedef pos_t dim_t;
typedef struct {
    dim_t map_size;
    tile_t **map;
    network_manager_t *nm;
    id_t classic_id;
    id_t websocket_id;
    trantorian_t *players;
    team_t *teams;
} zappy_t;

/* zappy_run.c */
bool run_zappy(zappy_t *zap);

/* zappy.c */
bool zappy(int ac, char **av);

/*  map.c   */
tile_t **create_map(int x, int y);

#endif //PSU_ZAPPY_2018_ZAPPY_WORLD_H
