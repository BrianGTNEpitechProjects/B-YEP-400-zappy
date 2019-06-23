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
#include "zcommands.h"

void spawn_resource(zappy_t *world, tile_t *tile, e_item_t type)
{
    if (type >= TOT_ITEM_NB)
        return;
    tile->content[type]++;
    nrs(world, tile, type);
}

void spawn_rand_resources(zappy_t *zap, e_item_t type)
{
    long x = 0;
    long y = 0;
    tile_t *tile = NULL;
    long ratio = 0;

    if (!zap->natural_spawn_activated)
        return;
    ratio = (int)(resources_per_tile * (zap->map_size.x * zap->map_size.y));
    if (ratio > zap->resources_spawn_cap)
        ratio = zap->resources_spawn_cap;
    for (int i = 0; i < ratio; ++i) {
        x = random() % zap->map_size.x;
        y = random() % zap->map_size.y;
        tile = &zap->map[y][x];
        spawn_resource(zap, tile, type);
    }
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
    for (e_item_t i = 1; i < TOT_ITEM_NB; i++) {
        if (timercmp(timeouts[i], min, <)) {
            min.tv_nsec = timeouts[i].tv_nsec;
            min.tv_sec = timeouts[i].tv_sec;
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
        clock_gettime(0, &last);
    clock_gettime(0, &now);
    timersub(&now, &last, &delta);
    for (e_item_t i = 0; i < TOT_ITEM_NB; i++) {
        timersub(&zap->resources_spawn[i], &delta, &zap->resources_spawn[i]);
        if (timercmp(zap->resources_spawn[i], zero, <=)) {
            scaled = item_map[i].spawn_frequency / zap->time_scale;
            spawn_rand_resources(zap, i);
            set_timeout(&zap->resources_spawn[i], scaled);
        }
    }
    last = now;
    set_min_timeout(zap, zap->resources_spawn);
}