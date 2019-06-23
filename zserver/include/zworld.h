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
#include "zitem.h"

#define ZAPPY_DELIM "\n"
#define ZAPPY_DELIM_SIZE 1

#define MAX_LEVEL 8
#define TEAM_PLAYERS_TO_WIN 6

#define COMMAND_QUEUE_LEN (10)

/*
 * CHARACTERS
 */
typedef struct {
    char *name;
    id_t id;
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
    struct timespec resources_spawn[TOT_ITEM_NB];
    bool natural_spawn_activated;
    bool case_sensitive_inputs;
    long resources_spawn_cap;
} zappy_t;

struct trantorian_s {
    user_base_t base;
    id_t id;
    id_t egg_owner;
    bool is_egg;
    zappy_t *zappy;
    unsigned char command_ind;
    command_t queue[COMMAND_QUEUE_LEN];
    team_t *team;
    unsigned int life_unit;
    unsigned int lvl;
    tile_t *pos;
    trantorian_t *neighbour;
    trantorian_t *next;
    e_cardinal_t orientation;
    uint inventory[TOT_ITEM_NB];
    double food_time;
};

struct tile_s {
    unsigned int content[TOT_ITEM_NB];
    trantorian_t *first;
    tile_t *north;
    tile_t *south;
    tile_t *west;
    tile_t *east;
    unsigned long long broadcasted;
    pos_t coords;
};

/* zappy_run.c */
bool run_zappy(zappy_t *zap);

/* zappy.c */
bool zappy(int ac, char **av);

/* resources.c */
void set_min_timeout(zappy_t *zap, struct timespec timeouts[TOT_ITEM_NB]);
void set_timeout(struct timespec *to, double scaled_time);

/*  map.c   */
tile_t **create_map(int x, int y);
pos_t get_random_positions(dim_t map_size);
void set_position(trantorian_t *to_place, tile_t *tile);

/* teams.c */
int count_unused_slot(zappy_t *zap, char *team_name);
int count_players_team(zappy_t *zap, char *team_name);
int count_teams(zappy_t *zap);

/* neighbour.c */
void trantorian_place_on_tile(trantorian_t *trantorian, tile_t *tile);
int tile_population_size(tile_t *tile);
int tile_population_size_with_lvl(tile_t *tile, unsigned int lvl);
trantorian_t *first_neighbour(trantorian_t *self);
trantorian_t *last_neighbour(trantorian_t *self);

/* move.c tile.c */
tile_t *tile_forward(tile_t *tile, e_cardinal_t dir);
int trantorian_move(trantorian_t *trantorian, tile_t *tile);
int trantorian_move_dir(trantorian_t *trantorian, e_cardinal_t dir);
int trantorian_move_forward(trantorian_t *trantorian);

/* cardinal_utils.c */
e_cardinal_t cardinal_rotate_right(e_cardinal_t dir);
e_cardinal_t cardinal_rotate_left(e_cardinal_t dir);
char *cardinal_to_string(e_cardinal_t dir);

/* get_item_id_from_name.c */
int get_item_id_from_name(char *name, bool case_sensitive);

/* apply_time.c */
bool apply_time(double *ref, struct timespec *delta_start, int scale);

/* kill_client.c */
bool kill_player(trantorian_t *p);
bool kill_client(client_user_pair_t *c);

/* set_to_newt_command.c */
void set_to_next_command(trantorian_t *t);

/* end_game.c */
void end_game(zappy_t *zap, team_t *winners);
void check_end_game(zappy_t *zap);

/* case_sensitive */
int cmpstr(const char *s1, const char *s2, bool case_sensitive);
int cmpnstr(const char *s1, const char *s2, bool case_sensitive, int n);

#endif
