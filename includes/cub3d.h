/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:20:26 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/27 19:36:39 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include "struct.h"
# include "../mlx_macos/mlx.h"

# define SCREEN_WIDTH 1500
# define SCREEN_HEIGTH 900

int             main(int argc, char **argv);

//Parsing functions
t_configuration *ft_configuration(char *file_path);
void	        skip_whitespaces(char *line, int *i);
void	        print_map(t_configuration *config);

//Game functions
int    ft_render_game(t_cub3d *cub3d);

#endif