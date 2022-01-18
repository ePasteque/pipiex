/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utiles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:00:21 by lbattest          #+#    #+#             */
/*   Updated: 2022/01/18 19:01:35 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = -1;
	len = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (++j < len)
		str[j] = s1[j];
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strndup(char *s1, char c)
{
	int		i;
	int		len;
	char	*array_ptr;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] != c)
		i++;
	if (i < len && c != '\0')
		len = i + 1;
	array_ptr = malloc((len + 1) * sizeof(char));
	if (!array_ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array_ptr[i] = s1[i];
		i++;
	}
	array_ptr[i] = '\0';
	return (array_ptr);
}
