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
        return (NULL);
    }
}