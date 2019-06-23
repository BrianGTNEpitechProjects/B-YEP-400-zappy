/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** remove_signals.c
*/

/* Created the 19/06/2019 at 03:31 by jfrabel */

#include <stdbool.h>
#include <signal.h>
#include "zserver.h"

bool remove_sig_catch(void)
{
    if (signal(SIGINT, (__sighandler_t) NULL) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    if (signal(SIGTERM, (__sighandler_t) NULL) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    return (true);
}