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
    team_t team;
    unsigned int life_unit;
    unsigned int lvl;
    pos_t pos;
    cardinal_t orientation;
    unsigned int inventory[TOT_ITEM_NB];
} trantorian_t;


typedef struct tile_s {
    unsigned int content[TOT_ITEM_NB];
    struct title_s *up;
    struct title_s *down;
    struct title_s *left;
    struct title_s *right;
} tile_t;

#endif //PSU_ZAPPY_2018_ZAPPY_WORLD_H
