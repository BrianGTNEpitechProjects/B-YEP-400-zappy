/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** deletion.c
*/

/* Created the 1/4/19 at 5:18 PM by jfrabel */

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

bool list_del_elem_at_front(list_t *front_ptr)
{
    list_t new_front = *front_ptr;

    if (new_front != NULL) {
        new_front = new_front->next;
    }
    free(*front_ptr);
    *front_ptr = new_front;
    return (new_front != NULL);
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    list_t last = NULL;
    list_t current = *front_ptr;

    if (current == NULL)
        return (false);
    while (current->next != NULL) {
        last = current;
        current = current->next;
    }
    free(current);
    if (last != NULL) {
        last->next = NULL;
    } else {
        *front_ptr = NULL;
    }
    return (*front_ptr != NULL);
}

bool list_del_elem_at_position(list_t *front_ptr, unsigned int position)
{
    list_t last = NULL;
    list_t current = *front_ptr;

    if (is_out_of_bound(*front_ptr, position))
        return (false);
    for (unsigned int i = 0; i < position; i++) {
        last = current;
        current = current->next;
    }
    if (last != NULL)
        last->next = current->next;
    else
        *front_ptr = current->next;
    free(current);
    return (*front_ptr != NULL);
}

void list_clear(list_t *front_ptr)
{
    list_t last = NULL;
    list_t curr = *front_ptr;

    while (curr != NULL) {
        free(last);
        last = curr;
        curr = curr->next;
    }
    free(last);
    *front_ptr = NULL;
}