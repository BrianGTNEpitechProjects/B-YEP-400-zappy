/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <math.h>
#include <string.h>
#include "zcommands.h"
#include "zitem.h"

int tile_look_limit(unsigned int lvl)
{
    return ((2 * lvl) + 1);
}

tile_t *top_left_corner_tile_at(tile_t *start, e_cardinal_t dir, \
unsigned int lvl)
{
    int tmp = tile_look_limit(lvl);

    for (unsigned int i = 0; i < lvl; i++)
        start = tile_forward(start, dir);
    dir = cardinal_rotate_left(dir);
    for (int i = 0; i < tmp / 2; i++)
        start = tile_forward(start, dir);
    return (start);
}

tile_t *top_right_corner_tile_at(tile_t *start, e_cardinal_t dir, \
unsigned int lvl)
{
    int tmp = tile_look_limit(lvl);

    for (unsigned int i = 0; i < lvl; i++)
        start = tile_forward(start, dir);
    dir = cardinal_rotate_right(dir);
    for (int i = 0; i < tmp / 2; i++)
        start = tile_forward(start, dir);
    return (start);
}

static void write_tile_out(client_user_pair_t *c, tile_t *tile)
{
    trantorian_t *self = (trantorian_t *)c->user;
    int player_nb = tile_population_size(tile);
    unsigned int sz;

    for (int i = 0; i < player_nb; ++i)
        write_to_buffer(&c->client->cb_out, (const uint8_t *)"player ", 7);
    for (int i = 0; i < TOT_ITEM_NB; ++i)
        for (unsigned int j = 0; j < self->inventory[i]; ++j) {
            sz = (unsigned int)strlen((const char *)item_map[i].name);
            write_to_buffer(&c->client->cb_out, item_map[i].name, sz);
            write_to_buffer(&c->client->cb_out, (const uint8_t *)" ", 1);
        }
}

void look(client_user_pair_t *c, __attribute__((unused)) char *arg)
{
    trantorian_t *s = (trantorian_t *)c->user;
    int limit;
    e_cardinal_t right_dir = cardinal_rotate_right(s->orientation);
    tile_t *start;

    write_to_buffer(&c->client->cb_out, (const uint8_t *)"[", 1);
    for (unsigned int i = 0; i <= s->lvl; ++i) {
        start = top_left_corner_tile_at(s->pos, s->orientation, i);
        limit = tile_look_limit(i);
        for (int j = 0; j < limit; ++j) {
            write_tile_out(c, start);
            write_to_buffer(&c->client->cb_out, (const uint8_t *)",", \
(size_t)(j + 1 < limit || i < s->lvl));
            start = tile_forward(start, right_dir);
        }
    }
    write_to_buffer(&c->client->cb_out, (const uint8_t *)"]\n", 2);
}
