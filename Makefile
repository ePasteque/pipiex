NAME = pipex

LIBFT =	libft/libft.a

SRCS =	pipex.c \
		process.c \
		get_path.c \

SRCS_BONUS =	pipex_bonus.c \
				process_bonus.c \
				get_path.c \
				libft/get_next_line.c \
				libft/get_next_line_utiles.c \

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

bonus: $(OBJS) $(OBJS_BONUS) $(NAME) $(LIBFT)
	$(CC) $(OBJS_BONUS) $(LIBFT) -o $(NAME) 

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all lib bonus clean fclean re