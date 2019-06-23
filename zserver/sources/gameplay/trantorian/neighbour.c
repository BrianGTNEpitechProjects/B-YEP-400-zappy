/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zworld.h"

trantorian_t *last_neighbour(trantorian_t *self)
{
    if (!self)
        return (NULL);
    for (trantorian_t *tmp = self->neighbour; tmp; tmp = tmp->neighbour)
        if (tmp->neighbour == self)
            return (tmp);
    return (NULL);
}

trantorian_t *first_neighbour(trantorian_t *self)
{
    if (!self)
        return (NULL);
    return (self->neighbour);
}

int tile_population_size(tile_t *tile)
{
    int tot = 0;
    trantorian_t *t = tile->first;

    if (t == NULL)
        return (0);
    do {
        tot++;
        t = t->neighbour;
    } while (t != tile->first);
    return (tot);
}

int tile_population_size_with_lvl(tile_t *tile, unsigned int lvl)
{
    int tot = 1;

    for (trantorian_t *trantorian = tile->first; \
         trantorian && trantorian->neighbour != tile->first; \
         trantorian = trantorian->neighbour) {
        if (trantorian->lvl == lvl)
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