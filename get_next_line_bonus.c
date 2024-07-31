/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:17:49 by okapshai          #+#    #+#             */
/*   Updated: 2024/07/05 12:39:57 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_line(int fd, char *leftover, char *buffer);
char	*extract(char *line_buffer);
char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*leftover[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(leftover[fd]);
		free(buffer);
		leftover[fd] = NULL;
		buffer = NULL;
		return (0);
	}
	if (!buffer)
		return (NULL);
	line = find_line(fd, leftover[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	leftover[fd] = extract(line);
	return (line);
}

char	*extract(char *line_buffer)
{
	char	*leftover;
	size_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	leftover = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*leftover == '\0')
	{
		free(leftover);
		leftover = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (leftover);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			to_find;

	to_find = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == to_find)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == to_find)
		return ((char *) &s[i]);
	return (NULL);
}

char	*find_line(int fd, char *leftover, char *buffer)
{
	ssize_t	read_index;
	char	*tmp;

	read_index = 1;
	while (read_index > 0)
	{
		read_index = read(fd, buffer, BUFFER_SIZE);
		if (read_index == -1)
		{
			free(leftover);
			return (NULL);
		}
		else if (read_index == 0)
			break ;
		buffer[read_index] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		tmp = leftover;
		leftover = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftover);
}
