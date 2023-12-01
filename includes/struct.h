/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:25:27 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 10:08:51 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_configuration
{
    int         n_rows;
    int         n_column;
    int         **map;
    char        *ea_tex;
    char        *no_tex;
    char        *so_tex;
    char        *we_tex;
    char        orientation;
    int         fl_color[3];
    int         c_color[3];
    float       player_x;
    float       player_y;
}               t_configuration;

typedef struct s_img
{
	void	*mlx;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_camera
{
    float   p_x;
    float   p_y;
    float   orientation;
    float   fov;
}           t_camera;

typedef struct s_cub3d
{
    t_configuration *config;
    t_img           img;
    t_camera        cam;
    void            *mlx;
    void            *win;
    
}            t_cub3d;

#endif