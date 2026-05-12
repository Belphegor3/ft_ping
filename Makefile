NAME = ft_ping

C = clang
CFLAGS = -Wall -Wextra -Werror -g3

OBJ_DIR = objs
SRC_DIR = $(shell find srcs -type d)
INC_DIR = ./inc

IFLAGS = -I$(INC_DIR)

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

# CHECKERS = dimension_sign.cpp equal.cpp check_format.cpp intruder.cpp nonsense.cpp operand.cpp unknown.cpp variable.cpp
# FIND_VALUES = discriminant_calculation.cpp determine_degree.cpp find_abc.cpp
# MATHS = ft_sqrt.cpp
# PRINTS = print_reduced_form.cpp

SRC = main.cpp #$(CHECKERS) $(FIND_VALUES) $(MATHS) $(PRINTS)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: test $(NAME)

$(NAME): $(OBJ)
	$(C) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(C) $(CFLAGS) $(IFLAGS) -c $< -o $@

test:
	@mkdir -p objs

clean:
	rm -rf $(OBJ_DIR)

re: clean all

fclean: clean
	rm -f $(NAME)

.PHONY: all clean re fclean