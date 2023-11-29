/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:35:25 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/27 19:35:55 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int    ft_render_game(t_cub3d *cub3d)
{
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.mlx, 0, 0);
    return (0);
}