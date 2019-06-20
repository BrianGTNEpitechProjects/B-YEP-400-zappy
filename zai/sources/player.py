#!/usr/bin/env python3


class Player:
    def __init__(self):
        self.map_size = [0, 0]
        self.target_position = [0, 0]
        self.target = None
        self.current_level = 1
        self.commands_count = 0
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

    def get_current_level(self):
        return self.current_level

    def set_map_size(self, size):
        self.map_size = size

    def get_map_size(self):
        return self.map_size

    def forward(self):
        self.target_position[0] -= 1

    def right(self):
        tmp = self.target_position[0]
        self.target_position[0] = self.target_position[1]
        self.target_position[1] = -tmp

    def left(self):
        tmp = self.target_position[0]
        self.target_position[0] = -self.target_position[1]
        self.target_position[1] = tmp

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

    def new_action(self):
        globals().update()
        if self.commands_count == 10:
            self.commands_count = 0
            return "Inventory\n"
        elif self.commands_count % 2 == 0:
            self.commands_count += 1
            if not self.target:
                return "Forward\n"
            elif self.target_position[0] == 0:
                if self.target_position[1] == 0:
                    self.take(self.target)
                    self.commands_count = 1
                    command = "Take " + self.target + "\n"
                    self.target = None
                    return command
                elif self.target_position[1] < 0:
                    return "Left\n"
                else:
                    return "Right\n"
            elif self.target_position[0] < 0:
                if self.target_position[1] < 0:
                    return "Left\n"
                else:
                    return "Right\n"
            else:
                return "Forward\n"
        else:
            self.commands_count += 1
            return "Look\n"

    def set_target_position(self, target_position):
        if abs(target_position[0]) + abs(target_position[1]) < abs(self.target_position[0]) + abs(self.target_position[1])\
                or self.target_position == [0, 0]:
            self.target_position = target_position
            return True
        return False

    def set_target(self, target):
        self.target = target

    def update_item(self, item, quantity):
        self.inventory[item] = quantity


player = Player()
