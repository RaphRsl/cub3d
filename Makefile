# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 16:32:28 by toteixei          #+#    #+#              #
#    Updated: 2023/12/04 10:05:02 by toteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= 	cub3d
SRCS 		=	sources/main.c sources/configuration.c sources/game.c sources/deal_key.c \
				sources/camera_movement.c sources/raycasting.c

OBJ 		= 	$(SRCS:.c=.o)

CC			= 	cc
LIBFT 		= 	libft
RM			=	rm -f
LIB 		= 	libft.a
MATH_LIB 	= 	-lm -lz
CFLAGS 		= 	-Wall -Wextra

#LINUX
INCLUDES	=	-I libft
MINILIBX	=	mlx_linux
XFLAGS		=	-lXext -lX11

#MACOS
#INCLUDES	=	-Imlx_macos -I libft
#MINILIBX	=	mlx_macos
#XFLAGS		=	-framework OpenGL -framework AppKit

all : libs $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a $(MINILIBX)/libmlx.a $(XFLAGS) $(MATH_LIB) -o $(NAME)

%.o : %.c cub3d.h Makefile
		$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@


libs:
		@$(MAKE) -C $(LIBFT)
		@$(MAKE) -C $(MINILIBX)

clean:
		@$(RM) $(OBJ)
		@$(MAKE) clean -C $(LIBFT)
		@$(MAKE) clean -C $(MINILIBX)

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) fclean -C $(LIBFT)
		@$(MAKE) fclean -C $(MINILIBX)

re:		fclean all

.PHONY: all libs clean fclean re
