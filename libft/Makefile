NAME = libft.a

FILENAMES = \
ft_memset.c\
ft_bzero.c\
ft_memcpy.c\
ft_memccpy.c\
ft_memmove.c\
ft_memchr.c\
ft_memcmp.c\
ft_strlen.c\
ft_strdup.c\
ft_strcpy.c\
ft_strncpy.c\
ft_strcat.c\
ft_strncat.c\
ft_strlcat.c\
ft_strchr.c\
ft_strrchr.c\
ft_strstr.c\
ft_strnstr.c\
ft_strcmp.c\
ft_strncmp.c\
ft_atoi.c\
ft_isalpha.c\
ft_isdigit.c\
ft_isint.c\
ft_isalnum.c\
ft_isascii.c\
ft_isprint.c\
ft_toupper.c\
ft_tolower.c\
ft_memalloc.c\
ft_memdel.c\
ft_strnew.c\
ft_strdel.c\
ft_strclr.c\
ft_striter.c\
ft_striteri.c\
ft_strmap.c\
ft_strmapi.c\
ft_strequ.c\
ft_strnequ.c\
ft_strsub.c\
ft_strjoin.c\
ft_strtrim.c\
ft_strsplit.c\
ft_itoa.c\
ft_putchar.c\
ft_putstr.c\
ft_putendl.c\
ft_putnbr.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_gnl.c\
ft_printf.c\
not_numbers.c\
numbers.c\
base10_i.c\
base10_u.c\
base8.c\
base16_x.c\
modifier_j.c\
unicode.c\
extra.c\
colors.c\

CC = @gcc

CFLAGS = -Wall -Wextra -Werror
OBJECTS = $(FILENAMES:.c=.o)

$(NAME): $(OBJECTS)
	@echo "Making Libft"
	$(CC) $(CFLAGS) -c $(FILENAMES)
	@ar rcs $(NAME) $(OBJECTS)
	@ranlib $(NAME)

all: $(NAME)
clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
