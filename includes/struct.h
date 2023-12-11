/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:25:27 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 15:31:38 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_configuration
{
	int				n_rows;
	int				n_column;
	int				**map;
	char			*ea_tex;
	char			*no_tex;
	char			*so_tex;
	char			*we_tex;
	char			orientation;
	int				fl_color[3];
	int				c_color[3];
	float			player_x;
	float			player_y;
}					t_configuration;

typedef struct s_img
{
	void			*mlx;
	int				*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_camera
{
	float	p_x;
	float	p_y;
	float	pd_x;
	float	pd_y;
	float	pa;
	float	fov;
	float	plane_x;
	float	plane_y;
	float	move_speed;
	float	rot_speed;
	int		x_mouse;
}					t_camera;

typedef struct s_xpm
{
	void			*n_tex;
	void			*s_tex;
	void			*e_tex;
	void			*w_tex;
	int				*n_tex_adrr;
	int				*s_tex_adrr;
	int				*e_tex_adrr;
	int				*w_tex_adrr;
	int				tex_w;
	int				tex_h;
}					t_xpm;

typedef struct s_cub3d
{
	t_configuration	*config;
	t_img			img;
	t_camera		cam;
	t_xpm			xpm;
	void			*mlx;
	void			*win;

}					t_cub3d;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct s_minimap
{
	int				bs;
	int				player_screen_x;
	int				player_screen_y;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
	int				player_map_x;
	int				player_map_y;
	int				scr_y;
	int				scr_x;
	int				x;
	int				y;
	int				n_col;
	int				n_row;
}					t_minimap;

typedef struct s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				error;
	int				e2;
	t_point			temp;
}					t_line;

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				*color;
}					t_ray;

#endif