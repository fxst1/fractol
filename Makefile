# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 10:57:23 by fxst1             #+#    #+#              #
#    Updated: 2018/06/12 18:43:38 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############################################################
###	TO CHANGE
#	Compilator
#	Compilator flags (and macros)
#	Executable name
#	Include header files flags
#	Librairies links
#	Sources extensions
#	Sources folder

CC = cc
FLAGS = -Wall -Wextra -Werror #-Wl,-rpath,./fmod/api/lowlevel/lib/x86_64/ -g
TARGET = fractol
INC = -I inc/ -I minilibx/ -I fmod/fmod/inc
LIBS = -lpthread -lm -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit#-lmlx -lX11 -L./fmod/api/lowlevel/lib/x86_64/ -lfmod
EXT = c
SRCDIR = src
############################################################

OBJDIR = ./obj/
SRC := $(filter %.$(EXT), $(shell find $(SRCDIR) -type f))
OBJ = $(addprefix $(OBJDIR), $(SRC:.$(EXT)=.o))

BUILD_PRINT_OBJ=$(pct)% : \033[1;34m$(1)\033[0m
BUILD_PRINT_EXEC=\033[K\033[1;32m$(1) is ready\033[0m
NB_FILES = $(words $(OBJ) $(TARGET))
compteur = 0
pct = 0
###########################################################

define show_file_obj
	$(eval compteur=$(shell echo $$(($(compteur)+1))))
	$(eval pct=$(shell echo $$((($(compteur)*100)/$(NB_FILES)))))
	@echo "\033[K$(BUILD_PRINT_OBJ)"
	@echo "\033[?25l\033[F\033[F"
endef

define show_file_exec
	$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@echo "$(BUILD_PRINT_EXEC)\033[?25h"
endef

all: $(TARGET)

$(TARGET) : $(OBJ)
	@$(CC) $(FLAGS) $(INC) -o $(TARGET) $(OBJ) $(LIBS)
	$(call show_file_exec, $(TARGET))

$(OBJDIR)%.o: %.$(EXT)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<
	$(call show_file_obj, $<)

clean:
	@rm -rf $(OBJDIR)

fclean:
	@rm -rf $(OBJDIR)
	@rm -rf $(TARGET)

install:
	cp fmod/fmod/lib/x86_64/libfmod.so.10.4 ./libfmod.so.10
	cd ./minilibx && ./configure
	cp ./minilibx/libmlx.a .

re: fclean all

push: fclean
	git add --all
	git commit -am "make push"
	git push
