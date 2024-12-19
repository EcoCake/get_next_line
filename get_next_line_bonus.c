/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezoe <amezoe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 07:59:36 by alicia            #+#    #+#             */
/*   Updated: 2024/12/19 08:13:50 by amezoe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_changing_static(char *s)
{
	char	*newstring;
	size_t	j;
	size_t	i;

	if (!s || !*s)
		return (free(s), NULL);
	j = 0;
	while (s[j] && s[j] != '\n')
		j++;
	if (!s[j])
		return (free(s), NULL);
	newstring = (char *)malloc((ft_strlen(s) - j) * sizeof(char));
	if (!newstring)
		return (free(s), NULL);
	i = 0;
	while (s[++j])
		newstring[i++] = s[j];
	newstring[i] = '\0';
	return (free(s), newstring);
}

char	*ft_get_line(char *result)
{
	char	*line;
	size_t	j;
	size_t	i;

	j = 0;
	if (result[0] == '\0')
		return (NULL);
	while (result[j] != '\n' && result[j] != '\0')
		j++;
	if (result[j] == '\n')
		j++;
	line = (char *)malloc(sizeof(char) * j + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < j)
	{
		line[i] = result[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_and_update_static(char *s, int fd, char *buffer)
{
	int	n;

	n = 1;
	while (ft_strchr(s, '\n') == NULL && n != 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(s);
			return (NULL);
		}
		buffer[n] = '\0';
		s = ft_strjoin(s, buffer);
		if (!s)
			return (NULL);
	}
	return (s);
}

char	*ft_read(char *s, int fd)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	s = read_and_update_static(s, fd, buffer);
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*res[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res[fd] = ft_read(res[fd], fd);
	if (res[fd] == NULL)
		return (NULL);
	line = ft_get_line(res[fd]);
	res[fd] = ft_changing_static(res[fd]);
	return (line);
}
