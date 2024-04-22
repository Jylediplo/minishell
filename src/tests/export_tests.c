/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:24:48 by pantoine          #+#    #+#             */
/*   Updated: 2024/04/22 13:29:45 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/export_tests.h"

void	copy_current(void)
{
	char	*content;
	int		temp;
	int		test_file;
	
	test_file = open("docs/export_tests.md", O_RDWR);
	temp = open("docs/.temp.md", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		content = get_next_line(test_file);
		if (!content)
			break ;
		if (!ft_strncmp(content, "## OUTPUT\n", 10) && ft_strlen(content) == 10)
		{
			write(temp, content, ft_strlen(content));
			free(content);
			break ;
		}
		write(temp, content, ft_strlen(content));
		free(content);
	}
	close(test_file);
	close(temp);
	temp = open("docs/.temp.md", O_RDONLY);
	unlink("docs/export_tests.md");
	test_file = open("docs/export_tests.md", O_TRUNC | O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		content = get_next_line(temp);
		if (!content)
			break ;
		write(test_file, content, ft_strlen(content));
		free(content);
	}
	close(test_file);
	close(temp);
	unlink("docs/.temp.md");
}

int	test_export(char *(*parser)(char *))
{
	char	**inputs;
	char	*to_test;
	char	*parsed_string;
	int		test_file;
	int		i;
	int		n_inputs;

	n_inputs = 0;
	i = 0;
	copy_current();
	test_file = open("docs/export_tests.md", O_RDWR);
	//get input size
	while (1)
	{
		to_test = get_next_line(test_file);
		if (!to_test)
			break ;
		if (!ft_strncmp(to_test, "\n", 1) && ft_strlen(to_test) == 1)
			continue ;
		else if (!ft_strncmp(to_test, "## INPUT\n", 9) && ft_strlen(to_test) == 9)
			continue ;
		else if (!ft_strncmp(to_test, "## OUTPUT\n", 10) && ft_strlen(to_test) == 10)
		{
			free(to_test);
			break ;
		}
		else
			n_inputs++;
		free(to_test);
	}
	inputs = malloc(sizeof(char *) * (n_inputs + 1));
	inputs[n_inputs] = NULL;
	close(test_file);
	test_file = open("docs/export_tests.md", O_RDWR);
	//copy inputs
	while (1)
	{
		to_test = get_next_line(test_file);
		if (!to_test)
			break ;
		if (!ft_strncmp(to_test, "\n", 1) && ft_strlen(to_test) == 1)
			continue ;
		else if (!ft_strncmp(to_test, "## INPUT\n", 9) && ft_strlen(to_test) == 9)
			continue ;
		else if (!ft_strncmp(to_test, "## OUTPUT\n", 10) && ft_strlen(to_test) == 10)
		{
			free(to_test);
			break ;
		}
		else
			inputs[i++] = to_test;
	}
	close(test_file);
	test_file = open("docs/export_tests.md", O_RDWR);
	//write output to file,  first increase location in file
	while (1)
	{
		to_test = get_next_line(test_file);
		if (!ft_strncmp(to_test, "## OUTPUT\n", 10) && ft_strlen(to_test) == 10)
		{
			free(to_test);
			break ;
		}
		free(to_test);
	}
	i = 0;
	while (inputs[i])
	{
		parsed_string = parser(inputs[i++]);
		if (!parsed_string)
			break ;
		write(test_file, parsed_string, ft_strlen(parsed_string));
		write(test_file, "\n", 1);
		free(parsed_string);
	}
	close(test_file);
	i = 0;
	while (inputs[i])
		free(inputs[i++]);
	free(inputs);
	return (0);
}
