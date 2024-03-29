/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** Zappy
*/

#include <stdlib.h>
#include "zserver.h"

static id_t get_new_id(void)
{
    static id_t id = 0;

    id++;
    return (id);
}

trantorian_t *create_player(void)
{
    trantorian_t *res = calloc(sizeof(*res), 1);

    if (res == NULL) {
        handle_error_return("calloc: %s\n", 0);
        return (NULL);
    }
    res->egg_owner = invalid_id;
    res->id = get_new_id();
    res->base.on_disconnect = &on_disconnect;
    res->base.on_extracted = &on_extract_not_connected;
    res->life_unit = 1;
    res->inventory[FOOD] = 10;
    res->food_time = FOOD_TTL;
    res->lvl = 1;
    return (res);
}

trantorian_t *accept_player(zappy_t *zap)
{
    trantorian_t *res = create_player();

    if (res == NULL)
        return (NULL);
    res->zappy = zap;
    return (res);
}

tile_t *get_tile_relative(tile_t *tile, pos_t pos)
{
    for (int x = 0; x < abs(pos.x); x++)
        tile = (pos.x > 0) ? tile->east : tile->west;
    for (int y = 0; y < abs(pos.y); y++)
        tile = (pos.x > 0) ? tile->north : tile->south;
    return (tile);
}

void set_position_relative(trantorian_t *to_place, tile_t *tile, pos_t pos)
{
    tile = get_tile_relative(tile, pos);
    set_position(to_place, tile);
}