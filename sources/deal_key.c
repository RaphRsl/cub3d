/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:40:03 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 15:50:04 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int end_program(t_cub3d *cub3d)
{
    mlx_destroy_window(cub3d->mlx, cub3d->win);
    //liberer la memoire de config
    exit(0);
    return (0);
}

int deal_key(int key, t_cub3d *cub3d)
{
    if (key == ESC)
        end_program(cub3d);
    else if (key == W_KEY || key == KB_UP)
        move_forward(cub3d);
    else if (key == S_KEY || key == KB_DOWN)
        move_backward(cub3d);
    else if (key == A_KEY || key == KB_RIGHT)
        rotate_left(&cub3d->cam);
    else if (key == D_KEY || key == KB_LEFT)
        rotate_right(&cub3d->cam);
    else if (key == Q_KEY)
        move_to_the_left(cub3d);
    else if (key == E_KEY)
        move_to_the_right(cub3d);
    return (0);
}