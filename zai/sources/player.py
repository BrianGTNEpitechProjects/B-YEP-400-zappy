#!/usr/bin/env python3

from main import map_size


class Player:
    def __init__(self):
        self.current_position = (0, 0)
        self.current_direction = 0
        self.current_level = 1
        self.inventory = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
            "food": 0
        }
        self.taken_objects = []
        self.thrown_objects = []

    def forward(self):
        if self.current_direction == 0:
            if self.current_position[0] == 0:
                self.current_position[0] = map_size[0] - 1
            else:
                self.current_position[0] -= 1
        elif self.current_direction == 90:
            if self.current_position[1] == map_size[1] - 1:
                self.current_position[1] = 0
            else:
                self.current_position[1] += 1
        elif self.current_direction == 180:
            if self.current_position[0] == map_size[0] - 1:
                self.current_position = 0
            else:
                self.current_position += 1
        else:
            if self.current_position[1] == 0:
                self.current_position[1] = map_size[1] - 1
            else:
                self.current_position[1] -= 1

    def right(self):
        if self.current_direction == 270:
            self.current_direction = 0
        else:
            self.current_direction += 90

    def left(self):
        if self.current_direction == 0:
            self.current_direction = 270
        else:
            self.current_direction -= 90

    def take(self, item):
        self.taken_objects.append(item)

    def throw(self, item):
        self.thrown_objects.append(item)

    def take_object(self, success):
        if success:
            self.inventory[self.taken_objects[0]] += 1
        self.taken_objects.pop(0)

    def set_object(self, success):
        if success:
            self.inventory[self.thrown_objects[0]] -= 1
        self.thrown_objects.pop(0)

    def level_up(self, level):
        self.current_level = level


player = Player()
