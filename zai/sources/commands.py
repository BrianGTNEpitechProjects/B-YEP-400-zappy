#!/usr/bin/env python3

import sys
import os
from main import connect_clients
from player import player


def forward(buffer):
    if buffer == "ok":
        player.forward()


def right(buffer):
    if buffer == "ok":
        player.right()


def left(buffer):
    if buffer == "ok":
        player.left()


def look(_):
    # TODO fill map with known entities
    return


def inventory(buffer):
    print(buffer)


def broadcast(_):
    return


def connect_nbr(buffer):
    if int(buffer) > 0:
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)


def fork(buffer):
    if buffer == "ok":
        if os.fork() == 0:
            connect_clients()
            sys.exit(0)


def eject(_):
    return


def take_object(buffer):
    if buffer == "ok":
        player.take_object(True)
    else:
        player.take_object(False)


def set_object(buffer):
    if buffer == "ok":
        player.set_object(True)
    else:
        player.set_object(False)


def start_incantation(buffer):
    if buffer != "ko":
        player.level_up(int(buffer))
