/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 02:28:18 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/20 18:15:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/export_tests.h"

int	g_current_sig = 0;

typedef struct s_quote
{
    int input_length;
    int output_index;
    int quote_open;
    int i;
    char current_quote;
    char *output;
} t_quote;

void init_cmd(t_quote *cmd, char *command)
{
    cmd->input_length = (int)ft_strlen(command);
    cmd->i = 0;
    cmd->quote_open = 0;
    cmd->output_index = 0;
    cmd->output = malloc(sizeof(char) * (cmd->input_length + 1));
    if (!cmd->output)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}
void current_is_quote(t_quote *cmd, char *command)
{
    if (!cmd->quote_open)
    {
        cmd->quote_open = 1;
        cmd->current_quote = command[cmd->i];
    }
    else if (cmd->current_quote == command[cmd->i])
        cmd->quote_open = 0;
    else
        cmd->output[cmd->output_index++] = command[cmd->i];
}

void current_is_not_quote(t_quote *cmd, char *command)
{
    if (cmd->quote_open)
        cmd->output[cmd->output_index++] = command[cmd->i];
    else if (command[cmd->i] != ' ')
        cmd->output[cmd->output_index++] = command[cmd->i];
    else
    {
        if (cmd->output_index > 0 && cmd->output[cmd->output_index - 1] != ' ')
            cmd->output[cmd->output_index++] = command[cmd->i];
    }
}

char *manage_quotes(t_shell *shell, char *command)
{
    t_quote cmd;

	(void)shell;
    init_cmd(&cmd, command);    
    while (cmd.i < cmd.input_length)
    {
        if (command[cmd.i] == '"' || command[cmd.i] == '\'')
            current_is_quote(&cmd, command);
        else
           current_is_not_quote(&cmd, command);
        cmd.i++;
    }
    if (cmd.quote_open)
    {
        free(cmd.output);
        printf("Error: Quote not properly closed.\n");
        return NULL;
    }
    cmd.output[cmd.output_index] = '\0';
    return (cmd.output);
}

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
	test_export(&shell, set_new_evar);
	while (shell.envp[i])
		free(shell.envp[i++]);
	free(shell.envp);
	return (0);
}
