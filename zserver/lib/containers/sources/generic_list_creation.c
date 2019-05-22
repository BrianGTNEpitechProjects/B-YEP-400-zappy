/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** creation.c
*/

/* Created the 1/4/19 at 5:14 PM by jfrabel */

#include <stdlib.h>
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

bool list_add_elem_at_front(list_t *front_ptr, void *elem)
{
    list_t new_elem = malloc(sizeof(*new_elem));

    if (new_elem == NULL) {
        return (false);
    }
    new_elem->next = *front_ptr;
    new_elem->value = elem;
    *front_ptr = new_elem;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr, void *elem)
{
    list_t new_elem = malloc(sizeof(*new_elem));
    list_t current_elem = *front_ptr;

    if (new_elem == NULL) {
        return (false);
    }
    new_elem->next = NULL;
    new_elem->value = elem;
    if (*front_ptr == NULL) {
        *front_ptr = new_elem;
    } else {
        while (current_elem->next != NULL) {
            current_elem = current_elem->next;
        }
        current_elem->next = new_elem;
    }
    return (true);
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem,\
unsigned int position)
{
    list_t new_elem = NULL;
    list_t last = NULL;
    list_t current = *front_ptr;

    if (is_out_of_bound(*front_ptr, position))
        return (false);
    new_elem = malloc(sizeof(*new_elem));
    if (new_elem == NULL)
        return (false);
    new_elem->value = elem;
    for (unsigned int i = 0; i < position; i++) {
        last = current;
        current = current->next;
    }
    if (last != NULL)
        last->next = new_elem;
    else
        *front_ptr = new_elem;
    new_elem->next = current;
    return (true);
}