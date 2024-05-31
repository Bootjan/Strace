CC = cc
C_FLAGS = -Wall -Wextra -Werror -Wpedantic

NAME = libft.a

SRC_DIR = src
SRC :=	$(wildcard $(SRC_DIR)/*.c)

OBJS_DIR = objs
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

REMOVE = rm -rf
ARRCS = ar rcs

INCLUDES = -I./includes

all: $(NAME)
.PHONY: all

$(NAME): $(OBJS_DIR) $(OBJS)
	$(ARRCS) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(REMOVE) $(OBJS)
.PHONY: clean

fclean: clean
	$(REMOVE) $(NAME)
	$(REMOVE) $(OBJS_DIR)
.PHONY: fclean

re: fclean all
.PHONY: re
