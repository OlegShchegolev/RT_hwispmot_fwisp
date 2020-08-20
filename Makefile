# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwisp <fwisp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/29 07:14:58 by hwispmot          #+#    #+#              #
#    Updated: 2020/07/18 13:06:03 by fwisp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang

NAME=RT

vpath %.c src
OBJ_DIR=obj/
LIB_SDL=-L sdl/lib -lSDL2 #-lOpenCL
LIB_MATH=-L/usr/lib -lm
LIB_FT=-L./libft -lft
FLAGS=-Wall -Wextra #-Werror
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
FRAMEWORKS=-framework OpenGL -framework AppKit -framework OpenCL

SRC=main.c pic.c construct_scene.c cl.c effect.c parser.c parser_functions1.c parser_functions2.c parser_functions3.c controls.c external_functions.c effect2.c effect3.c#controls2.c

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