# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 10:57:23 by fxst1             #+#    #+#              #
#    Updated: 2018/04/22 10:35:28 by fxst1            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
FLAGS = -Wall -Wextra -Werror -Wl,-rpath,./fmod/api/lowlevel/lib/x86_64/
NAME = fractol
INC = -I inc/ -I minilibx/ -I fmod/fmod/inc
LIBS = -lpthread -L. -lmlx -lXext -lX11 -L./fmod/api/lowlevel/lib/x86_64/ -lfmod
OBJDIR = ./obj/

SRC := $(filter %.c, $(shell find src -type f))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBS)

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR)

fclean:
	@rm -rf $(OBJDIR)
	@rm -rf $(NAME)

install:
	cp fmod/fmod/lib/x86_64/libfmod.so.10.4 ./libfmod.so.10
	cd ./minilibx && ./configure
	cp ./minilibx/libmlx.a .

re: fclean all

push: fclean
	git add --all
	git commit -am "make push"
	git push
