/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** access.c
*/

/* Created the 1/4/19 at 5:26 PM by jfrabel */

#include <stddef.h>
#include "generic_list.h"

static bool is_out_of_bound(list_t front, unsigned int position)
{
    for (unsigned int i = 0; i < position; i++) {
        if (front == NULL) {
            return (true);
        }
        front = front->next;
    }
    return (false);
}

void *list_get_elem_at_front(list_t list)
{
    if (list == NULL) {
        return (0);
    }
    return (list->value);
}

void *list_get_elem_at_back(list_t list)
{
    if (list == NULL) {
        return (0);
    }
    while (list->next != NULL) {
        list = list->next;
    }
    return (list->value);
}

void *list_get_elem_at_position(list_t list, unsigned int position)
{
    if (is_out_of_bound(list, position) || list == NULL) {
        return (0);
    }
    for (unsigned int i = 0; i < position; i++) {
        list = list->next;
    }
    return (list->value);
}

node_t *list_get_first_node_with_value(list_t list, void *value,\
value_comparator_t val_comp)
{
    node_t *found = NULL;

    while (list != NULL && found == NULL) {
        if ((*val_comp)(value, list->value) == 0) {
            found = list;
        }
        list = list->next;
    }
    return (found);
}