/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:36:43 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/16 01:16:53 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_delpointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*read_until_newline(int fd, char *remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_readed;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_delpointer((void *) &remainder));
	bytes_readed = 0;
	while (remainder && !ft_strchr(remainder, '\n'))
	{
		bytes_readed = read(fd, buffer, BUFFER_SIZE);
		if (bytes_readed <= 0)
			break ;
		buffer[bytes_readed] = '\0';
		temp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(temp);
	}
	free(buffer);
	if (!remainder || bytes_readed < 0)
		ft_delpointer((void *) &remainder);
	return (remainder);
}

static char	*extract_line(char **remainder)
{
	char	*line;
	char	*rest;
	size_t	line_len;
	size_t	remainder_len;

	if ((*remainder)[0] == '\0')
		return (NULL);
	line_len = 0;
	while ((*remainder)[line_len] != '\n' && (*remainder)[line_len])
		line_len++;
	if ((*remainder)[line_len] == '\n')
		line_len++;
	line = ft_substr(*remainder, 0, line_len);
	if (!line)
		return (NULL);
	remainder_len = line_len;
	while ((*remainder)[remainder_len])
		remainder_len++;
	if (remainder_len > line_len)
		rest = ft_substr(*remainder, line_len, remainder_len - line_len);
	else
		rest = NULL;
	free(*remainder);
	*remainder = rest;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
	{
		remainder = (char *)malloc(1 * sizeof(char));
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	remainder = read_until_newline(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(&remainder);
	if (!line)
		ft_delpointer((void *) &remainder);
	return (line);
}
