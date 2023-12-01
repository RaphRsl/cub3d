/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:40:03 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 15:11:37 by toteixei         ###   ########.fr       */
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
    else if (key == W_KEY)
        move_forward(&cub3d->cam);
    else if (key == S_KEY)
        move_backward(&cub3d->cam);
    else if (key == A_KEY)
        rotate_left(&cub3d->cam);
    else if (key == D_KEY)
        rotate_right(&cub3d->cam);
        printf("D\n");
    return (0);
}