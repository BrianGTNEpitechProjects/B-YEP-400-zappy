/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** queue_access.c
*/

/* Created the 1/4/19 at 5:47 PM by jfrabel */

#include "queue.h"

void *queue_front(queue_t queue)
{
    return (list_get_elem_at_front(queue));
}