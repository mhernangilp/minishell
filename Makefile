NAME = minishell

SRC = main.c

RM = rm -f
CC = gcc
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=addres
READLINE_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include 
#READLINE_FLAGS = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

OBJS = $(SRC:.c=.o)

RED	= '\033[1;31m'
GREEN	= '\033[1;32m'
NO_COLOR	= '\033[0m'

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)"Generating executable..."$(NO_COLOR)
	$(CC) $(FLAGS) $(READLINE_FLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN)"$(NAME) Generated!"$(NO_COLOR)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo $(RED)"OBJS were deleted"$(NO_COLOR)

fclean: clean
	$(RM) $(NAME)
	@echo $(RED)"$(NAME) deleted"$(NO_COLOR)

re: fclean all

n:
	"norminette"
