/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:17 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/31 21:31:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

static int	empty_envp(t_list **head)
{
	char	*value;
	char	current[4096];
	t_list	*envvar;

	value = ft_strdup("SHLVL=1");
	if (!value)
		free_envp_exit(*head);
	envvar = ft_lstnew(value);
	if (!envvar)
		free_envp_value_exit(*head, value);
	ft_lstadd_back(head, envvar);
	if (!getcwd(current, 4096))
	{
		perror_context("getcwd", NULL, 2);
		return (0);
	}
	value = ft_strjoin("PWD=", current);
	if (!value)
		free_envp_exit(*head);
	envvar = ft_lstnew(value);
	if (!envvar)
		free_envp_value_exit(*head, value);
	ft_lstadd_back(head, envvar);
	return (0);
}

t_list	*copy_env(char **envp)
{
	int		i;
	t_list	*envvar;
	t_list	*head;
	char	*value;

	head = NULL;
	i = 0;
	if (!envp[0])
	{
		empty_envp(&head);
		return (head);
	}
	while (envp[i])
	{
		value = ft_strdup(envp[i++]);
		if (!value)
			free_envp_exit(head);
		envvar = ft_lstnew(value);
		if (!envvar)
			free_envp_value_exit(head, value);
		ft_lstadd_back(&head, envvar);
	}
	return (head);
}

int	export_envar(t_cmd *cmd, t_shell *shell)
{
	t_evar	evar;
	int		i;
	int		last_sigerror;

	i = 1;
	last_sigerror = 0;
	while (cmd->command[i])
	{
		if (init_change_evar(shell, &evar, cmd->command[i++],
				cmd->error_pipe[1]))
			last_sigerror = g_current_sig;
	}
	if (last_sigerror)
		g_current_sig = last_sigerror;
	return (0);
}
