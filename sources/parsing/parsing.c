/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/10 18:37:05 by tomteixeira      ###   ########.fr       */
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

char	*file_in_line(int fd)
{
	char	*buffer;
	char	*file_buffer;
	char	*l_file;

	l_file = NULL;
	buffer = get_next_line(fd);
	if (!buffer)
		return (NULL);
	while (buffer)
	{
		file_buffer = NULL;
		file_buffer = ft_strdup(l_file);
		if (l_file)
			free(l_file);
		l_file = NULL;
		l_file = ft_strjoin(file_buffer, buffer);
		if (!l_file)
			return (free(buffer), NULL);
		free(buffer);
		free(file_buffer);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
	}
	return (free(buffer), l_file);
}

char	**create_tab(int fd)
{
	char	*line;
	char	**tab;
	int		line_count;

	line = get_next_line(fd);
	line_count = 0;
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	tab = malloc((line_count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	else
		return (tab);
}

char *malloc_good_size(char *line)
{
	char *ret;

	if (!ft_strchr(line, '\n'))
	{
		ret = malloc((ft_strlen(line) + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		return (ret);
	}
	ret = malloc(ft_strlen(line) * sizeof(char));
	return (ret);
}

char	**file_in_tab(int fd, int row, int column, int i)
{
	char	*line;
	char	**tab;

	tab = create_tab(fd);
	if (!tab)
		return (ft_printf("Error\nMalloc\n"), NULL);
	line = get_next_line(3);
	if (!line)
		return (free(tab), ft_printf("Error\nMalloc\n"), NULL);
	while (line != NULL)
	{
		tab[row] = malloc_good_size(line);
		if (!tab[row])
			return (ft_free_arrays_i(tab, row), ("Error\nMalloc\n"), NULL);
		while (line[i] != '\0' && line[i] != '\n')
			tab[row++][column] = line[i++];
		i = 0;
		column = 0;
		free(line);
		line = get_next_line(fd);
	}
	printf("test %d\n", row);
	tab[row] = NULL;
	int j = 0;
	while (j < row)
		printf("%s\n", tab[j++]);
	return (tab);
}

// t_configuration	*parse_map(int fd)
// {
// 	char			**file;
// 	int				i;
// 	int				row;
// 	int				column;
// 	t_configuration	*config;

// 	i = 0;
// 	row = 0;
// 	column = 0;
// 	file = file_in_tab(fd, row, column, i);
// 	if (!file)
// 		return (close(fd), ft_printf("Error\nFile empty\n"), NULL);
// 	close(fd);
// 	config = fill_config_arg(file);
// 	return (ft_free_arrays_i(file, -1), config);
// }

t_configuration	*parse_map(int fd)
{
	char			*l_file;
	char			**file;
	t_configuration	*config;

	l_file = file_in_line(fd);
	if (!l_file)
		return (close(fd), ft_printf("Error\nFile empty\n"), NULL);
	close(fd);
	file = ft_split(l_file, '\n');
	if (!file)
		return (free(l_file), ft_printf("Error\nMalloc"), NULL);
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
