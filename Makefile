# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgouasmi <pgouasmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 10:48:24 by pgouasmi          #+#    #+#              #
#    Updated: 2023/10/13 19:48:36 by pgouasmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_PATH	=	./includes/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

# OBJS = ${SRCS:.c=.o}

HEADER = pipex.h

CC = cc

FLAG = -Wall -Wextra -Werror -ggdb3

C_FILE		=	pipex.c					\
				./utils/arg_manager.c	\
				./utils/get_paths.c		\
				./utils/free.c			\
				./utils/utils.c			\
				./utils/core.c			\

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all:	$(NAME)

lib:	
	@make -C $(LIBFT_PATH)

%.o:	%.c $(HEADER) Makefile
			$(CC) $(FLAG) -I . -c $< -o $@

$(NAME): lib $(OBJ)
	$(CC) $(OBJ) $(OBJS) $(LIBFT_LIB) -o $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJ) $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re :
	make fclean
	make
