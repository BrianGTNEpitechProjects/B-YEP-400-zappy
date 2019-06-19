/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** No file there , just an Epitech header example
*/

#include <string.h>
#include "zworld.h"

void set_to_next_command(trantorian_t *trantorian)
{
    command_t *command = &trantorian->queue[trantorian->command_ind];

    trantorian->command_ind = \
(unsigned char)((trantorian->command_ind + 1) % COMMAND_QUEUE_LEN);
    command->code = EMPTY;
    memset(command->arg, 0, ARG_BUFFER_SIZE);
}