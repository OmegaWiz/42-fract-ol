# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 08:16:18 by kkaiyawo          #+#    #+#              #
#    Updated: 2023/04/11 15:24:18 by kkaiyawo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fractol

SRCS			=	fractol.c mlx_utils.c mandelbrot.c

SRC_DIR			=	./src/
LIB_DIR			=	./lib/
BUILD_DIR		=	./build/

SRC				=	${addprefix ${BUILD_DIR},${SRCS}}
OBJ				=	${SRC:.c=.o}

CC				=	gcc
CFLAG			=	-g -Wall -Wextra -Werror -O3

all:			library ${BUILD_DIR} ${NAME}

library:
					find ${LIB_DIR} -mindepth 1 -maxdepth 1 -exec make -C {} \;

clean:
					rm -f ${OBJ}

fclean:			clean
					rm -f ${NAME}

re:				fclean all

${BUILD_DIR}:
					mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
					${CC} -Imlx -c -o $@ $^

${NAME}:		${OBJ}
					${CC} ${OBJ} -Lmlx -lmlx -lm -framework OpenGL -framework AppKit ${wildcard ${LIB_DIR}*/*.a} -o ${NAME} ${CFLAG}

.PHONY:			all library clean fclean re
