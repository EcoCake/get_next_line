/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicia <alicia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:40:04 by amezoe            #+#    #+#             */
/*   Updated: 2024/12/18 00:48:58 by alicia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(char *s, int fd)
{
	char	*buffer;
	int		n;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	n = 1;
	while (ft_strchr(s, '\n') == NULL && n != 0)
		{
			n = read(fd, buffer, BUFFER_SIZE);
			if (n == -1)
			{
				free(buffer);
				return (NULL);
			}
			buffer[n] = '\0';
			s = ft_strjoin(s, buffer);
		}
		free (buffer);
		return (s);
}
char	*ft_changing_static(char *s)
{
	char	*newstring;
	size_t	i;
	size_t	j;

	j = 0;
	while (s[j] != '\n' && s[j] != '\0')
		j++;
	if (s[j] == '\0')
	{
		free (s);
		return (NULL);
	}
	newstring = (char *)malloc((ft_strlen(s) - j + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	i = 0;
	while (s[j++])
	{
		newstring[i] = s[j];
		i++;
	}
	newstring[i] = '\0';
	free (s);
	return (newstring);
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

char *get_next_line(int fd)
{
	static char	*s;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_read(s, fd);
	if (s == NULL)
		return (NULL);
	buffer = ft_get_line(s);
	s = ft_changing_static(s);
	return (buffer);
}
