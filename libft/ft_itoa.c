/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcandido <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:51:22 by lcandido          #+#    #+#             */
/*   Updated: 2020/02/20 19:27:33 by lcandido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	qtdedigitos(int n)
{
	int	contadigitos;

	if (n == 0)
		return (1);
	contadigitos = 0;
	while (n > 0)
	{
		contadigitos++;
		n = n / 10;
	}
	return (contadigitos);
}

static int	definei(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char		*ft_itoa(int n)
{
	int		i;
	int		cont;
	char	*str;

	if (n == -2147483648)
		return (ft_substr("-2147483648", 0, 11));
	i = definei(n);
	if (n < 0)
		n = n * -1;
	cont = qtdedigitos(n);
	if (!(str = (char *)malloc((cont + i + 1) * sizeof(char))))
		return (NULL);
	str[cont + i] = '\0';
	if (i == 1)
		str[0] = '-';
	while (n >= 0)
	{
		str[cont-- + i - 1] = n % 10 + 48;
		n = n / 10;
		if (n == 0)
			break ;
	}
	return (str);
}
