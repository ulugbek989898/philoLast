/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:18:40 by uisroilo          #+#    #+#             */
/*   Updated: 2022/06/22 04:34:30 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start > (size_t)ft_strlen(s))
		new_str = (char *)malloc(1);
	else if (len > (size_t)ft_strlen(s))
		new_str = (char *)malloc((size_t)(ft_strlen(s) - start));
	else
		new_str = (char *)malloc(len + 1);
	if (!s || !(new_str))
		return (0);
	i = start;
	j = 0;
	while (i < (size_t)ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**push_words(char const *s, char **ptr, char c, size_t count)
{
	size_t	j;
	size_t	i;
	size_t	item_len;

	j = 0;
	i = 0;
	while (j < count)
	{
		item_len = 0;
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		while (s[i] != c && s[i])
		{
			item_len++;
			i++;
		}
		ptr[j] = ft_substr(s, i - item_len, item_len);
		j++;
	}
	ptr[count] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**ptr;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	ptr = push_words(s, ptr, c, count);
	return (ptr);
}
