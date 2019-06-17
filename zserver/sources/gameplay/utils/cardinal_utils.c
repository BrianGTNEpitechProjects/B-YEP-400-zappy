/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include "zworld.h"

e_cardinal_t cardinal_rotate_right(e_cardinal_t dir)
{
    return ((dir + 1) % 4);
}

e_cardinal_t cardinal_rotate_left(e_cardinal_t dir)
{
    --dir;
    return ((dir < 0) ? 3 : dir);
}

char *cardinal_to_string(e_cardinal_t dir)
{
    char *map[] = {
        "NORTH",
        "EAST",
        "SOUTH",
        "WEST"
    };

    return (map[dir]);
}
