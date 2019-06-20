/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Zappy
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "zworld.h"
#include "common.h"
#include "graphical_protocol.h"

void spawn_resource(zappy_t *world, tile_t *tile, e_item_t type)
{
    if (type >= TOT_ITEM_NB)
        return;
    tile->content[type]++;
    nrs(world, tile, type);
}

void spawn_rand_resources(zappy_t *zap, e_item_t type)
{
    tile_t *tile = *zap->map;

    for (long x = random() % zap->map_size.x; x >= 0; x--)
        tile = tile->east;
    for (long y = random() % zap->map_size.y; y >= 0; y--)
        tile = tile->south;
    if (zap->natural_spawn_activated)
        spawn_resource(zap, tile, type);
}

void set_timeout(struct timespec *to, double scaled_time)
{
    to->tv_sec = (long)scaled_time;
    to->tv_nsec = (long)((scaled_time - (long)scaled_time) * pow(10, 9));
}

void set_min_timeout(zappy_t *zap, struct timespec timeouts[TOT_ITEM_NB])
{
    network_server_t *server = get_server(zap->nm, zap->classic_id);
    struct timespec min = {0};

    min.tv_nsec = timeouts[0].tv_nsec;
    min.tv_sec = timeouts[0].tv_sec;
    for (e_item_t i = 0; i < TOT_ITEM_NB; i++) {
        if ((timeouts[i].tv_sec < min.tv_sec) || (timeouts[i].tv_sec == min.tv_sec && timeouts[i].tv_nsec < min.tv_nsec)) {
            min.tv_nsec = zap->resources_spawn[i].tv_nsec;
            min.tv_sec = zap->resources_spawn[i].tv_sec;
        }
    }
    server->world_event_timeout.tv_sec = min.tv_sec;
    server->world_event_timeout.tv_usec = min.tv_nsec / 1000;
}

void process_spawn_resources(zappy_t *zap)
{
    static struct timespec last = {0};
    struct timespec now = {0};
    struct timespec delta;
    struct timespec zero = {0, 0};
    double scaled = 0;

    if (last.tv_sec == 0 && last.tv_nsec == 0)
        clock_gettime(0, (struct timespec *)&last);
    clock_gettime(0, (struct timespec *)&now);
    timersub(&now, &last, &delta);
    for (e_item_t i = 0; i < TOT_ITEM_NB; i++) {
        timersub(&zap->resources_spawn[i], &delta, &zap->resources_spawn[i]);
        if (timercmp(zap->resources_spawn[i], zero, <=)) {
            scaled = item_map[i].spawn_frequency / zap->time_scale;
            spawn_rand_resources(zap, i);
            set_timeout(&zap->resources_spawn[i], scaled);
        }
    }
    set_min_timeout(zap, zap->resources_spawn);
}

void init_spawn_timeouts(zappy_t *res)
{
    double scaled;

    for (e_item_t i = 0; i < TOT_ITEM_NB; i++) {
        scaled = item_map[i].spawn_frequency / res->time_scale;
        set_timeout(&(res->resources_spawn[i]), scaled);
    }
    set_min_timeout(res, res->resources_spawn);
}
