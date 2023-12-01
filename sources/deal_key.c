/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:40:03 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 14:59:21 by toteixei         ###   ########.fr       */
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
        cub3d->cam.p_y -= 0.2;
    else if (key == S_KEY)
        cub3d->cam.p_y += 0.2;
    else if (key == A_KEY)
        cub3d->cam.p_x -= 0.2;
    else if (key == D_KEY)
        cub3d->cam.p_x += 0.2;
        printf("D\n");
    return (0);
}