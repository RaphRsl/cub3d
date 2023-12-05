/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:26:42 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 15:27:33 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (1);
	return (0);
}

int	is_element(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (1);
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

void	skip_whitespaces(char *line, int *i)
{
	while (ft_iswhitespace(line[*i]))
		(*i)++;
}