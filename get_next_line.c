/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:55 by jhansen           #+#    #+#             */
/*   Updated: 2019/06/21 16:29:29 by jhansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

t_list	*ft_file(int fd, t_list **file)
{
	t_list	*temp;

	if (!file)
		return (NULL);
	temp = *file;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("", fd);
	ft_lstadd(file, temp);
	return (temp);
}

int		ft_line(char *content, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	temp = *line;
	while (content[i] && content[i] != '\n')
		i++;
	if (!(*line = ft_strndup(content, i)))
		return (0);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*file;
	t_list			*current;
	char			buffer[BUFF_SIZE + 1];
	char			*temp;
	int				ret;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0 || !(current = ft_file(fd, &file)))
		return (-1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		temp = current->content;
		temp = ft_strjoin(temp, buffer);
		current->content = temp;
		if (ret == 0 && current->content == '\0')
			return (0);
		if (ft_strchr(temp, '\n'))
		{
			ret = ft_line(current->content, line);
			break ;
		}
	}
	temp = current->content;
	if (temp[ret] != '\0')
	{
		current->content = ft_strdup(current->content + ret + 1);
		free(temp);
	}
	else
		ft_strclr(temp);
	return (1);
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
