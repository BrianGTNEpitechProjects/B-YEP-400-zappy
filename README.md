# ZAPPY

To fix lag issues on big maps resource spawning has been capped.
Normally resources spawn according to the following tab:

| Resource  | Rate  |
|:---------:|:-----:|
| Food      | 50/f  |
| Linemate  | 50/f  |
| Deraumere | 60/f  |
| Sibur     | 70/f  |
| Mendiane  | 80/f  |
| Phiras    | 90/f  |
| Thystame  | 100/f |

Each time resources of a type must be spawned 1 / 4 of the tiles on the map will receive a resource
but this will be capped by the nscap value (100000 by default).
You can modify this value in interactive mode using the nscap command but be aware that it can lead to serious lag issues on big maps.