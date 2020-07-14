# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hwispmot <hwispmot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/29 07:14:58 by hwispmot          #+#    #+#              #
#    Updated: 2019/11/20 23:06:09 by hwispmot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

NAME=RTv1

vpath %.c src
OBJ_DIR=obj/
LIB_SDL=-L sdl/lib -lSDL2
LIB_MATH=-L/usr/lib -lm
LIB_FT=-L./libft -lft
FLAGS=-Wall -Wextra -Werror
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
FRAMEWORKS=-framework OpenGL -framework AppKit -framework OpenCL

SRC=main.c pic.c construct_scene.c cl.c effect.c

OBJ=${addprefix obj/, ${SRC:%.c=%.o}}

all: ${NAME}

${NAME}: ${OBJ} libft/libft.a sdl/lib/libSDL2.a
	${CC} ${OBJ} ${LIB_FT} ${LIB_SDL} ${LIB_MATH} $(FRAMEWORKS) -o $@

${OBJ}: obj/%.o: %.c include/rtv1.h
	${CC} -c -I include/ -I libft/ -I sdl/include $(FLAGS) $< -o $@
	
clean:
	@rm -f obj/*.o
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	@make uninstall -C ./sdl
	@make clean -C ./sdl
	@rm -f $(NAME)

libft/libft.a:
	make -C ./libft

sdl/lib/libSDL2.a:
	cd sdl && ./configure --prefix=${ROOT_DIR}/sdl/ && cd ..
	make -C ./sdl
	make install -C ./sdl

re:	fclean all