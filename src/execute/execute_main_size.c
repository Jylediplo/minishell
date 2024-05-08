/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:18 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/08 00:54:22 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/evars.h"
#include "../../includes/minishell.h"

int	get_size_command(t_lexer **lexer, int *lexer_pos)
{
	int		size_cmd;

	size_cmd = 0;
	while (lexer[*lexer_pos] && (lexer[*lexer_pos]->flag == WORD
			|| lexer[*lexer_pos]->flag == BUILTIN))
	{
		size_cmd++;
		(*lexer_pos)++;
	}
	return (size_cmd);
}

int	filter_type_input(t_lexer **lexer, int *lexer_pos, t_list **cmds)
{
	void	*size_ptr;
	int		size;

	size = 0;
	size_ptr = NULL;
	if (lexer[*lexer_pos]->flag == WORD
		|| lexer[*lexer_pos]->flag == PIPE)
	{
		if (add_size_arg_node(lexer, lexer_pos, cmds))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == HEREDOC)
	{
		if (!is_legal_heredoc(lexer, lexer_pos, cmds))
			return (1);
	}
	else if (lexer[*lexer_pos]->flag == APPEND
			|| lexer[*lexer_pos]->flag == GREATER
			|| lexer[*lexer_pos]->flag == LESSER)
	{
		if (!is_legal_token(lexer, lexer_pos, *cmds))
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

t_lexer	**init_lex(char *input)
{
	t_lexer **lexer;
	char	**contents;
	int		i;
	int		len;

	i = 0;
	len = 0;
	contents = ft_split(input, ' ');
	while (contents[i++])
		len++;
	i = 0;
	lexer = malloc(sizeof(t_lexer *) * len + 1);
	printf("Command: ");
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
	first_cmd->in = "0";
	first_cmd->out = "1";
	head = ft_lstnew(first_cmd);
	if (!head)
	{
		free(first_cmd);
		return (NULL);
	}
	return (head);
}

int	get_cmdlist_size(char *input)
{
	int		i;
	t_lexer **lexer;
	t_list	*head;

	i = 0;
	head = init_cmdlist_size();
	if (!head)
		return (1);
	lexer = init_lex(input);
	while (lexer[i])
	{
		if (filter_type_input(lexer, &i, &head))
			break ;
	}
	free_lexer(lexer);
	free_envp(head);
	return (0);
}
