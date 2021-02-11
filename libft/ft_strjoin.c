/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:50:44 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/20 20:35:26 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nbstrlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	total;
	char	*substring;

	total = nbstrlen(s1) + nbstrlen(s2) + 1;
	substring = (char *)malloc(total * sizeof(char));
	if (!substring)
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		substring[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		substring[i + j] = s2[j];
		j++;
	}
	substring[i + j] = '\0';
	return (substring);
}
