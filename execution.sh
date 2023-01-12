#!/bin/sh
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c
# -D BUFFER_SIZE=11
cc -Wall -Wextra -Werror main.c get_next_line_bonus.c get_next_line_utils_bonus.c
# -D BUFFER_SIZE=11
