/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:55 by jhansen           #+#    #+#             */
/*   Updated: 2019/06/20 16:34:39 by jhansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int		ft_line(char **content, char **line)
{
	int		i;
	char	*temp;

	temp = *content;
	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (!(ft_memcpy(line, temp, i)))
		return (-1);
	if (temp[i + 1] == '\n')
	{
		ft_memcpy(temp, (temp + (i + 2)), (ft_strlen(temp) - i + 1));
		*content = temp;
	}
	else if (temp[i + 1] == '\0')
	{
		free(*content);
	}
	//free(temp);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*current;
	static int 		i = 0;
	char			buffer[BUFF_SIZE + 1];
	char			*temp;
	char 			*str;
	int				ret;
	
	current = ft_lstnew("", 0);
	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		temp = current->content;
		temp = ft_strjoin(temp, buffer);
		current->content = temp;
		str = ft_strdup(temp);
		if (ft_strchr(temp, '\n'))
		{
			ret = ft_line(&temp, line);
			current->content = temp;
			break ;
		}
		i++;
	}
	if (ret < 0)
		return (-1);
	else if (str[ret + 1] == '\n')
	{
		free(str);
		//free(temp);
		return (1);
	}
	free(str);
	//free(temp);
	return (0);
}

int		main(int argc, char **argv)
{
    int		fd;
    char	**line;
    int		gnlret;
    int		linecount;

	linecount = 0;
	gnlret = 1;
	if (argc != 2)
	{
		printf("%s\n", "Input a file name please\n");
		return (0);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Could not find file: %s\n", argv[1]);
			return (0);
		}
		printf("Argc: %d\n", argc);
		printf("File to open: %s\n", argv[1]);
		line = ft_memalloc(sizeof(char **));
		printf("BUFF_SIZE: %d\n\n", BUFF_SIZE);
		while ((gnlret = get_next_line(fd, line)) > 0)
		{
			printf("%s\n", *line);
			printf("%d\n", gnlret);
			linecount++;
		}
		printf("\nLine count: %d\n", linecount);
		printf("Finished\n\n");
		close(fd);
	}
	return (0);
}
