NAME = minishell

SRC =	src/main.c \
		src/parse/parse.c \
		src/parse/environment/environment.c src/parse/environment/utils_env.c \
		src/parse/redirections/redirections.c src/parse/redirections/utils_rdir.c \
		src/parse/utils/split_quote.c src/parse/utils/remove_quotes.c src/parse/utils/check_parse.c \
		src/signals/heredoc.c src/signals/input.c src/signals/process.c \
		src/execution/execution.c src/execution/errors.c src/execution/child_process.c src/execution/set_redirections.c \
		src/execution/here_doc.c src/execution/builtins.c src/execution/cd.c src/execution/return_val.c \
		src/execution/pwd.c src/execution/enviroment.c src/execution/unset.c src/execution/export.c src/execution/echo.c src/execution/exit.c src/execution/init_utils.c src/execution/env_sort.c src/execution/execution_utils.c

CC = gcc
RM = rm -f
LIBFT_PATH = libft/
LIBFT = libft/libft.a
FLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address
READLINE_FLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include 
#READLINE_FLAGS = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

OBJS = $(SRC:.c=.o)

RED	= '\033[1;31m'
GREEN	= '\033[1;32m'
PINK	= '\033[1;35m'
NO_COLOR	= '\033[0m'

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@echo $(PINK)"Generating executable..."$(NO_COLOR)
	$(CC) $(FLAGS) $(READLINE_FLAGS) $(OBJS) $(LIBFT) -I $(LIBFT_PATH) -o $(NAME)
	@echo $(PINK)"$(NAME) Generated!"$(NO_COLOR)

%.o: %.c
	@echo $(GREEN)"[OK]"$(NO_COLOR) "\c"
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
