/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:50:55 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/20 21:40:51 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compara(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	ini;
	char	*ret;
	size_t	tamanho;

	i = 0;
	if (s1 == 0 || set == 0)
		return (0);
	while (s1[i] != '\0' && compara(s1[i], set) == 1)
		i++;
	ini = i;
	i = ft_strlen(s1) - 1;
	while (i > 0 && compara(s1[i], set) == 1)
		i--;
	tamanho = i > ini ? i - ini + 1 : 0;
	ret = (char*)malloc((tamanho + 1) * sizeof(char));
	if (ret != 0)
	{
		if (tamanho == 0)
			ret[0] = '\0';
		else
			ft_strlcpy(ret, &s1[ini], tamanho + 1);
	}
	return (ret);
}
