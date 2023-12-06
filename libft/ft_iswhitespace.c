/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:28:06 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 11:23:47 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}
