/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:55 by jhansen           #+#    #+#             */
/*   Updated: 2019/06/19 17:15:38 by jhansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		*ft_line(char *content, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (content && content[i] != '\n')
		i++;
	if (!(ft_strsub(line, content, '\n')))
		return (-1);

	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	current;
	char			buffer[BUFF_SIZE + 1];
	char			*temp;
	int				ret;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (current->content == NULL)
			current->content = ft_strnew(1);
		temp = ft_strjoin(current->content, buffer);
		current->content = temp;
		if (ft_strchr(current->content, '\n'))
		{
			ret = ft_line(current->content, line);
			break ;
		}
	}
	if (ret < 0)
		return (-1);
	if (temp[ret] != '\0')
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
