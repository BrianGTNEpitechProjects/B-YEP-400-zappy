/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zworld.h"
#include "zcommands.h"

void set_to_next_command(trantorian_t *t)
{
    command_t *command = &t->queue[t->command_ind];

    t->command_ind = \
(unsigned char)((t->command_ind + 1) % COMMAND_QUEUE_LEN);
    command->code = EMPTY;
    command->remaining_time = .0;
    memset(command->arg, 0, ARG_BUFFER_SIZE);
}