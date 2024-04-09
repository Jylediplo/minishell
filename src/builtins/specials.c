/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:25:37 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/09 17:25:39 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **copy_env(char **envp)
{
    char    **res;
    char    len;
    int     i;

    i = 0;
    len = 0;
    while (envp[i])
    {
        len++;
        i++;
    }
    res = malloc(sizeof(char *) * (len + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        res[i] = ft_strdup(envp[i]);
        i++;
    }
    res[i] = NULL;
    return (res);
}

void    export_envar(t_shell *shell, char *to_change)
{
    char    *evar_changed;
    char    **temp;
    int     i;

    i = 0;
    temp = ft_split(to_change, '=');
    if (!temp)
        return ;
    while (shell->envp[i])
    {
        if (!ft_strncmp(temp[0], ft_strchr(shell->envp[i], '=') - shell->envp[i], ft_strlen(temp[0])) &&
            ft_strlen(temp[0]) == ft_strlen(ft_strchr(shell->envp[i], '=') - shell->envp[i]))
        shell->envp[i] = ft_strchr(to_change, '=') + 1;
    }
}
/*
void    unset_envar(t_shell *shell)
{

}*/