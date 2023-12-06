/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:22:26 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 19:39:45 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_configuration	*init_config_struct(void)
{
	t_configuration	*config;

	config = malloc(sizeof(t_configuration));
	if (!config)
		return (NULL);
	config->ea_tex = NULL;
	config->no_tex = NULL;
	config->so_tex = NULL;
	config->we_tex = NULL;
	config->map = NULL;
	config->n_column = 0;
	config->n_rows = 0;
	config->fl_color[0] = -1;
	config->fl_color[1] = -1;
	config->fl_color[2] = -1;
	config->c_color[0] = -1;
	config->c_color[1] = -1;
	config->c_color[2] = -1;
	return (config);
}
