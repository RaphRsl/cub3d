/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 17:50:16 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	find_longest_map_line(char **file, t_configuration **config, int i)
{
	int	j;
	int	len;

	if ((*config)->n_column != 0)
		return ;
	len = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j])
			j++;
		if (j > len)
			len = j;
		i++;
	}
	(*config)->n_column = len;
}

// int	parse_line(char *line, t_configuration **config)
// {
// 	int	i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		//while (ft_iswhitespace(line[i]))
// 		//	i++;
// 		if (is_element(&line[i]))
// 		{
// 				if (!fill_element(&line[i], config, &i))
// 				return (0);
// 			else
// 				return (1);
// 		}
// 		else if (is_map(&line[i], *config))
// 		{
// 			if (!fill_map(&line[i], config))
// 				return (0);
// 			else
// 				return (1);
// 		}
// 	}
// 	return (1);
// }

t_configuration	*fill_config_arg(char **file)
{
	int				i;
	t_configuration	*config;

	i = -1;
	config = init_config_struct();
	if (!config)
		return (NULL);
	while (file[++i])
	{
		if (is_element(file[i]))
		{
			if (!fill_element(file[i], &config))
				return (free_config(config), NULL);
		}
		else if (is_map(file[i], config))
		{
			find_longest_map_line(file, &config, i);
			if (!fill_map(file[i], &config))
				return (free_config(config), NULL);
		}
	}
	if (!check_arguments(config))
		return (free_config(config), NULL);
	return (config);
}

//Un malloc mal protege ici avec le strdup, mais je ne sais pas comment faire
char	*file_in_line(int fd)
{
	char	*buffer;
	char	*file_buffer;
	char	*l_file;

	buffer = get_next_line(fd);
	if (!buffer)
		return (NULL);
	file_buffer = NULL;
	while (buffer)
	{
		file_buffer = ft_strdup(l_file);
		if (l_file)
			free(l_file);
		l_file = NULL;
		l_file = ft_strjoin(file_buffer, buffer);
		if (!l_file)
			return (free(buffer), NULL);
		(free(buffer), free(file_buffer));
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
	}
	return (free(buffer), l_file);
}

// Norme et proteger les mallocs + verifier pour les fd
t_configuration	*parse_map(int fd)
{
	char			*l_file;
	char			**file;
	t_configuration	*config;

	l_file = NULL;
	l_file = file_in_line(fd);
	if (!l_file)
		return (close(fd), ft_printf("Error\nMalloc error\n"), NULL);
	close(fd);
	file = ft_split(l_file, '\n');
	if (!file)
		return (free(l_file), ft_printf("Malloc error\n"), NULL);
	free(l_file);
	config = fill_config_arg(file);
	return (ft_free_arrays_i(file, -1), config);
}

t_configuration	*ft_configuration(char *file_path)
{
	int	fd_ptr;

	if (!ft_check_file_path(file_path))
		return (NULL);
	fd_ptr = open(file_path, O_RDONLY);
	if (fd_ptr < 0)
		return (ft_printf("Error\n%s : file does not exist\n", file_path),
			NULL);
	return (parse_map(fd_ptr));
}
