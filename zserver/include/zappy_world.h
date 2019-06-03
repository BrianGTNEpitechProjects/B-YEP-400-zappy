/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** zappy_world.h
*/

#ifndef PSU_ZAPPY_2018_ZAPPY_WORLD_H
#define PSU_ZAPPY_2018_ZAPPY_WORLD_H

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

typedef struct {
    user_base_t base;
    team_t team;
    unsigned int life_unit;
    unsigned int lvl;
    pos_t pos;
    cardinal_t orientation;
    unsigned int inventory[TOT_ITEM_NB];
} trantorian_t;

typedef struct tile_s tile_t;
struct tile_s {
    unsigned int content[TOT_ITEM_NB];
    tile_t *up;
    tile_t *down;
    tile_t *left;
    tile_t *right;
};

#endif //PSU_ZAPPY_2018_ZAPPY_WORLD_H
