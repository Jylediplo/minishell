/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:03:12 by pantoine          #+#    #+#             */
/*   Updated: 2023/11/16 10:22:37 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_words(char const *s, char c)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			res++;
		}
		else
			i++;
	}
	return (res);
}

static int	size_word(const char *s, char c, int j)
{
	int	res;
	int	sw;

	res = 0;
	sw = 0;
	while (s[j])
	{
		if (s[j] != c)
		{
			sw = 1;
			res++;
		}
		else if (s[j] == c && sw == 1)
			break ;
		j++;
	}
	return (res);
}

static	void	delete_mall(char **res, int nmall)
{
	while (nmall >= 0)
		free(res[nmall--]);
	free(res);
}

static char	*fill_word(char const *s, char c, int *j)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc((size_word(s, c, *j) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[*j])
	{
		if (s[*j] != c)
		{
			while (s[*j] && s[*j] != c)
			{
				res[i] = s[*j];
				*j += 1;
				i++;
			}
			res[i] = '\0';
			break ;
		}
		else
			*j += 1;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		*j;
	int		n;

	i = -1;
	n = 0;
	j = &n;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (++i, i < count_words(s, c))
	{
		res[i] = fill_word(s, c, j);
		if (!(res[i]))
		{
			delete_mall(res, i);
			return (NULL);
		}
	}
	res[i] = NULL;
	return (res);
}
/*
#include <stdio.h>
int	main(void)
{
	char	**test;
	int	sizet;
	int	i;
	char	*str = "hello! there!";
	char	sep = ' ';

	i = 0;
	test = ft_split(str, sep);
	sizet = count_words(str, sep) + 1;
	printf("%d", sizet);
	
	while (i < sizet)
	{
		printf("%s\n", test[i]);
		free(test[i]);
		i++;
	}
	free(test);
	return (0);
}*/
