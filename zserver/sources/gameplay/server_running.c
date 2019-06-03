/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** server_running.c
*/

#include <signal.h>
#include "zserver.h"

static bool global_bool(const bool *v)
{
    static bool status = true;

    if (v != NULL)
        status = *v;
    return (status);
}

static void catch_sig()
{
    bool status = false;

    global_bool(&status);
}

bool setup_catch_signals(void)
{
    if (signal(SIGINT, (__sighandler_t) &catch_sig) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    if (signal(SIGTERM, (__sighandler_t) &catch_sig) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    return (true);
}

bool remove_sig_catch(void)
{
    if (signal(SIGINT, (__sighandler_t) NULL) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    if (signal(SIGTERM, (__sighandler_t) NULL) == SIG_ERR)
        return (handle_error_return("signal: %s\n", false));
    return (true);
}

bool running(void)
{
    return (global_bool(NULL));
}
