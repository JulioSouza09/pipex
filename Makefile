# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/31 16:09:59 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/12 11:50:04 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
IDIR = include/
ODIR = obj/
SDIR = src/
LFTDIR = $(IDIR)libft/
SRCFILES = main.c cmd_checker.c pipex_init.c utils.c pipes.c
SRC = $(patsubst %, $(SDIR)%, $(SRCFILES))
OBJ = $(patsubst %.c, $(ODIR)%.o, $(SRCFILES))
DEP = $(IDIR)pipex.h
LFT = $(LFTDIR)libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFT)

$(ODIR)%.o: $(SDIR)%.c $(DEP)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I $(LFTDIR)

$(LFT):
	@if [ ! -d $(LFTDIR) ]; then \
		git clone git@github.com:JulioSouza09/libft.git $(LFTDIR); \
		rm -rf $(LFTDIR).git; \
	fi
	@make -C $(LFTDIR) --no-print-directory

libclean:
	rm -rf $(LFTDIR)

clean:
	#@make clean -C $(LFTDIR) --no-print-directory
	rm -rf $(ODIR)

fclean: clean
	#@make fclean -C $(LFTDIR) --no-print-directory
	rm -f $(NAME)

re: fclean all

#.PHONY: all clean fclean re
