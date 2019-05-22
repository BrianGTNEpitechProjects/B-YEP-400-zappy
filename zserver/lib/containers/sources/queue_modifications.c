/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** queue_modifications.c
*/

/* Created the 1/4/19 at 5:46 PM by jfrabel */

#include "queue.h"

bool queue_push(queue_t *queue_ptr, void *elem)
{
    return (list_add_elem_at_back(queue_ptr, elem));
}

bool queue_pop(queue_t *queue_ptr)
{
    return (list_del_elem_at_front(queue_ptr));
}