/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 15:18:59 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_line(char *line, t_configuration **config)
{
	int	i;
	
	i = -1;
	while (line[++i])
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if (is_element(&line[i]))
		{
				if (!fill_element(&line[i], config, &i))
				return (0);
			else
				return (1);
		}
		else if (is_map(&line[i]))
		{
			if (!fill_map(&line[i], config))
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

t_configuration	*fill_configuration_argument(char **file)
{
	int				i;
	t_configuration *config;
	
	i = 0;
	config = init_config_struct();
	if (!config)
		return (NULL);
	while (file[i])
	{
		if (!parse_line(file[i], &config))
			return (ft_printf("error\n"), NULL); // ne pas oublier d'implementer la liberation de memoire de la structure;
		i++;
	}
	if (!check_arguments(config))
		return (NULL);
	return (config);
}

t_configuration	*parse_map(int fd)
{
	char			*file_in_line;
	char			**file;
	char			*buffer;
	t_configuration	*config;

	file_in_line = NULL;
	buffer = get_next_line(fd);
	if (!*buffer)
		return (0);
	while (buffer)
	{
		file_in_line = ft_strjoin(file_in_line, buffer);
		if (!file_in_line)
			return (free(buffer), NULL);
		free(buffer);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
	}
	free(buffer);
	close(fd);
	file = ft_split(file_in_line, '\n');
	if (!file)
		return (close(fd), free(file_in_line), ft_printf("Malloc error\n"), NULL);
	config = fill_configuration_argument(file);
	return (close(fd), free(file_in_line), ft_free_arrays_i(file, -1), config);
}

t_configuration	*ft_configuration(char *file_path)
{
	int fd_ptr;

	if (!ft_check_file_path(file_path))
		return (NULL);
	fd_ptr = open(file_path, O_RDONLY);
	if (fd_ptr < 0)
		return (ft_printf("Error\n%s : file does not exist\n", file_path), NULL);
	return (parse_map(fd_ptr));
}