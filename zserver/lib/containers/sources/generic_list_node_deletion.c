/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** generic_list.c
*/

/* Created the 1/4/19 at 6:12 PM by jfrabel */

#include <stddef.h>
#include <stdlib.h>
#include "generic_list.h"

bool list_del_node(list_t *front_ptr, node_t *node_ptr)
{
    list_t last = NULL;
    list_t curr = *front_ptr;

    while (curr != NULL && curr != node_ptr) {
        last = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return (false);
    }
    if (last != NULL) {
        last->next = curr->next;
    } else {
        *front_ptr = curr->next;
    }
    free(curr);
    return (true);
}