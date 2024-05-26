/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:37:51 by pantoine          #+#    #+#             */
/*   Updated: 2024/05/26 10:48:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define HDNAME ".hdtmp"
# include "minishell.h"
# include <sys/stat.h>

typedef struct s_cmd
{
	char	**command;
	char	*tempfile_name;
	t_list	*cmd_args;
	char	*in;
	t_list	*out;
	int		outtype;
	int		nb;
}	t_cmd;
typedef struct s_outfile
{
	char	*name;
	int		outtype;
}	t_outfile;

//execute_main_size.c
int		add_arg_to_cmd(int *lexer_pos, t_cmd *cmd, char *newarg_content);
int		get_cmdlist(t_lexer **lexer, t_shell *shell);

//execute_init_structs.c
t_lexer	**init_lex(t_list *envp, t_lexer **lexer);
t_list	*init_cmdlist_size(t_lexer **lexer);

//execute_init_structs_utils.c
int		parse_builtin_sequence(t_lexer **lexer, int *index, t_list *envp);
int		replace_parsed_content(t_lexer **lexer,
			int *index, char *newval, t_list *envp);
int		parse_dollar_sequence(t_lexer **lexer, int *index, t_list *envp);

//execute_flags.c
int		add_size_arg_node(t_lexer **lexer, int *lexer_pos,
			t_list **cmds, t_list *envp);

//execute_flags_utils.c
void	zero_cmdargs(t_cmd *cmd);
int		delete_current_command(t_cmd *cmd);

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
void	free_single_cmd(t_list *args);
void	free_command_arrays(t_list *head);
void	free_cmdlist(t_list *cmds);
void	free_lexer(t_lexer **lexer);

//execute_set_redirections.c
int		is_legal_token(t_lexer **lexer, int *lexer_pos, t_cmd *cmd);
int		is_legal_heredoc(t_lexer **lexer, int *lexer_pos,
			t_cmd *cmd, t_list *envp);

//execute_utils.c
int		flag_redirect_stream(t_lexer **lexer, int *lexer_pos);
int		flag_add_to_node(t_lexer **lexer, int *lexer_pos);

//execute_transform_cmdlist.c
int		copy_all_cmds(t_list *head);

//execute_dispatcher.c
int		is_same_str(char *s1, char *s2);
int		call_builtin(t_cmd *cmd, t_shell *shell,
			t_list *cmdlist, t_lexer **lexer);
int		no_command(t_cmd *cmd);
int		dispatch_commands(t_list *cmdlist, t_shell *shell, t_lexer **lexer);

//execute_dispatcher_utils.c
int		dispatch_builtin(t_cmd *cmd, t_shell *shell);

//execute_onecommand.c
int		execute_one_command(t_list *cmdlist, t_shell *shell, t_lexer **lexer);

//execute_normalcmd.c
void	executor(t_cmd *cmd, t_shell *shell, t_list *cmdlist, t_lexer **lexer);
int		pimped_execve(t_cmd *cmd, t_shell *shell);

//execute_normalcmd_utils.c
int		is_a_dir_error(t_cmd *cmd);
void	free_partial_envp_char(t_shell *shell, int i);
int		reset_shlvl(t_shell *shell);
int		export_newshlvl(t_shell *shell, char *shlvl_value);

//execute_pathfinding.c
int		is_executable(t_cmd *cmd);
int		is_a_dir(t_cmd *cmd);
void	free_split(char **tofree);
int		find_executable_path(t_cmd *cmd, t_shell *shell);

//execute_redirect_utils.c
int		transfer_pipes(t_cmd *cmd, t_shell *shell,
			t_list *cmdlist, int pipe_fds[2]);
int		write_and_read_pipe(t_list *cmdlist, int nb_cmd,
			t_shell *shell, int pipefds[2]);
int		open_outfile(t_outfile *outfile);

//execute_redirect.c
int		dup_redirections(t_cmd *cmd);
#endif
