/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** map_informations.c
*/

/* Created the 1/4/19 at 5:56 PM by jfrabel */

#include "map.h"

unsigned int map_get_size(map_t map)
{
    return (list_get_size(map));
}

bool map_is_empty(map_t map)
{
    return (list_is_empty(map));
}