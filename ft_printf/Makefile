CC = cc
C_FLAGS = -Wall -Wextra -Werror -Wpedantic

NAME = libftprintf.a

SRC_DIR = src
SRC :=	$(wildcard $(SRC_DIR)/*.c)

OBJS_DIR = objs
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

REMOVE = rm -rf
ARRCS = ar rcs

INCLUDES = -I./includes

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MAIN = main.c

all: $(NAME)
.PHONY: all

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(ARRCS) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
.PHONY: clean

fclean:	clean
	make -C $(LIBFT_DIR) fclean
	$(REMOVE) $(NAME)
	$(REMOVE) $(OBJS_DIR)
.PHONY: fclean

re: fclean all
.PHONY: re
