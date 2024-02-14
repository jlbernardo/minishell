/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:37 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_ast *ast, t_meta *meta)
{
	if (ast->right == NULL)
	{
		run_simple_command(ast->left, meta);
	}
	else 
		return;
	// {
	// 	run_pipeline(ast);
	// }
}

void	run_simple_command(t_ast *cmd_node, t_meta *meta)
{
	//deal with redirects
	if	(is_builtin(cmd_node->data->word_list[0].word))
		run_builtin(cmd_node->data->word_list);
	else
		run_executable(cmd_node->data, meta);
}

int	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0
	|| ft_strcmp(cmd_name, "cd") == 0
	|| ft_strcmp(cmd_name, "pwd") == 0
	|| ft_strcmp(cmd_name, "export") == 0
	|| ft_strcmp(cmd_name, "unset") == 0
	|| ft_strcmp(cmd_name, "env") == 0
	|| ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	else
		return (0);
}

void	run_builtin(t_word *wl)
{
	//TODO
	wl = NULL;
	return ;
}

void	run_executable(t_cmd *data, t_meta *meta)
{
	pid_t	child_pid;
	int		exit_status;
	int		exec_return;
	char	**array_of_strings;

	if ((child_pid = fork()) == -1)
		return ;
	if (child_pid == 0)
	{
		sleep(10);
		array_of_strings = stringfy(data->word_list);
		exec_return = execve(data->pathname, array_of_strings, NULL);
		if (exec_return == -1)
		{
			// modificar para printar no fd 2
			ft_printf("Command not found\n");
			finisher(meta->tokens, meta->ast);
			free_ht(meta->env_vars);
			//liberar array_of_strings
			free_array_of_strings(array_of_strings, get_size(data->word_list));
			free(array_of_strings);
			exit(2);
		}
	}
	waitpid(child_pid, &exit_status, 0); 
}

void	free_array_of_strings(char **array, int size)
{
	int index;

	if (array == NULL)
		return ;
	index = 0;
	while (index <= size)
	{
		free(array[index]);
		index++;
	}
}

char **stringfy(t_word *wl)
{
	char	**array;
	int		size;
	int		index;
	
	size = get_size(wl) + 1;
	array = ft_calloc(size, sizeof(char *));
	index = 0;
	while (wl->next != NULL)
	{
		array[index] = ft_strdup(wl->word);
		index++;
		wl = wl->next;
	}
	array[index] = ft_strdup(wl->word);
	return (array);
}

int	get_size(t_word *wl)
{
	int	nelem;

	nelem = 1;
	while (wl->next != NULL)
	{
		nelem++;
		wl = wl->next;
	}
	return (nelem);
}
