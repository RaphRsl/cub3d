# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 16:32:28 by toteixei          #+#    #+#              #
#    Updated: 2023/12/07 16:35:47 by toteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_CYAN=\033[0;36m
COLOUR_END=\033[0m

NAME 		= 	cub3d
SRCS 		=	sources/main.c sources/game.c sources/deal_key.c \
				sources/camera_movement.c sources/raycasting.c \
				sources/parsing/parsing.c \
				sources/parsing/init_config_struct.c \
				sources/parsing/fill_element.c \
				sources/parsing/fill_element_utils.c \
				sources/parsing/check_file.c \
				sources/parsing/check_file_utils.c \
				sources/end_program.c

# OBJ 		= 	$(SRCS:.c=.o)

# CC			= 	cc
# LIBFT 		= 	libft
# RM			=	rm -f
# LIB 		= 	libft.a
# MATH_LIB 	= 	-lm -lz
# CFLAGS 		= 	-Wall -Wextra -Werror -g3

# #LINUX
# INCLUDES	=	-I libft
# MINILIBX	=	mlx_linux
# XFLAGS		=	-lXext -lX11

# #MACOS
# # INCLUDES	=	-Imlx_macos -I libft
# # MINILIBX	=	mlx_macos
# # XFLAGS		=	-framework OpenGL -framework AppKit

# all : libs $(NAME)

# $(NAME) : $(OBJ)
# 		$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a $(MINILIBX)/libmlx.a $(XFLAGS) $(MATH_LIB) -o $(NAME)

# %.o : %.c cub3d.h Makefile
# 		$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@


# libs:
# 		@$(MAKE) -C $(LIBFT)
# 		@$(MAKE) -C $(MINILIBX)

# clean:
# 		@$(RM) $(OBJ)
# 		@$(MAKE) clean -C $(LIBFT)
# 		@$(MAKE) clean -C $(MINILIBX)

# fclean:	clean
# 		@$(RM) $(NAME)
# 		@$(MAKE) fclean -C $(LIBFT)
# 		@$(MAKE) fclean -C $(MINILIBX)

# re:		fclean all

# .PHONY: all libs clean fclean re


#LINUX
#MLX := ./mlx_linux//libmlx.a
#UFLAGS := -lX11 -lXext -lm -lz
#MLX_NAME := mlx_linux

#MACOS
MLX		:=	./mlx_macos/libmlx.a
UFLAGS	:=	-lm -lz -framework OpenGL -framework AppKit
MLX_NAME := mlx_macos

CC := cc
LIBFT := ./libft/libft.a
HEADERS := ./includes/cub3d.h
CFLAGS := -Wall -Wextra -Werror
OBJS := $(SRCS:.c=.o)
RM := rm -f

.ONESHELL:


$(NAME):	  $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(UFLAGS) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "Cub3d compiled"

$(LIBFT):
	@echo "Compiling libft"
	@$(MAKE) -C libft -s

$(MLX):
	@echo "Compiling $(MLX_NAME)"
	@$(MAKE) -C $(MLX_NAME) -s

%.o : %.c $(HEADERS) Makefile
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -I ./includes -o $@
	@sleep .033
	@printf "\033[1A"
	@printf "\033[K"

all:	$(NAME)

clean:
	@echo "Cleaning files..."
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean -s
	@$(MAKE) -C $(MLX_NAME) clean -s
	@echo "↪ Finished, $(COLOUR_BLUE)files$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

fclean:	clean
	@echo "Cleaning binaries..."
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean -s
	@echo "↪ Finished, $(COLOUR_BLUE)binaries$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

re:	fclean all
	@echo "↪ Finished, $(COLOUR_BLUE)re-make$(COLOUR_END) $(COLOUR_GREEN)done$(COLOUR_END)"

.PHONY: clean fclean re all
.SILENT: all clean fclean re