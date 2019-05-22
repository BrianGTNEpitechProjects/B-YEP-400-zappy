/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** map_access.c
*/

/* Created the 1/4/19 at 6:44 PM by jfrabel */

#include <stddef.h>
#include <stdio.h>
#include "map.h"

void *map_get_elem(map_t map, void *key, key_comparator_t key_cmp)
{
    list_t elem = NULL;

    key_cmp_container(true, key_cmp);
    elem = list_get_first_node_with_value(map, &(pair_t){key, NULL}, \
&pair_comparator);
    if (elem == NULL)
        return (NULL);
    return (((pair_t *)elem->value)->value);
}