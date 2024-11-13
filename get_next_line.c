/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:36:43 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/13 23:17:47 by jarao-de         ###   ########.fr       */
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
	while (bytes_readed > 0 && !ft_strchr(remainder, '\n'))
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
	if (bytes_readed == -1)
	{
		free(remainder);
		remainder = NULL;
	}
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
	char			*new_remainder;
	unsigned int	start;
	size_t			end;

	start = 0;
	while (remainder[start] != '\n' && remainder[start])
		start++;
	if (remainder[start] == '\n')
	{
		start++;
		end = start;
		while (remainder[end])
			end++;
		new_remainder = ft_substr(remainder, start, end);
	}
	else
		new_remainder = NULL;
	free(remainder);
	remainder = new_remainder;
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
	{
		remainder = (char *)malloc(1);
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	remainder = read_until_newline(fd, remainder);
	if (!remainder)
		return (NULL);
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
