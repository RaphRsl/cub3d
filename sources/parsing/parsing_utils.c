/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:33:31 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 16:36:15 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	fill_element_quater(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(&line[*i], "WE ", 3) == 0)
	{
		if ((*config)->we_tex)
			return (ft_putstr_fd("Error\nWE key find multiple time\n", 2), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->we_tex = ft_strdup(&line[*i]);
		if (!(*config)->we_tex)
			return (0);
	}
	else
	{
		ft_putstr_fd("Error\nWrong key find in file\n", 2);
		return (0);
	}
	return (1);
}

int	find_file_len(char *path)
{
	char	*line;
	int		line_count;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	line_count = 0;
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), line_count);
}

char	*malloc_good_size(char *line, int i, int column)
{
	char	*ret;

	if (line[0] == '\n')
	{
		ret = malloc(2 * sizeof(char));
		if (!ret)
			return (NULL);
		ret[0] = line[0];
		ret[1] = '\0';
		return (ret);
	}
	if (!ft_strchr(line, '\n'))
		ret = malloc((ft_strlen(line) + 1) * sizeof(char));
	else
		ret = malloc(ft_strlen(line) * sizeof(char));
	if (!ret)
		return (NULL);
	while (line[i] && line[i] != '\n')
		ret[column++] = line[i++];
	ret[column] = '\0';
	return (ret);
}
