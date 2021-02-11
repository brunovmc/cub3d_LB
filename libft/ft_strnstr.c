/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:48:32 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/12 03:46:30 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *largestr, const char *smallstr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (smallstr[0] == '\0')
		return ((char *)&largestr[0]);
	while (largestr[i] != '\0' && (i + j) < len)
	{
		if (largestr[i + j] == smallstr[j])
			j++;
		else
		{
			i++;
			j = 0;
		}
		if (smallstr[j] == '\0')
			return ((char *)&largestr[i]);
	}
	return (0);
}
