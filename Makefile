# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <cmarteau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 00:25:28 by marvin            #+#    #+#              #
#    Updated: 2021/09/18 01:21:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/main.c srcs/raycasting.c srcs/move.c srcs/parsing.c \
	srcs/get_next_line.c srcs/get_next_line_utils.c srcs/ft_atoi.c \
	srcs/colors.c srcs/ft_split.c srcs/sprites.c srcs/ft_keys.c \
	srcs/ft_events.c srcs/textures.c srcs/move2.c srcs/parsing2.c srcs/error.c \
	srcs/error2.c srcs/ft_strdup.c srcs/ft_color_check.c

SRCS_bonus	=	srcs/main_bonus.c srcs/raycasting_bonus.c srcs/move.c \
	srcs/parsing_bonus.c srcs/get_next_line.c srcs/get_next_line_utils.c \
	srcs/ft_atoi_bonus.c srcs/colors_bonus.c srcs/ft_split.c \
	srcs/sprites_bonus.c srcs/ft_keys.c srcs/ft_events.c srcs/textures_bonus.c \
	srcs/move2.c srcs/parsing2_bonus.c srcs/error_bonus.c srcs/error2_bonus.c \
	srcs/ft_strdup.c srcs/ft_color_check.c
	
OBJS	=	${SRCS:.c=.o}

OBJS_bonus	=	${SRCS_bonus:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g
LIB		=   -framework OpenGL -framework AppKit ./minilibx_macos/libmlx.a

LIBSRC = minilibx-linux
LIB_LINUX = -lm -lmlx_Linux -lX11 -lXext -lbsd


NAME	=	cub3D

.c	: .o	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	./minilibx-linux/libmlx.a ${OBJS}
		${CC} -L$(LIBSRC) ${CFLAGS} ${OBJS} ${LIB_LINUX} -o $(NAME)

./minilibx-linux/libmlx.a : 
			$(MAKE) -C $(LIBSRC)

bonus	:	./minilibx-linux/libmlx.a ${OBJS_bonus}
		${CC} -L$(LIBSRC) ${CFLAGS} ${OBJS_bonus} ${LIB_LINUX} -o $(NAME)

all	:	${NAME}

clean	:
			rm -rf ${OBJS}
			rm -rf ${OBJS_bonus}

fclean	:	clean
			rm -rf ${NAME}
			$(MAKE) -C $(LIBSRC)/. clean

re	:	fclean all

.PHONY	:	all clean fclean re
