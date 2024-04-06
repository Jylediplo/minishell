/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:57:37 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/15 17:58:53 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	len_int(int n)
{
	int	res;
	int	m;

	res = 1;
	m = 1;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		n *= -1;
		res++;
	}
	while (n / m >= 10)
	{
		m *= 10;
		res++;
	}
	return (res);
}

static char	*swapstr(char *r)
{
	char	temp;
	int		i;
	int		sz;

	i = -1;
	sz = ft_strlen(r) - 1;
	while (++i, i < sz)
	{
		temp = r[i];
		r[i] = r[sz];
		r[sz] = temp;
		sz--;
	}
	return (r);
}

static char	*fill_int(char *r, int n)
{
	int	i;
	int	nb;

	nb = n;
	i = 0;
	if (n < 0)
		nb *= -1;
	while (nb)
	{
		r[i] = 48 + ((nb % 10 < 0) * -(nb % 10) + (nb % 10 > 0) * (nb % 10));
		nb /= 10;
		i++;
	}
	if (n < 0)
		r[i++] = '-';
	else if (n == 0)
		r[i++] = '0';
	r[i] = '\0';
	return (swapstr(r));
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sz;

	sz = len_int(n) + 1;
	res = (char *)malloc(sz * sizeof(char));
	if (!res)
		return (NULL);
	return (fill_int(res, n));
}
/*
#include <stdio.h>

int	main(void)
{
	char	*test;

	test = ft_itoa(-2147483648);
	printf("%s", test);
	free(test);
	return (0);
}*/
