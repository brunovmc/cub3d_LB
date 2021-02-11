/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:48:01 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/08 00:19:54 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int caracter)
{
	unsigned int	i;
	char			c;
	char			*s;

	i = 0;
	c = (char)caracter;
	s = (char *)string;
	while (i <= ft_strlen(string))
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
