/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:30:49 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/17 13:40:07 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	is_whitespace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
	while (is_whitespace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		if (result != ((result * 10 + (nptr[i] - 48)) / 10))
			return ((sign < 0) * LONG_MIN + (sign > 0) * LONG_MAX);
		result = result * 10 + (nptr[i++] - 48);
	}
	return (sign * result);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	printf("%d\n", ft_atoi("-9223372036854775810f		djkwehuifs999!!!"));
	printf("%d", atoi("-9223372036854775810		oiqwjheoi999!!!"));
	return (0);
}*/
