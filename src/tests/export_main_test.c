/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/26 13:52:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/export_tests.h"

int	g_current_sig = 0;

void	init_shell(int argc, char **argv, char **envp, t_shell *shell)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = copy_env(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		i;

	i = 0;
	init_shell(argc, argv, envp, &shell);
	test_export(parse_evar);
	while (shell.envp[i])
		free(shell.envp[i++]);
	free(shell.envp);
	return (0);
}
