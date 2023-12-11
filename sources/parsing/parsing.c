/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 09:36:11 by toteixei         ###   ########.fr       */
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

t_configuration	*fill_config_arg(char **file, int i)
{
	t_configuration	*config;

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
			if (file[i + 1] && file[i + 1][0] == '\n')
				break ;
		}
	}
	if (!check_arguments(config))
		return (free_config(config), NULL);
	return (config);
}

char	**file_in_tab(int fd, int row, int i, int len)
{
	char	*line;
	char	**tab;
	int		column;

	column = 0;
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (ft_printf("Error\nMalloc\n"), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tab[row] = malloc_good_size(line, i, column);
		if (!tab[row])
			return (ft_free_arrays_i(tab, row),
				ft_printf("Error\nMalloc\n"), NULL);
		i = 0;
		column = 0;
		row++;
		free(line);
		line = get_next_line(fd);
	}
	tab[row] = NULL;
	return (tab);
}

t_configuration	*parse_map(int fd, int len)
{
	char			**file;
	int				i;
	int				row;
	t_configuration	*config;

	i = 0;
	row = 0;
	file = file_in_tab(fd, row, i, len);
	if (!file)
		return (close(fd), NULL);
	close(fd);
	i = -1;
	config = fill_config_arg(file, i);
	return (ft_free_arrays_i(file, -1), config);
}

t_configuration	*ft_configuration(char *file_path)
{
	int	fd_ptr;
	int	file_len;

	if (!ft_check_file_path(file_path))
		return (NULL);
	file_len = 0;
	file_len = find_file_len(file_path);
	fd_ptr = open(file_path, O_RDONLY);
	if (fd_ptr < 0)
		return (ft_printf("Error\n%s : file does not exist\n", file_path),
			NULL);
	return (parse_map(fd_ptr, file_len));
}

// t_configuration	*parse_map(int fd)
// {
// 	char			*l_file;
// 	char			**file;
// 	t_configuration	*config;

// 	l_file = file_in_line(fd);
// 	if (!l_file)
// 		return (close(fd), ft_printf("Error\nFile empty\n"), NULL);
// 	close(fd);
// 	file = ft_split(l_file, '\n');
// 	if (!file)
// 		return (free(l_file), ft_printf("Error\nMalloc"), NULL);
// 	free(l_file);
// 	config = fill_config_arg(file);
// 	return (ft_free_arrays_i(file, -1), config);
// }

// char	*file_in_line(int fd)
// {
// 	char	*buffer;
// 	char	*file_buffer;
// 	char	*l_file;

// 	l_file = NULL;
// 	buffer = get_next_line(fd);
// 	if (!buffer)
// 		return (NULL);
// 	while (buffer)
// 	{
// 		file_buffer = NULL;
// 		file_buffer = ft_strdup(l_file);
// 		if (l_file)
// 			free(l_file);
// 		l_file = NULL;
// 		l_file = ft_strjoin(file_buffer, buffer);
// 		if (!l_file)
// 			return (free(buffer), NULL);
// 		free(buffer);
// 		free(file_buffer);
// 		buffer = get_next_line(fd);
// 		if (!buffer)
// 			break ;
// 	}
// 	return (free(buffer), l_file);
// }