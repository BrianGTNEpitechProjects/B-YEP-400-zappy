/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** map_internals.c
*/

/* Created the 1/4/19 at 6:10 PM by jfrabel */

#include <stddef.h>
#include "map.h"

key_comparator_t key_cmp_container(bool store, key_comparator_t new_key_cmp)
{
    static key_comparator_t key_cmp = NULL;

    if (store) {
        key_cmp = new_key_cmp;
    }
    return (key_cmp);
}

int pair_comparator(void *first, void *second)
{
    key_comparator_t cmp = key_cmp_container(false, NULL);

    return ((*cmp)(((pair_t *)first)->key, ((pair_t *)second)->key));
}