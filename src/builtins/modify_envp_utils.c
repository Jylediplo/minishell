/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:58:33 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/28 19:11:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/evars.h"

char	*strjoin_free(char *s1, const char *s2)
{
	char	*res;

	(void)s2;
	res = ft_strjoin(s1, s2);
	if (!res)
	{
		free(s1);
		ft_putstr_fd("error: malloc failed\n", 2);
		return (NULL);
	}
	return (res);
}
