NAME = ft_ping

C = gcc
CFLAGS = -Wall -Wextra -Werror -g3

OBJ_DIR = objs
SRC_DIR = $(shell find srcs -type d)
INC_DIR = ./inc

IFLAGS = -I$(INC_DIR)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

CALCUL = checksum.c mdev.c
INIT = init_ping.c
PARSING = check_args.c
PRINTS = print.c
SIGNAUX = sigquit.c sigint.c
TIME = time.c

SRC = main.c $(CALCUL) $(INIT) $(PARSING) $(PRINTS) $(SIGNAUX) $(TIME)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: test $(NAME)

$(NAME): $(OBJ)
	$(C) $(CFLAGS) $^ -o $@ -lm

$(OBJ_DIR)/%.o: %.c
	$(C) $(CFLAGS) $(IFLAGS) -c $< -o $@

test:
	@mkdir -p objs

clean:
	rm -rf $(OBJ_DIR)

re: clean all

fclean: clean
	rm -f $(NAME)

.PHONY: all clean re fclean