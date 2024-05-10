/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/10 23:03:09 by pantoine         ###   ########.fr       */
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
		malloc_exec_err();
		return (1);
	}
	ft_lstadd_back(&cmd->cmd_args, new_arg);
	(*lexer_pos)++;
	return (0);
}

int	get_size_command(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	while (lexer[*lexer_pos] && lexer[*lexer_pos]->flag != PIPE)
	{
		if (lexer[*lexer_pos]->flag == WORD
			|| lexer[*lexer_pos]->flag == BUILTIN)
			add_arg_to_cmd(lexer_pos, cmd, lexer[*lexer_pos]->content);
		else if (lexer[*lexer_pos]->flag == APPEND
			|| lexer[*lexer_pos]->flag == GREATER
			|| lexer[*lexer_pos]->flag == LESSER)
		{
			if (!is_legal_token(lexer, lexer_pos, cmd))
				return (-1);
		}
		else if (lexer[*lexer_pos]->flag == HEREDOC)
		{
			if (!is_legal_heredoc(lexer, lexer_pos, cmd))
				return (-1);
		}
		if (!lexer[*lexer_pos])
			return (0);
		if (lexer[*lexer_pos]->flag == PIPE)
			break ;
	}
	return (0);
}

int	flag_add_to_node(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->flag == WORD
		|| lexer[*lexer_pos]->flag == PIPE
		|| lexer[*lexer_pos]->flag == BUILTIN)
		return (1);
	return (0);
}

int	flag_redirect_stream(t_lexer **lexer, int *lexer_pos)
{
	if (lexer[*lexer_pos]->flag == APPEND
		|| lexer[*lexer_pos]->flag == GREATER
		|| lexer[*lexer_pos]->flag == LESSER)
		return (1);
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

t_list	*init_cmdlist_size(void)
{
	t_list	*head;
	char	*begin;
	t_cmd	*first_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
		return (NULL);
	first_cmd->size_cmd = 0;
	first_cmd->in = STDIN_FILENO;
	first_cmd->out = STDOUT_FILENO;
	first_cmd->tempfile_name = NULL;
	begin = ft_strdup("BEGIN");
	first_cmd->cmd_args = ft_lstnew(begin);
	head = ft_lstnew(first_cmd);
	if (!head)
	{
		free(first_cmd);
		return (NULL);
	}
	return (head);
}

void	free_split(char **tofree)
{
	int	i;

	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}

void	print_commands(t_list *cmds)
{
	t_list	*iter;
	t_list	*args;
	t_cmd	*cmd;

	iter = cmds;
	while (iter)
	{
		cmd = iter->content;
		args = cmd->cmd_args;
		while (args)
		{
			printf("ARG: %s\n", (char *)args->content);
			args = args->next;
		}
		iter = iter->next;
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
		{
			g_current_sig = 258;
			break ;
		}
	}
	print_commands(head);
	free_lexer(lexer);
	free_cmdlist(head);
	free(contents);
	return (0);
}
