/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:37:51 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/15 23:38:50 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define HDNAME ".hdtmp"
# include "minishell.h"

typedef struct s_cmd
{
	char	**command;
	char	*tempfile_name;
	t_list	*cmd_args;
	char	*in;
	char	*out;
}	t_cmd;

//execute_main_size.c
int		add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content);
int		filter_type_input(t_lexer **lexer,
			int *lexer_pos, t_list **cmds, t_list *envp);
t_lexer	**init_lex(t_list *envp, t_lexer **lexer);
void	free_current_lexer(t_lexer **lexer, int i);
t_list	*create_begin_cmd(t_cmd *begin_cmd, char *begin);
t_list	*init_cmdlist_size(void);
int		get_cmdlist(t_lexer **lexer, t_shell *shell);

//execute_flags.c
int		get_size_command(t_lexer **lexer, int *lexer_pos,
			t_cmd *cmd, t_list *envp);
int		set_cmdargs_basevalues(t_lexer **lexer, int *lexer_pos, t_cmd *cmd, t_list *envp);
t_cmd	*init_cmdargs(t_lexer **lexer, int *lexer_pos, t_list *envp);
int		add_size_arg_node(t_lexer **lexer, int *lexer_pos,
			t_list **cmds, t_list *envp);

//execute_heredocs.c
int		create_heredoc(t_lexer *delimiter, t_cmd *cmd, t_list *envp);

//execute_heredocs_utils.c
int		expand_dollars_heredocs(int fd, char *input,
			t_list *envp, int noexpand);

//execute_errors.c
int		newcmd_malloc_err(t_cmd *cmd);
void	unexpected_token_exec_err(char *error_token);
void	perror_context(char *failed_command, char *context);

//execute_free_utils.c
void	close_fds_remove_tmps(t_cmd *cmd);
void	free_single_cmd(t_list *args);
void	free_command_arrays(t_list *head);
void	free_cmdlist(t_list *cmds);
void	free_lexer(t_lexer **lexer);

//execute_set_redirections.c
int		redirect_stream(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		is_legal_heredoc(t_lexer **lexer, int *lexer_pos,
			t_cmd *cmd, t_list *envp);

//execute_utils.c
int		flag_redirect_stream(t_lexer **lexer, int *lexer_pos);
int		flag_add_to_node(t_lexer **lexer, int *lexer_pos);

//execute_transform_cmdlist.c
char	**init_cmd_array(t_cmd *cmd);
int		copy_all_cmds(t_list *head);

//cd_main.c
int		count_args_cd(t_cmd *cmd);
int		get_chdir_status(int len, t_cmd *cmd, t_list **envp);
int		change_directory(t_cmd *cmd, t_shell *shell);

//cd_utils.c
int		change_pwd(t_shell *shell);
int		change_oldpwd(t_shell *shell, char *old);
int		cd_error_message(char *message);

//exit_main.c
int		exit_petitcoq(t_cmd *cmd, t_list *cmdlist,
			t_lexer **lexer, t_shell *shell);

//pwd_main.c
void	get_pwd(void);

//execute_dispatcher.c
int		call_builtin(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer);
int		no_command(t_cmd *cmd);
int		dispatch_commands(t_list *cmdlist, t_shell *shell, t_lexer **lexer);

//execute_dispatcher_utils.c
int		init_pipeline(t_shell *shell);

//execute_onecommand.c
int	execute_one_command(t_list *cmdlist, t_shell *shell, t_lexer **lexer);

//execute_normalcmd.c
int	pimped_execve(t_cmd *cmd, t_shell *shell);

//execute_redirect.c
int		dup_redirections(t_cmd *cmd);
#endif
