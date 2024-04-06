/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:14:45 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/14 18:42:46 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*m;

	if (!nmemb || !size)
	{
		m = malloc(0);
		return (m);
	}
	m = malloc(nmemb * size);
	if (!m)
		return (NULL);
	ft_bzero(m, nmemb * size);
	return (m);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*testarr;
	//char	*testarr2;
	testarr = ft_calloc(SIZE_MAX, SIZE_MAX);
	//testarr2 = calloc(4294967296, 1);
	free(testarr);
	//free(testarr2);
	return (0);
}*/
