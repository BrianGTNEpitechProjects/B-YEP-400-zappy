#!/usr/bin/env python3

import getopt
import socket
import select
from commands import *
from globals import *


def static_vars(**kwargs):
    def decorate(func):
        for k in kwargs:
            setattr(func, k, kwargs[k])
        return func
    return decorate


@static_vars(answers=[""])
def parse_buffer(pending_commands, buffer):
    func_table = {
        "Forward\n": forward,
        "Right\n": right,
        "Left\n": left,
        "Look\n": look,
        "Inventory\n": inventory,
        "Broadcast ": broadcast,
        "Connect_nbr\n": connect_nbr,
        "Fork\n": fork,
        "Eject\n": eject,
        "Take ": take_object,
        "Set ": set_object,
        "Incantation\n": start_incantation
    }

    parse_buffer.answers[0] += buffer
    parse_buffer.answers = parse_buffer.answers[0].split('\n')
    if "dead" in parse_buffer.answers:
        return "dead"
    for command, answer in zip(pending_commands, parse_buffer.answers):
        # print("Command : " + command + "Answer : " + answer)
        for known_command in func_table:
            if command.startswith(known_command):
                function = func_table[known_command]
                function(answer)
        pending_commands.pop(0)
        parse_buffer.answers.pop(0)
    return "ok"


def run(client_socket):
    commands = ["Forward\n"]
    pending_commands = []
    fds = [client_socket]

    while 1:
        infds, outfds, errfds = select.select(fds, fds, [], 0.1)
        if len(infds) != 0:
            buffer = client_socket.recv(1024).decode()
            print(buffer)
            if len(buffer) != 0:
                if parse_buffer(pending_commands, buffer) == "dead":
                    sys.exit(0)
                commands.append(player.new_action())
        if len(outfds) != 0 and len(commands) != 0:
            if len(commands) > 0:
                print("Commands : " + str(commands))
                client_socket.send(("".join(commands)).encode("Utf8"))
                pending_commands = commands.copy()
                commands.clear()
            print("After clear : " + str(commands))


def init_client_connection(client_socket):
    data = client_socket.recv(1024).decode()
    if data == "WELCOME\n":
        client_socket.send((name + "\n").encode("Utf8"))
    else:
        sys.exit(84)
    data = client_socket.recv(1024).decode()
    client_num, map_size = int(data.split('\n')[0]), (int(data.split('\n')[1].split(' ')[0]), int(data.split('\n')[1].split(' ')[1]))
    player.set_map_size(map_size)
    # if client_num > 0:
    #     if os.fork() == 0:
    #         connect_clients()
    #         sys.exit(0)


def connect_clients():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((socket.gethostbyname(hostname), port))
    init_client_connection(client_socket)
    run(client_socket)
    client_socket.close()


def display_usage():
    print("USAGE: " + sys.argv[0] + " -p port -n name -h machine")


def main():
    global port, name, hostname

    if len(sys.argv) == 2 and sys.argv[1] == "-help":
        display_usage()
        sys.exit(0)
    try:
        opts, args = getopt.getopt(sys.argv[1:], "p:n:h:")
    except getopt.GetoptError as error:
        print(error, file=sys.stderr)
        sys.exit(84)
    for o, a in opts:
        if o == "-p":
            port = int(a)
        elif o == "-n":
            name = a
        elif o == "-h":
            hostname = a
        else:
            print("Invalid argument.", file=sys.stderr)
            sys.exit(84)
    if port == 0 or not name:
        print("Missing argument.", file=sys.stderr)
        sys.exit(84)
    connect_clients()
    sys.exit(0)


if __name__ == '__main__':
    main()
