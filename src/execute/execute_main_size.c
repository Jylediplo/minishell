/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/12 14:55:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content)
{
	t_list	*new_arg;

	new_arg = ft_lstnew(newarg_content);
	if (!new_arg)
	{
		perror_context("malloc", NULL);
		return (1);
	}
	ft_lstadd_back(&cmd->cmd_args, new_arg);
	(*lexer_pos)++;
	return (0);
}

int	filter_type_input(t_lexer **lexer, int *lexer_pos, t_list **cmds)
{
	t_cmd	*cmd;
	t_list	*current_cmd;

	current_cmd = ft_lstlast(*cmds);
	cmd = current_cmd->content;
	if (flag_add_to_node(lexer, lexer_pos))
	{
		if (add_size_arg_node(lexer, lexer_pos, cmds))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == HEREDOC)
	{
		if (!is_legal_heredoc(lexer, lexer_pos, cmd))
			return (1);
	}
	else if (flag_redirect_stream(lexer, lexer_pos))
	{
		if (!is_legal_token(lexer, lexer_pos, cmd))
			return (1);
	}
	else
		*lexer_pos += 1;
	return (0);
}

t_lexer	**init_lex(t_list *envp, char **contents)
{
	t_lexer	**lexer;
	char	*temp;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (contents[i])
	{
		temp = parse_echo(envp, contents[i]);
		free(contents[i]);
		contents[i++] = temp;
		len++;
	}
	i = 0;
	lexer = malloc(sizeof(t_lexer *) * (len + 1));
	while (contents[i])
	{
		lexer[i] = malloc(sizeof(t_lexer));
		lexer[i]->content = contents[i];
		printf("%s ", lexer[i]->content);
		if (!ft_strncmp(contents[i], "|", 1) && ft_strlen(contents[i]) == 1)
			lexer[i]->flag = PIPE;
		else if (!ft_strncmp(contents[i], "<", 1)
			&& ft_strlen(contents[i]) == 1)
			lexer[i]->flag = LESSER;
		else if (!ft_strncmp(contents[i], ">", 1)
			&& ft_strlen(contents[i]) == 1)
			lexer[i]->flag = GREATER;
		else if (!ft_strncmp(contents[i], ">>", 2)
			&& ft_strlen(contents[i]) == 2)
			lexer[i]->flag = APPEND;
		else if (!ft_strncmp(contents[i], "<<", 2)
			&& ft_strlen(contents[i]) == 2)
			lexer[i]->flag = HEREDOC;
		else
			lexer[i]->flag = WORD;
		i++;
	}
	lexer[len] = NULL;
	printf("\n\n");
	return (lexer);
}

t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin)
{
	t_list	*head;

	if (!begin_cmd->cmd_args)
	{
		perror_context("malloc", NULL);
		free(begin);
		free(begin_cmd);
		return (NULL);
	}
	head = ft_lstnew(begin_cmd);
	if (!head)
	{
		perror_context("malloc", NULL);
		free(begin);
		free(begin_cmd->cmd_args);
		free(begin_cmd);
		return (NULL);
	}
	return (head);
}

t_list	*init_cmdlist_size(void)
{
	char	*begin;
	t_cmd	*first_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
	{
		perror_context("malloc", NULL);
		return (NULL);
	}
	first_cmd->in = STDIN_FILENO;
	first_cmd->out = STDOUT_FILENO;
	first_cmd->tempfile_name = NULL;
	first_cmd->command = NULL;
	begin = ft_strdup("BEGIN");
	if (!begin)
	{
		perror_context("malloc", NULL);
		free(first_cmd);
		return (NULL);
	}
	first_cmd->cmd_args = ft_lstnew(begin);
	return (create_begin_cmd(first_cmd, begin));
}

void	print_commands(t_list *cmds)
{
	t_list	*iter;
	char	**args;
	t_cmd	*cmd;
	int		i;

	i = 0;
	iter = cmds;
	while (iter)
	{
		cmd = iter->content;
		args = cmd->command;
		while (args[i])
		{
			printf("CMD[%d]: %s\n", i, args[i]);
			i++;
		}
		printf("Input/output for this command: %d/%d\n", cmd->in, cmd->out);
		iter = iter->next;
		i = 0;
	}
}

int	get_cmdlist(char *input, t_list *envp)
{
	int		i;
	char	**contents;
	t_lexer	**lexer;
	t_list	*head;

	i = 0;
	head = init_cmdlist_size();
	if (!head)
		return (1);
	contents = ft_split(input, ' ');
	lexer = init_lex(envp, contents);
	while (lexer[i])
	{
		if (filter_type_input(lexer, &i, &head) == 1)
			break ;
	}
	if (!copy_all_cmds(head->next))
		print_commands(head->next);
	free_lexer(lexer);
	free_command_arrays(head);
	free_cmdlist(head);
	free(contents);
	return (0);
}
