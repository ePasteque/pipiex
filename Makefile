NAME = pipex

NAME_BONUS = pipex_bonus

LIBFT =	libft/libft.a

SRCS =	pipex.c \
		process.c \
		get_path.c \

SRCS_BONUS =	pipex_bonus.c \
				process_bonus.c \
				get_path.c \
				gnled.c \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

HEADER =	pipex.h \
			libft/libft.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

lib:
	make -C libft

%.o : %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -I includes -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(HEADER) Makefile
	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
 
clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C libft fclean

re: fclean all

.PHONY:	all lib bonus clean fclean re