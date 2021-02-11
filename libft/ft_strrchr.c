/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:48:21 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/08 02:15:24 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int caracter)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == caracter)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
