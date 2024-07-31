/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okapshai <okapshai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:18:30 by okapshai          #+#    #+#             */
/*   Updated: 2024/07/04 11:06:54 by okapshai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_string;
	int		len_prefix;
	int		len_suffix;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len_prefix = ft_strlen(s1);
	len_suffix = ft_strlen(s2);
	new_string = (char *)malloc((sizeof(char) * (len_prefix + len_suffix)) + 1);
	if (!(new_string))
		return (NULL);
	while (i++ < len_prefix - 1)
		new_string[i] = s1[i];
	while (j++ < len_suffix - 1)
	{
		new_string[i] = s2[j];
		i++;
	}
	new_string[i] = '\0';
	return ((char *)new_string);
}
