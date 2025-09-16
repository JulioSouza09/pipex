# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/31 16:09:59 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/16 17:25:53 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
IDIR = include/
ODIR = obj/
SDIR = src/
LFTDIR = $(IDIR)libft/
SRCFILES = main.c cmd_checker.c pipex_init.c utils.c pipes.c create_pipes.c
SRC = $(patsubst %, $(SDIR)%, $(SRCFILES))
OBJ = $(patsubst %.c, $(ODIR)%.o, $(SRCFILES))
DEP = $(IDIR)pipex.h
LFT = $(LFTDIR)libft.a

BSDIR = $(SDIR)bonus/
BSRCFILES = main_bonus.c cmd_checker_bonus.c pipex_init_bonus.c \
			utils_bonus.c pipes_bonus.c create_pipes_bonus.c \
			case_heredoc_bonus.c
BSRC = $(patsubst %, $(BSDIR)%, $(BSRCFILES))
BOBJ = $(patsubst %.c, $(ODIR)%.o, $(BSRCFILES))

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
	@make clean -C $(LFTDIR) --no-print-directory
	rm -rf $(ODIR)
	rm -f .bonus

fclean: clean
	@make fclean -C $(LFTDIR) --no-print-directory
	rm -f $(NAME)

re: fclean all

bonus: .bonus

.bonus: $(BOBJ) $(LFT)
	rm -f $(NAME)
	$(CC) $(CFLAGS) $(BOBJ) -o $(NAME) $(LFT)
	touch .bonus

$(ODIR)%.o: $(BSDIR)%.c $(DEP)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR) -I $(LFTDIR)
	rm -f .bonus

.PHONY: all clean fclean re bonus
