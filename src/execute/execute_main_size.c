/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/09 20:24:09 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content)
{
	t_list *new_arg;

	//printf("To add: %s\n", newarg_content);
	new_arg = ft_lstnew(newarg_content);	
	if (!new_arg)
	{
		printf("fucking shit fucking bugged malloc trash PC just buy more ram bro LOOOOL1111\n");
		return (1);
	}
	//printf("Value: %s\n", (char *)cmd->cmd_args->content);
	ft_lstadd_back(&cmd->cmd_args, new_arg);
	(*lexer_pos)++;
	return (0);
}

int	get_size_command(t_lexer **lexer, int *lexer_pos, t_cmd *cmd)
{
	int		size_cmd;

	size_cmd = 0;
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
			return (size_cmd);
		if (lexer[*lexer_pos]->flag == PIPE)
			break ;
	}
	printf("Command sequence over at: %s\n", lexer[*lexer_pos]->content);
	return (size_cmd);
}

int	filter_type_input(t_lexer **lexer, int *lexer_pos, t_list **cmds)
{
	t_cmd	*cmd;
	t_list	*current_cmd;

	current_cmd = ft_lstlast(*cmds);
	cmd = current_cmd->content;
	if (lexer[*lexer_pos]->flag == WORD
		|| lexer[*lexer_pos]->flag == PIPE)
	{
		if (add_size_arg_node(lexer, lexer_pos, cmds))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == HEREDOC)
	{
		if (!is_legal_heredoc(lexer, lexer_pos, cmd))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == APPEND
			|| lexer[*lexer_pos]->flag == GREATER
			|| lexer[*lexer_pos]->flag == LESSER)
	{
		if (!is_legal_token(lexer, lexer_pos, cmd))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == BUILTIN)
	{
		*lexer_pos += 1;
	}
	else
		*lexer_pos += 1;
	return (0);
}

void free_lexer(t_lexer **lexer)
{
	int	i;

	i = 0;
	while (lexer[i])
		free(lexer[i++]);
	free(lexer);
}

t_lexer	**init_lex(char **contents)
{
	t_lexer **lexer;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (contents[i++])
		len++;
	i = 0;
	lexer = malloc(sizeof(t_lexer *) * len + 1);
	while (contents[i])
	{
		lexer[i] = malloc(sizeof(t_lexer));
		lexer[i]->content = contents[i];
		printf("%s ", lexer[i]->content);
		if (!ft_strncmp(contents[i], "|", 1) && ft_strlen(contents[i]) == 1)
			lexer[i]->flag = PIPE;
		else if (!ft_strncmp(contents[i], "<", 1) && ft_strlen(contents[i]) == 1)
			lexer[i]->flag = LESSER;
		else if (!ft_strncmp(contents[i], ">", 1) && ft_strlen(contents[i]) == 1)
			lexer[i]->flag = GREATER;
		else if (!ft_strncmp(contents[i], ">>", 2) && ft_strlen(contents[i]) == 2)
			lexer[i]->flag = APPEND;
		else if (!ft_strncmp(contents[i], "<<", 2) && ft_strlen(contents[i])== 2)
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
	t_cmd	*first_cmd;
	
	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
		return (NULL);
	first_cmd->size_cmd = 0;
	first_cmd->in = STDIN_FILENO;
	first_cmd->out = STDOUT_FILENO;
	head = ft_lstnew(first_cmd);
	if (!head)
	{
		free(first_cmd);
		return (NULL);
	}
	return (head);
}

void	free_cmdlist(t_list *cmds)
{
	t_list	*iter;
	t_list	*temp;
	t_cmd	*cmd;

	iter = cmds;
	while (iter)
	{
		temp = iter->next;
		cmd = iter->content;
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		free(cmd);
		free(iter);
		iter = temp;
	}
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

int	get_cmdlist_size(char *input)
{
	int		i;
	char	**contents;
	t_lexer **lexer;
	t_list	*head;

	i = 0;
	head = init_cmdlist_size();
	if (!head)
		return (1);
	contents = ft_split(input, ' ');
	lexer = init_lex(contents);
	while (lexer[i])
	{
		if (filter_type_input(lexer, &i, &head) == 1)
		{
			g_current_sig = 258;
			break ;
		}
	}
	free_lexer(lexer);
	print_commands(head);
	free_cmdlist(head);
	free_split(contents);
	return (0);
}
