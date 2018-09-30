ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
EXEC = malloc_test
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
SRC = support.c ft_malloc.c ft_free.c ft_realloc.c show_alloc.c
OBJ = $(SRC:.c=.o)

FT_LNK = -L ./libft -lft

.PHONY: clean fclean all re

$(NAME): $(OBJ) main.o libft/libft.a
	@echo "Compiling ..."
	@rm -f libft_malloc.so
	$(CC) -shared $(CFLAGS) $(FT_LNK) $(OBJ) -o $(NAME)
	$(CC) $(CFLAGS) $(FT_LNK) $(OBJ) main.o -o $(EXEC)
	@ln -sv $(NAME) libft_malloc.so

libft/libft.a:
	@make -C libft

clean:
	@echo "Cleaning"
	@rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f libft_malloc.so
	@rm -f $(EXEC)
	@make fclean -C libft

all: $(NAME)

re:	fclean all
