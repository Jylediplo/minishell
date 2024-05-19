/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_dispatcher_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:18:12 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/19 18:24:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/evars.h"
#include "../../includes/execute.h"

int	dispatch_builtin(t_cmd *cmd, t_shell *shell)
{
	if (is_same_str(cmd->command[0], "echo"))
		efftee_echo(cmd->command);
	else if (is_same_str(cmd->command[0], "cd"))
		change_directory(cmd, shell);
	else if (is_same_str(cmd->command[0], "pwd"))
		get_pwd();
	else if (is_same_str(cmd->command[0], "export"))
		export_envar(cmd, shell);
	else if (is_same_str(cmd->command[0], "unset"))
		unset_envvar(cmd, shell);
	else if (is_same_str(cmd->command[0], "env"))
		show_me_the_way(shell->envp);
	return (0);
}
