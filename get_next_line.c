/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:17:49 by okapshai          #+#    #+#             */
/*   Updated: 2024/07/04 15:11:51 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*find_line(int fd, char *leftover_char, char *buffer);
static char	*extract_next_line(char *line_buffer);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*leftover_char;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(leftover_char);
		free(buffer);
		leftover_char = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = find_line(fd, leftover_char, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	leftover_char = extract_next_line(line);
	return (line);
}

static char	*extract_next_line(char *line_buffer)
{
	char	*leftover_char;
	size_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	leftover_char = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*leftover_char == '\0')
	{
		free(leftover_char);
		leftover_char = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (leftover_char);
}

static char	*ft_strchr(char *s, int c)
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

static char	*find_line(int fd, char *leftover_char, char *buffer)
{
	ssize_t	read_index;
	char	*tmp;

	read_index = 1;
	while (read_index > 0)
	{
		read_index = read(fd, buffer, BUFFER_SIZE);
		if (read_index == -1)
		{
			free(leftover_char);
			return (NULL);
		}
		else if (read_index == 0)
			break ;
		buffer[read_index] = '\0';
		if (!leftover_char)
			leftover_char = ft_strdup("");
		tmp = leftover_char;
		leftover_char = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (leftover_char);
}
