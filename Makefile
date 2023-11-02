# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 10:48:24 by pgouasmi          #+#    #+#              #
#    Updated: 2023/11/02 18:18:29 by pgouasmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLOR
_GREEN = \033[92m
_YELLOW = \033[33m
_RED = \033[31m

#POLICE
_END = \033[0m
_BOLD = \033[1m

NAME = pipex
CFLAGS = -Wall -Wextra -Werror -IIncludes
RM = @rm -rf
CC = @cc
DIR = @mkdir -p
PRINT = @echo
HEADER = Includes/pipex.h
LIBFT = Libft/libft.a
MAKE_LIBFT = @make -C Libft
CLEAN_LIBFT = @make clean -C Libft
FCLEAN_LIBFT = @make fclean -C Libft
NORM = @norminette | awk '$$NF!="OK!" {print "$(_RED)" $$0 "\033[0;0m"}'
FILES = pipex\
		utils/arg_manager\
		utils/core\
		utils/free\
		utils/get_paths\
		utils/utils
SRCS = $(addsuffix .c, $(addprefix Sources/, $(FILES)))
OBJS = $(addsuffix .o, $(addprefix Objects/, $(FILES)))

$(NAME): $(OBJS) $(LIBFT)
	$(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	$(NORM)
	$(PRINT) "${_BOLD}Norminette done.${_END}"
	$(PRINT) "\n${_YELLOW}Making $(NAME)...${_END}"
	$(CC) $(OBJS) -o $(NAME) $(LIBFT)
	$(PRINT) "${_BOLD}${_GREEN}$(NAME) done.\a${_END}"

$(LIBFT): force
	$(PRINT) "\n${_YELLOW}Checking Libft...${_END}"
	$(MAKE_LIBFT)

Objects/%.o: Sources/%.c Makefile $(HEADER)
	$(DIR) Objects
	$(DIR) Objects/utils
	$(PRINT) "Compiling ${_BOLD}$<$(_END)..."
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

clean:
	$(CLEAN_LIBFT)
	$(PRINT) "\n${_BOLD}Cleaning Objects...${_END}"
	$(RM) $(OBJS)
	$(PRINT) "${_BOLD}${_GREEN}Objects cleaned.\a${_END}"

fclean:
	$(FCLEAN_LIBFT)
	$(PRINT) "\n${_BOLD}Cleaning Objects...${_END}"
	$(RM) $(OBJS)
	$(PRINT) "${_RED}Deleting $(NAME)...${_END}"
	$(RM) $(NAME)
	$(PRINT) "${_RED}Deleting Objects directory...${_END}"
	$(RM) Objects
	$(PRINT) "${_GREEN}Objects cleaned.${_END}"
	$(PRINT) "${_GREEN}Objects directory deleted.${_END}"
	$(PRINT) "${_GREEN}$(NAME) deleted.\a\n${_END}"

re: fclean all

norminette:
	$(PRINT) "\n${_BOLD}Waiting for norminette...${_END}"
	$(NORM)
	$(PRINT) "${_BOLD}Norminette done.${_END}"

force:

.PHONY: all clean fclean re norminette force
