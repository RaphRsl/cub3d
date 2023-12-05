/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:37 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 19:00:02 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_free_int_i(int **arrays, int index) {
    
	int	i;

	i = 0;
	if (arrays == NULL || index < 0) {
        return;
    }
    while (i < index)
{
        free(arrays[i]);
        arrays[i] = NULL;
		i++;
    }
	free(arrays);
	arrays = NULL;
}

void	ft_free_arrays_i(char **arrays, int index)
{
	int	i;

	i = 0;
	if (index == -1)
	{
		while (arrays[i])
		{
			if (arrays[i])
				free(arrays[i]);
			i++;
		}
		free(arrays);
		return ;
	}
	while (i < index)
	{
		if (arrays[i])
			free(arrays[i]);
		i++;
	}
	free(arrays);
}
