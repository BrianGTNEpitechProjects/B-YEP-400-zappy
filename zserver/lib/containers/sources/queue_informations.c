/*
** EPITECH PROJECT, 2018
** cpp_d02a_2018
** File description:
** queue_informations.c
*/

/* Created the 1/4/19 at 5:45 PM by jfrabel */

#include "queue.h"

unsigned int queue_get_size(queue_t queue)
{
    return (list_get_size(queue));
}

bool queue_is_empty(queue_t queue)
{
    return (list_is_empty(queue));
}