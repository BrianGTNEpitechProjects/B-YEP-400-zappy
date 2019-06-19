#!/usr/bin/env python3


class Player:
    def __init__(self):
        self.map_size = (0, 0)
        self.map2d = []
        self.current_position = (5, 5)
        self.current_direction = 90
        self.target = (0, 0)
        self.target_locked = False
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

    def get_current_position(self):
        return self.current_position

    def get_current_direction(self):
        return self.current_direction

    def get_current_level(self):
        return self.current_level

    def set_map_size(self, size):
        self.map_size = size

    def get_map_size(self):
        return self.map_size

    def set_map2d(self, array):
        self.map2d = array

    def get_map2d(self):
        return self.map2d

    def init_map(self):
        self.map2d = [[[] for j in range(self.map_size[1])] for i in range(self.map_size[0])]
        # self.map2d[5][6].append("food")
        # for i in range(self.map_size[0]):
        #     print(self.map2d[i])

    def append_item_to_map(self, x, y, item):
        self.map2d[x][y].append(item)

    def forward(self):
        if self.current_direction == 0:
            if self.current_position[0] == 0:
                self.current_position[0] = self.map_size[0] - 1
            else:
                self.current_position[0] -= 1
        elif self.current_direction == 90:
            if self.current_position[1] == self.map_size[1] - 1:
                self.current_position[1] = 0
            else:
                self.current_position[1] += 1
        elif self.current_direction == 180:
            if self.current_position[0] == self.map_size[0] - 1:
                self.current_position = 0
            else:
                self.current_position += 1
        else:
            if self.current_position[1] == 0:
                self.current_position[1] = self.map_size[1] - 1
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

    def new_action(self):
        globals().update()
        if self.inventory["food"] < 2 and self.reachable_target("food") and not self.target_locked:
            self.set_target("food")
            self.target_locked = True
        elif self.commands_count == 10:
            self.commands_count = 0
            return "Look\n"
        else:
            self.commands_count += 1
            return "Forward\n"
        if self.target != self.current_position and self.target_locked:
            self.commands_count += 1
            return self.go_to_target()

    def reachable_target(self, target):
        for i in range(1, int(self.map_size[0] / 2) + 1):
            for x in range(self.current_position[0] - i, self.current_position[0] + i):
                for y in range(self.current_position[1] - i, self.current_position[1] + i):
                    if target in self.map2d[(x + self.map_size[0]) % self.map_size[0]][(y + self.map_size[1]) % self.map_size[1]]:
                        return True
        return False

    def set_target(self, target):
        for i in range(1, int(self.map_size[0] / 2) + 1):
            for x in range(self.current_position[0] - i, self.current_position[0] + i):
                for y in range(self.current_position[1] - i, self.current_position[1] + i):
                    if target in self.map2d[(x + self.map_size[0]) % self.map_size[0]][(y + self.map_size[1]) % self.map_size[1]]:
                        self.target = ((x + self.map_size[0]) % self.map_size[0], (y + self.map_size[1]) % self.map_size[1])

    def go_to_target(self):
        if self.current_direction == 0:
            diff = self.current_position[0] - self.target[0]
            if diff < 0 and diff + self.map_size[0] < self.map_size[0] / 2:
                return "Forward\n"
            elif self.current_position[1] - self.target[1] < 0:
                return "Left\n"
            else:
                return "Right\n"


player = Player()
