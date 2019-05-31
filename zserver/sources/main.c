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
#include "zserver.h"

bool is_alphanum(uint8_t *val, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        if (val[i] > 127)
            return (false);
    }
    return (true);
}

void on_extracted(user_base_t *user, network_client_t *client, uint8_t *extracted, size_t size)
{
    if (((struct zuser *)user)->sock_type == WEBSOCKET) {
        send_websocket(client, (uint8_t *) "G RECU", 6, 1);
    }
    if (!is_alphanum(extracted, size))
        return;
    char *tmp = calloc(size + 1, sizeof(*tmp));
    if (tmp == NULL)
        return;
    memcpy(tmp, extracted, size);
    parse_websocket_protocol(tmp, (struct zuser *) user, client);
    free(tmp);
}

void on_disconnect(user_base_t *user, network_client_t *client)
{
    printf("%p %p just disconnected (or was disconnected)\n", user, client);
}

int main(__attribute__((unused)) int ac, char **av)
{
    network_manager_t *nm = create_manager(atoi(av[1]));
    char *input = NULL;
    size_t len = 0;
    struct zuser user = {&on_extracted, &on_disconnect, UNDEFINED, NULL};

    if (nm == NULL) {
        return (84);
    }
    while (getline(&input, &len, stdin) > 0) {
        if (strcmp("exit\n", input) == 0)
            break;
        free(input);
        input = NULL;
        len = 0;
        if (accept_connections(nm) && PRINT_DEBUG) {
            fprintf(stderr, "[DEBUG] accepted client\n");
        }
        sync_buffers(nm);
        read_ws_clients_data(nm);
        extract_to_users(nm, (uint8_t *) "\n", 1);
        if (get_next_client_without_user(nm->client_user_map) != NULL)
            get_next_client_without_user(nm->client_user_map)->user = (void *)&user;
    }
    free(input);
    delete_manager(nm);
    return (0);
}