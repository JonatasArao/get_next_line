/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarao-de <jarao-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:36:39 by jarao-de          #+#    #+#             */
/*   Updated: 2024/11/06 10:14:39 by jarao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	char	target_char;

	target_char = (char)c;
	while (*s && *s != target_char)
		s++;
	if (*s == target_char)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		i;
	char		*str;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*substr_start;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		substr = ft_strdup("");
		if (!substr)
			return (NULL);
		return (substr);
	}
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr_start = substr;
	while (len-- > 0 && *(s + start))
		*substr++ = *(s + start++);
	*substr = '\0';
	return (substr_start);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*str_start;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str_start = str;
	while (s1_len-- > 0 && *s1)
		*str++ = *s1++;
	while (s2_len-- > 0 && *s2)
		*str++ = *s2++;
	*str = '\0';
	return (str_start);
}
