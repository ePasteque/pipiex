NAME = pipex.a

SRCS =

SRCS_BONUS =	pipex_bonus.c \
				

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c libft.h
	$(CC) $(FLAGS) -I includes -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_BONUS) $(NAME)
	ar -rcs $(NAME) $(OBJS_BONUS)  

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all bonus clean fclean re