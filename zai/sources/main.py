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


@static_vars(answer="")
def parse_buffer(pending_command, buffer):
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
        "Set ": set_object
    }

    if buffer.startswith("dead"):
        return "dead"
    elif buffer.startswith("message "):
        message(buffer[8:].split('\n')[0])
        buffer = buffer.split('\n', 1)[1]
        if len(buffer) == 0:
            return "ko"
    elif buffer.startswith("Current level: "):
        player.level_up(int(buffer.split('\n')[0].split(':')[1]))
        player.reset()
        return "ok"
    elif buffer == "ko\n" and player.get_elevation_started():
        player.reset()
        return "ok"
    parse_buffer.answer += buffer
    if '\n' in parse_buffer.answer:
        for known_command in func_table:
            if pending_command.startswith(known_command):
                function = func_table[known_command]
                if function(parse_buffer.answer.split('\n')[0]):
                    parse_buffer.answer = ""
                    return "ok"
                else:
                    return "ko"
    return "ko"


def run(client_socket):
    command = "Forward\n"
    pending_command = ""
    fds = [client_socket]

    while 1:
        infds, outfds, errfds = select.select(fds, fds, [], 0.1)
        if len(infds) != 0:
            buffer = client_socket.recv(1024).decode()
            if len(buffer) != 0:
                return_value = parse_buffer(pending_command, buffer)
                if return_value == "dead":
                    sys.exit(0)
                elif return_value == "ok":
                    command = player.new_action()
            else:
                command = player.new_action()
        if len(outfds) != 0 and len(command) != 0:
            if len(command) > 0:
                try:
                    client_socket.send(command.encode("Utf8"))
                except BrokenPipeError:
                    print("Connection closed.", file=sys.stderr)
                    sys.exit(84)
                pending_command = command
                command = ""


def init_client_connection(client_socket):
    data = client_socket.recv(1024).decode()
    if data.startswith("WELCOME\n"):
        client_socket.send((name + "\n").encode("Utf8"))
    else:
        sys.exit(84)
    data = client_socket.recv(1024).decode()
    client_num, map_size = int(data.split('\n')[0]), (int(data.split('\n')[1].split(' ')[0]), int(data.split('\n')[1].split(' ')[1]))
    player.set_map_size(map_size)


def connect_clients():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client_socket.connect((socket.gethostbyname(hostname), port))
    except ConnectionRefusedError:
        print("Connection refused.", file=sys.stderr)
        sys.exit(84)
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
