/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:50:03 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/08 05:03:58 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;
	size_t	len;

	len = count * size;
	mem = malloc(len);
	if (mem == 0)
		return (0);
	i = 0;
	while (len > 0)
	{
		mem[i] = '\0';
		i++;
		len--;
	}
	return (mem);
}
