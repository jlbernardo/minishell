/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:05:13 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/16 18:30:19 by iusantos         ###   ########.fr       */
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
}

void	run_pipeline(t_ast *ast, int in_fd, t_meta *meta)
{
	int		pipe_fd[2];
	int		exit_status;
	pid_t	child_pid;

	//precisa checar de pipe deu errado
	pipe(pipe_fd);
	if (ast->right->type == CMD) //ultimo node pipeline
	{
		child_pid = fork();
		if (child_pid == 0) //lowest left node
		{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
				close(pipe_fd[0]);
			}
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			run_executable(ast->left->data, meta);
		}
		else 
		{
			child_pid = fork(); //lowest right node
			if (child_pid == 0)
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				run_executable(ast->right->data, meta);
			}
		}
	}
	else 
	{
		child_pid = fork();
		if (child_pid == 0) //left node
		{
			if (in_fd != 0) //not first command
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
				close(pipe_fd[0]);
			}
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			run_executable(ast->left->data, meta);
		}
		close(pipe_fd[1]);
		run_pipeline(ast->right, pipe_fd[0], meta); //recursion
		close(pipe_fd[0]); //only closes fd after it is passed to recursion
	}
	close(in_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	while(wait(&exit_status) > 0)
	{
	}
	//recover STDIN & STDOUT if necessary
	return ;
}

void	run_simple_command(t_ast *cmd_node, t_meta *meta)
{
	pid_t	child_pid;
	int		exit_status;

	//TODO: deal with redirects
	if	(is_builtin(cmd_node->data->word_list[0].word))
		run_builtin(cmd_node->data->word_list);
	else
	{
		if ((child_pid = fork()) == -1)
			return ;
		if (child_pid == 0)
			run_executable(cmd_node->data, meta);
		waitpid(child_pid, &exit_status, 0); 
		printf("%d\n", exit_status);
		add_or_upd_ht_entry("?", ft_itoa(exit_status), meta->env_vars);
	}
	//save exit status
	//recover original STDIN, STDOUT if necessary
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
	int		exec_return;
	char	**array_of_strings;


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
			exit(127);
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
