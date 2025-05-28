CC=cc
SANITIZERS=
#-fsanitize=address -fno-omit-frame-pointer 
LIB=-L. -lft -lreadline
CFLAGS=-Wall -Werror -Wextra -Wunused -g3 $(SANITIZERS)
SRCFILES=src/env/env.c \
src/parsing/stringutils.c \
src/env/addenv.c \
src/env/printenv.c \
src/env/envvars_utils.c \
src/exec/executils.c \
src/exec/executing.c \
src/exec/utils.c \
src/parsing/nodes.c \
src/parsing/parser1.c \
src/parsing/parser2.c \
src/parsing/tokenizer.c \
src/parsing/xbuffer.c \
src/parsing/xbuffer2.c \
src/prompt/prompt.c \
src/minishell.c \
src/builtins/ft_cd.c \
src/builtins/ft_echo.c \
src/builtins/ft_env.c \
src/builtins/ft_exit.c \
src/builtins/ft_export.c \
src/builtins/ft_pwd.c \
src/builtins/ft_unset.c \
src/parsing/args.c \
src/signals/init.c \
src/exec/t_executils.c \
src/exec/pipeutils.c \
src/exec/argutils.c \
src/exec/parsenodes.c \
src/exec/redirutils.c \
src/parsing/quote.c \
src/env/envvars.c \
src/exec/heredoc.c \
src/history/history.c \
src/exec/accessutils.c \
src/exec/redir.c \
src/exec/redirutils2.c \
src/exec/exitstatuses.c \
src/exec/new_exec.c
OBJECTS=$(patsubst src/%.c,objects/%.o,$(SRCFILES))
OBJDIR=objects
NAME=minishell

all: libft.a $(NAME)

libft.a:
	$(MAKE) -C libft/
	cp libft/libft.a .

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft/ clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C libft/ fclean
	rm -f $(NAME) libft.a

re: fclean all

.PHONY: all clean fclean re
