# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/31 16:09:59 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/02 15:52:30 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
IDIR = include/
ODIR = obj/
SDIR = src/
LFTDIR = $(IDIR)libft/
SRCFILES = main.c
SRC = $(patsubst %, $(SDIR)%, $(SRCFILES))
OBJ = $(patsubst %.c, $(ODIR)%.o, $(SRCFILES))
DEP = $(IDIR)pipex.h
LFT = $(LFTDIR)libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFT)

$(ODIR)%.o: $(SDIR)%.c $(DEP)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I $(LFTDIR)

$(LFT):
	@if [ ! -d $(LFTDIR) ]; then \
		git clone git@github.com:JulioSouza09/libft.git $(LFTDIR); \
		rm -rf $(LFTDIR).git; \
	fi
	make -C $(LFTDIR)

libclean:
	rm -rf $(LFTDIR)

clean:
	make clean -C $(LFTDIR)
	rm -rf $(ODIR)

fclean: clean
	make fclean -C $(LFTDIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
