/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:42:03 by afadouac          #+#    #+#             */
/*   Updated: 2023/11/30 13:06:22 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*read_data(int fd, char *st_buffer)
{
	char		*buffer;
	ssize_t		read_bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buffer), free(st_buffer), NULL);
		buffer[read_bytes] = '\0';
		st_buffer = ft_strjoin(st_buffer, buffer);
		if (ft_strchr(st_buffer, '\n') != NULL || read_bytes == 0)
			break ;
	}
	return (free(buffer), st_buffer);
}

char	*get_next_line(int fd)
{
	char		*endlindex;
	char		*buffer;
	char		*s;
	static char	*st_buffer[5000];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	s = read_data(fd, st_buffer[fd]);
	endlindex = ft_strchr(s, '\n');
	if (endlindex == NULL && st_buffer[fd] != NULL)
	{
		st_buffer[fd] = NULL;
		return (s);
	}
	st_buffer[fd] = ft_substr(s, endlindex - s + 1, ft_strlen(s));
	buffer = ft_substr(s, 0, endlindex - s + 1);
	free(s);
	return (buffer);
}
