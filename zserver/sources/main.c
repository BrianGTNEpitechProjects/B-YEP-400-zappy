/*
** EPITECH PROJECT, 2018
** PSU_bootstrap_zappy_2018
** File description:
** main.c
*/

/* Created the 13/05/2019 at 11:10 by jfrabel */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "network_manager.h"

void on_extracted(user_base_t *user, network_client_t *client, uint8_t *extracted, size_t size)
{
    printf("Just extracted %ld bytes [%.*s] from %p %p\n", size, (int)size, extracted, user, client);
}

void on_disconnect(user_base_t *user, network_client_t *client)
{
    printf("%p %p just disconnected (or was disconnected)\n", user, client);
}

struct test_user {
    on_extracted_func on_extracted;
    on_disconnect_func on_disconnect;
    time_t user_select_timeout;
};

int main(void)
{
    network_manager_t *nm = create_manager(4242);
    char *input = NULL;
    size_t len = 0;
    struct test_user user = {&on_extracted, &on_disconnect, 0};

    if (nm == NULL) {
        return (84);
    }
    nm->default_client_disconnect_timeout = 20;
    while (getline(&input, &len, stdin) > 0) {
        if (strcmp("exit\n", input) == 0)
            break;
        free(input);
        input = NULL;
        len = 0;
        update_manager(nm);
        extract_to_users(nm, (uint8_t *)"\n", 1);
        if (get_next_client_without_user(nm->client_user_map) != NULL)
            get_next_client_without_user(nm->client_user_map)->user = (void *)&user;
    }
    free(input);
    delete_manager(nm);
    return (0);
}