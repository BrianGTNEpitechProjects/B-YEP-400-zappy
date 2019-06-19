/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zworld.h"

static void add_to_tile(trantorian_t *trantorian, tile_t *tile)
{
    trantorian_t * last;

    if (tile) {
        if (tile->first == NULL) {
            tile->first = trantorian;
            trantorian->neighbour = trantorian;
        } else {
            last = last_neighbour(tile->first);
            trantorian->neighbour = last->neighbour;
            last->neighbour = trantorian;
        }
    }
    trantorian->pos = tile;
}

static void remove_from_tile(trantorian_t *trantorian)
{
    trantorian_t *first = first_neighbour(trantorian);
    trantorian_t *last = last_neighbour(trantorian);
    tile_t *origin = trantorian->pos;

    if (first && last)
        last->neighbour = first;
    if (origin && origin->first == trantorian)
        origin->first = first;
}

int trantorian_move(trantorian_t *trantorian, tile_t *tile)
{
    remove_from_tile(trantorian);
    add_to_tile(trantorian, tile);
    return (0);
}

int trantorian_move_dir(trantorian_t *trantorian, e_cardinal_t dir)
{
    if (trantorian->pos == NULL)
        return (-1);
    switch (dir) {
    case NORTH:
        return (trantorian_move(trantorian, trantorian->pos->north));
    case EAST:
        return (trantorian_move(trantorian, trantorian->pos->east));
    case SOUTH:
        return (trantorian_move(trantorian, trantorian->pos->south));
    case WEST:
        return (trantorian_move(trantorian, trantorian->pos->west));
    default:
        return (0);
    }
}

int trantorian_move_forward(trantorian_t *trantorian)
{
    return (trantorian_move_dir(trantorian, trantorian->orientation));
}
