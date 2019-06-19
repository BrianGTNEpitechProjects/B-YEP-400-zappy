/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zworld.h"

tile_t *tile_forward(tile_t *tile, e_cardinal_t dir)
{
    switch (dir) {
    case NORTH:
        return (tile->north);
    case EAST:
        return (tile->east);
    case SOUTH:
        return (tile->south);
    case WEST:
        return (tile->west);
    default:
        return (0);
    }
}

int trantorian_move(trantorian_t *trantorian, tile_t *tile)
{
    trantorian_t *first = first_neighbour(trantorian);
    trantorian_t *last = last_neighbour(trantorian);

    if (first && last) {
        last->neighbour = first;
    }
    if (tile->first == trantorian) {
        tile->first = first;
    }
    trantorian->pos = tile;
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
