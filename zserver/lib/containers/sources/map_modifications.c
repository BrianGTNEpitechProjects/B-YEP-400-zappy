/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** map_modifications.c
*/

/* Created the 1/4/19 at 6:25 PM by jfrabel */

#include <stddef.h>
#include <stdlib.h>
#include "map.h"

bool map_add_elem(map_t *map_ptr, void *key,\
void *value, key_comparator_t key_cmp)
{
    list_t elem = NULL;
    pair_t *new_pair = malloc(sizeof(*new_pair));

    if (new_pair == NULL) {
        return (false);
    }
    new_pair->value = value;
    new_pair->key = key;
    key_cmp_container(true, key_cmp);
    elem = list_get_first_node_with_value(*map_ptr, new_pair, &pair_comparator);
    if (elem != NULL) {
        free(elem->value);
        elem->value = new_pair;
    } else if (!list_add_elem_at_front(map_ptr, new_pair)) {
        free(new_pair);
        return (false);
    }
    return (true);
}

bool map_del_elem(map_t *map_ptr, void *key, key_comparator_t key_cmp)
{
    list_t elem = NULL;

    key_cmp_container(true, key_cmp);
    elem = list_get_first_node_with_value(*map_ptr, &(pair_t){key, NULL},\
&pair_comparator);
    free(elem->value);
    return (list_del_node(map_ptr, elem));
}

void map_clear(map_t *map_ptr)
{
    map_t last = NULL;
    map_t curr = *map_ptr;

    while (curr != NULL) {
        if (last != NULL)
            free(last->value);
        free(last);
        last = curr;
        curr = curr->next;
    }
    if (last != NULL)
        free(last->value);
    free(last);
    *map_ptr = NULL;
}