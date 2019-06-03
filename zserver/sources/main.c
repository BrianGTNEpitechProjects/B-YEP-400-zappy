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
    printf("Extract\n");
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
    printf("End extract\n");
}

void on_disconnect(user_base_t *user, network_client_t *client)
{
    printf("%p %p just disconnected (or was disconnected)\n", user, client);
}

int main(__attribute__((unused)) int ac, char **av)
{
    network_manager_t *nm = create_manager();
    id_t id = add_server(nm, atoi(av[1]));
    if (id == invalid_id)
        return (84);
    struct network_server_s *server = get_server(nm, id);
    char *input = NULL;
    size_t len = 0;
    struct zuser user = {&on_extracted, &on_disconnect, 0, UNDEFINED, NULL};

    if (nm == NULL) {
        return (84);
    }
    server->default_client_disconnect_timeout = 20;
    while (getline(&input, &len, stdin) > 0) {

        printf("start1\n");
        if (strcmp("exit\n", input) == 0)
            break;
        free(input);
        printf("start2\n");
        input = NULL;
        len = 0;
        printf("start3\n");
        update_manager(nm);
        printf("start4\n");
        read_ws_clients_data(server);
        printf("start5\n");
        extract_to_users(server, (uint8_t *) "\n", 1);
        if (get_next_client_without_user(server->client_user_map) != NULL)
            get_next_client_without_user(server->client_user_map)->user = (void *)&user;
        printf("end1\n");
    }
    free(input);
    delete_manager(nm);
    return (0);
}