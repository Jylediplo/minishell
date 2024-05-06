/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyjy <jyjy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:07:04 by lefabreg          #+#    #+#             */
/*   Updated: 2024/04/28 15:33:18 by jyjy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

void free_split(char **str)
{
    int i;

    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

void error(char *file, char **to_free1, char **to_free2)
{
   
	if (file)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2 , ": ", 2);
		write(2, file, ft_strlen(file));
        write(2, "\n", 1);
	}
	if (to_free1)
		free_split(to_free1);
	if (to_free2)
		free_split(to_free2);
	exit(1);
}

int find_str(char *to_find, char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == to_find[i])
        i++;
    return (i);
}

char *find_path(char **envp)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (envp[i])
    {
        if (find_str("PATH=", envp[i]) == 5)
            break;
        i++;
    }
    while (envp[j])
        j++;
    if (j == i)
        return(NULL);
    else
        return (envp[i]);
}
char  *correct_path(char *argv, char **local_path)
{
    
    char *path_to_try;
    char *command_line;
    char **cmd;
    int i;
    
    cmd = ft_split(argv, ' ');
    if (!cmd)
        return (NULL);
    i = 0;
    while (local_path[i])
    {
        path_to_try = ft_strjoin(local_path[i], "/");
        if (!path_to_try)
            return (free_split(cmd), NULL);
        command_line = ft_strjoin(path_to_try, cmd[0]);
		free(path_to_try);
        if (!command_line)
            return (free_split(cmd), NULL);
       if (access(command_line, F_OK) == 0)
            return (free_split(cmd), command_line);
        free(command_line);
        i++;
    }
    return (free_split(cmd), NULL);
}

void manage_path(char *argv, char **envp)
{
    char *path;
    char **local_path;
    char *test;
    char **cmd;

    cmd = ft_split(argv, ' ');
    if (!cmd)
        error(NULL, NULL, NULL);
    path = find_path(envp);
    if (!path)
        error(NULL, cmd, NULL);
    local_path = ft_split(path, ':');
    if (!local_path)
        error(NULL, cmd, NULL);
    test = correct_path(argv, local_path);
    if (!test)
        error(cmd[0], local_path, cmd);
    if (execve(test, cmd, envp) == -1)
    {
	   	free(test);
    	error(NULL, local_path, cmd);
    }
    free(local_path);
}

void manage_child(int *fd, char **argv, char **envp)
{
        int input_file;
        input_file = open(argv[1], O_RDONLY, 0644);
        if (input_file == -1)
		{
            error(argv[1], NULL, NULL);
		}
        dup2(input_file, 0);
        dup2(fd[1], 1);
        close(input_file);
        manage_path(argv[2], envp);
}

void manage_parent(int *fd, char **argv, char **envp)
{
    int output_file;
    
    output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_file == -1)
        error(argv[4], NULL, NULL);
    dup2(fd[0], 0);
    dup2(output_file, 1);
    close(output_file);
    manage_path(argv[3], envp);
}

// int main(int argc, char **argv, char **envp)
// {
//     int fd[2];
//     int pid;
// 	int pid1;

//     if (argc != 5)
//         error(NULL, NULL, NULL);
//     if (pipe(fd) == -1)
//         error(NULL, NULL, NULL);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		manage_child(fd, argv, envp);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		pid1 = fork();
// 		if (pid1 == 0)
// 		{
// 			manage_parent(fd, argv, envp);
// 		}
// 		wait(NULL);
// 		close(fd[0]);
// 	}
//     return (0);
// }