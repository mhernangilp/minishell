NAME = minishell

SRC = src/main.c src/parse.c

CC = gcc
RM = rm -f
LIBFT_PATH = libft/
LIBFT = libft/libft.a
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=addres
READLINE_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include 
#READLINE_FLAGS = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

OBJS = $(SRC:.c=.o)

RED	= '\033[1;31m'
GREEN	= '\033[1;32m'
NO_COLOR	= '\033[0m'

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@echo $(GREEN)"Generating executable..."$(NO_COLOR)
	$(CC) $(FLAGS) $(READLINE_FLAGS) $(OBJS) $(LIBFT) -I $(LIBFT_PATH) -o $(NAME)
	@echo $(GREEN)"$(NAME) Generated!"$(NO_COLOR)

%.o: %.c
	$(CC) $(FLAGS) -I $(LIBFT_PATH) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	$(RM) $(OBJS)
	@echo $(RED)"minishell OBJS were deleted"$(NO_COLOR)

fclean: clean
	$(RM) $(LIBFT)
	@echo $(RED)"libft.a deleted"$(NO_COLOR)
	$(RM) $(NAME)
	@echo $(RED)"$(NAME) deleted"$(NO_COLOR)

re: fclean all

n:
	"norminette"
