/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** find_tantorian_by.c
*/

/* Created the 18/06/2019 at 18:32 by jfrabel */

#include "graphical_protocol.h"

trantorian_t *find_trantorian_egg_by_owner_id(zappy_t *world, id_t id)
{
    trantorian_t *current;

    for (current = world->players; current != NULL; current = current->next) {
        if (current->egg_owner == id && current->is_egg)
            return (current);
    }
    return (NULL);
}

trantorian_t *find_trantorian_egg_by_id(zappy_t *world, id_t id)
{
    trantorian_t *current;

    for (current = world->players; current != NULL; current = current->next) {
        if (current->id == id && current->is_egg)
            return (current);
    }
    return (NULL);
}

trantorian_t *find_trantorian_by_id(zappy_t *world, id_t id)
{
    trantorian_t *current;

    for (current = world->players; current != NULL; current = current->next) {
        if (current->id == id)
            return (current);
    }
    return (NULL);
}

trantorian_t *find_trantorian_by_parent_id(zappy_t *world, id_t id)
{
    trantorian_t *current;

    for (current = world->players; current != NULL; current = current->next) {
        if (current->egg_owner == id)
            return (current);
    }
    return (NULL);
}