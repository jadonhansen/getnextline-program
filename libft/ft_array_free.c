/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:35:50 by jhansen           #+#    #+#             */
/*   Updated: 2019/08/16 14:30:11 by jhansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != '\0')
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
