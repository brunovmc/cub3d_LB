/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:37:14 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/20 21:37:23 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*frase;

	frase = b;
	i = 0;
	if (len > 0)
	{
		while (i < len)
		{
			frase[i] = c;
			i++;
		}
	}
	return (frase);
}
