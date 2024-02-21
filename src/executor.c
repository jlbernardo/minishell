/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/21 12:07:06 by iusantos         ###   ########.fr       */
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
	{
		run_pipeline(ast, 0, meta);
	}
	//debugging statement below
	ft_printf("errno: %d, exit_status: %s\n", errno, grab_value("?", meta->env_vars));
}

void	run_pipeline(t_ast *ast, int in_fd, t_meta *meta)
{
	int		pipe_fd[2];
	pid_t	child_pid;

	if(pipe(pipe_fd) == -1)
		return;
	if (ast->right->type == CMD) //last pipeline node
	{
		//apply redirects before fork?
		child_pid = fork();
		if (child_pid == 0) //lowest left node
		{
			exec_left_node(ast->left->data, in_fd, pipe_fd, meta);
		}
		//apply redirects before fork?
		child_pid = fork(); //lowest right node
		if (child_pid == 0)
		{
			exec_right_node(ast->right->data, pipe_fd, meta);
		}
	}
	else 
	{
		//apply redirects before fork?
		child_pid = fork();
		if (child_pid == 0) //left node
		{
			exec_left_node(ast->left->data, in_fd, pipe_fd, meta);
		}
		close(pipe_fd[1]);
		run_pipeline(ast->right, pipe_fd[0], meta); //recursion
		close(pipe_fd[0]); //only closes fd after it is passed to recursion
	}
	close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	while(cap_n_upd_exit_status(meta) != -1);
	//recover STDIN & STDOUT if necessary?
	return ;
}

void	capture_exit_status(pid_t current_child_pid, int exit_status, t_meta *meta)
{
	static pid_t	last_child_pid;
	char	*exit_string;

	if (current_child_pid > last_child_pid)
	{
		exit_status = WEXITSTATUS(exit_status);
		exit_string = ft_itoa(exit_status);
		if (exit_status == 13)
		{
			add_or_upd_ht_entry("?", "126", meta->env_vars);
		}
		else
		{
			add_or_upd_ht_entry("?", exit_string, meta->env_vars);
		}
		free(exit_string);
	}
	last_child_pid = current_child_pid;
}

void	run_executable(t_cmd *data, t_meta *meta)
{
	int		exec_return;
	char	**array_of_strings = NULL;


	array_of_strings = stringfy(data->word_list);
	exec_return = execve(data->pathname, array_of_strings, NULL);
	if (exec_return == -1)
	{
		perror(strerror(errno));
		free_array_of_strings(array_of_strings, get_size(data->word_list));
		free(array_of_strings);
		finisher(meta->tokens, meta->ast);
		free_ht(meta->env_vars);
		exit(errno);
	}
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

void handle_null_pathname(t_meta *meta)
{
	ft_putstr_fd("Minishell: command not found\n", 2);
	add_or_upd_ht_entry("?", "127", meta->env_vars);
}
