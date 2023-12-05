/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:20:26 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 15:40:29 by toteixei         ###   ########.fr       */
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

# include "../mlx_linux/mlx.h"

# define SCREEN_WIDTH 1024
# define SCREEN_HEIGTH 512
# define PI 3.1415926535

enum {
	ON_DESTROY = 17,
};

//LINUX KEYS
enum {
    A_KEY = 97,
    D_KEY = 100,
	W_KEY= 119,
	S_KEY = 115,
	ESC = 65307,
	KB_UP = 0xFF52,
	KB_DOWN = 0xFF54,
	KB_RIGHT = 0xFF51,
	KB_LEFT = 0xFF53,
};

//arrows keys

//MacOS KEYS
// enum {
// 	A_KEY = 0,
//     D_KEY = 2,
//     W_KEY = 13,
// 	S_KEY = 1,
// 	ESC = 53,
// };

int             main(int argc, char **argv);

//Parsing functions
t_configuration *ft_configuration(char *file_path);
t_configuration	*parse_map(int fd);
t_configuration	*fill_configuration_argument(char **file);
int				parse_line(char *line, t_configuration **config);
t_configuration *init_config_struct(void);
int				fill_map(char *line, t_configuration **config);
int 			fill_element(char *line, t_configuration **config, int *i);
void	        skip_whitespaces(char *line, int *i);
void	        print_map(t_configuration *config);
int				fill_element_bis(char *line, t_configuration **config, int *i);
void			fill_floor_ceiling_color(int color[3], char *line, int *i);
int				is_element(char *line);
int				is_map(char *line);
int				check_arguments(t_configuration *config);
int				check_map(t_configuration *config);
int 			check_xpm_file(t_configuration *config);
int				check_floor_ceiling_color(t_configuration *config);
int				check_missing_argument(t_configuration *config);
int				ft_check_file_path(char *file);
int 			flood_fill(t_configuration *config, int **map, int y, int x);
int				**duplicate_map(t_configuration *config);
int			find_player(t_configuration *config, int *i, int *j);


//Game functions
int    ft_render_game(t_cub3d *cub3d);
void	draw_line(t_cub3d *cub3d, t_point p1, t_point p2);

//Deal key functions
int     deal_key(int key, t_cub3d *cub3d);
int     end_program(t_cub3d *cub3d);

//Camera functions
void    rotate_left(t_camera *cam);
void    rotate_right(t_camera *cam);
void    move_forward(t_cub3d *cub3d);
void    move_backward(t_cub3d *cub3d);

//Raycasting functions
void    draw_rays_3d(t_cub3d *cub3d);

//MLX functions
void	img_pixel_put(int x, int y, unsigned int color, t_cub3d *cub3d);
int     get_color(int *color);

#endif