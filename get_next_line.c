/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:36:43 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/11 16:29:32 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_readed;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read(fd, buffer, BUFFER_SIZE);
		if (bytes_readed <= 0)
			break ;
		buffer[bytes_readed] = '\0';
		temp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	size_t	len;

	if (remainder[0] == '\0')
		return (NULL);
	len = 0;
	while (remainder[len] != '\n' && remainder[len])
		len++;
	if (remainder[len] == '\n')
		len++;
	line = ft_substr(remainder, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_remainder(char *remainder)
{
	char	*newline_pointer;
	char	*new_remainder;

	newline_pointer = ft_strchr(remainder, '\n');
	if (newline_pointer && newline_pointer + 1)
		new_remainder = ft_strdup(newline_pointer + 1);
	else
		new_remainder = NULL;
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	remainder = read_until_newline(fd, remainder);
	line = extract_line(remainder);
	if (!line)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	remainder = update_remainder(remainder);
	return (line);
}
