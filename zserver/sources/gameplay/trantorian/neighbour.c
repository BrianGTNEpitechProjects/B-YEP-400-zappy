/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zworld.h"

trantorian_t *last_neighbour(trantorian_t *self)
{
    for (trantorian_t *tmp = self->neighbour; tmp; tmp = tmp->neighbour)
        if (tmp->neighbour == self)
            return ((tmp == self) ? NULL : tmp);
    return (NULL);
}

trantorian_t *first_neighbour(trantorian_t *self)
{
    return ((self->neighbour != self) ? self->neighbour : NULL);
}

int tile_population_size(tile_t *tile)
{
    int tot = 1;

    for (trantorian_t *trantorian = tile->first; \
         trantorian && trantorian->neighbour != tile->first; \
         trantorian = trantorian->neighbour)
    {
        ++tot;
    }
    return ((tile->first) ? tot : 0);
}

void trantorian_place_on_tile(trantorian_t *trantorian, tile_t *tile)
{
    if (!trantorian)
        return;
    if (trantorian->pos)
        trantorian->pos->first = first_neighbour(trantorian);
    trantorian->pos = tile;
    if (tile) {
        if (tile->first) {
            last_neighbour(tile->first)->neighbour = trantorian;
            trantorian->neighbour = tile->first;
        } else
            trantorian->neighbour = NULL;
        tile->first = trantorian;
    }
}