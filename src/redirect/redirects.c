/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:32:57 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/08 16:22:29 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_redirects(t_redir *rl, t_meta *meta)
{
	int	process_next_redir;

	while (rl != NULL)
	{
		if (rl->type == REDIN)
			process_next_redir = red_input(rl);
		else if (rl->type == APPEND)
			process_next_redir = red_append(rl);
		else if (rl->type == REDOUT)
			process_next_redir = red_output(rl);
		else
			process_next_redir = red_heredoc(rl, meta->cmd_nbr);
		if (process_next_redir == LIE)
		{
			add_upd_hashtable("?", "1", meta->hash);
			return (LIE);
		}
		else
			rl = rl->next;
	}
	return (TRUTH);
}

int	red_input(t_redir *r)
{
	int	fd;

	if (access(r->filename, F_OK) == 0)
	{
		if (access(r->filename, R_OK) != 0)
		{
			print_np_error_msg(r->filename);
			return (LIE);
		}
		fd = open(r->filename, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (TRUTH);
	}
	else
	{
		print_nsf_error_msg(r->filename);
		return (LIE);
	}
}

int	red_output(t_redir *r)
{
	int			fd;
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(buf));
	stat(r->filename, &buf);
	if (S_ISDIR(buf.st_mode) != 0)
	{
		print_dir_error_msg(r->filename);
		return (LIE);
	}
	if (access(r->filename, F_OK) == 0 && access(r->filename, W_OK) != 0)
	{
		print_np_error_msg(r->filename);
		return (LIE);
	}
	fd = open(r->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		print_nsf_error_msg(r->filename);
		return (LIE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (TRUTH);
}

int	red_heredoc(t_redir *r, int cmd_nbr)
{
	int		fd;
	char	*heredoc_file;

	(void)r;
	heredoc_file = gen_tmpfile_name(cmd_nbr);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (TRUTH);
}

int	red_append(t_redir *r)
{
	int			fd;
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(buf));
	stat(r->filename, &buf);
	if (S_ISDIR(buf.st_mode) != 0)
	{
		print_dir_error_msg(r->filename);
		return (LIE);
	}
	if (access(r->filename, F_OK) == 0 && access(r->filename, W_OK) != 0)
	{
		print_np_error_msg(r->filename);
		return (LIE);
	}
	fd = open(r->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		print_nsf_error_msg(r->filename);
		return (LIE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (TRUTH);
}
