/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:56:18 by iusantos          #+#    #+#             */
/*   Updated: 2024/03/03 14:05:26 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_heredocs(t_ast *ast, t_meta *meta)
{
	int		child_pid;
	int		exit_status;

	child_pid = fork();
	signal(SIGINT, SIG_IGN);
	if (child_pid == 0)
		child_heredoc(meta, ast);
	waitpid(-1, &exit_status, 0);
	signal_handler(meta);
	if (WEXITSTATUS(exit_status) == 1)
	{
		add_upd_hashtable("?", "130", meta->hash);
		meta->ast->success = LIE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	capture_content(t_redir *rl, t_meta *meta)
{
	int				heredoc_fd;
	char			*tmp_file;
	static int		cmd_nbr;

	while (rl != NULL)
	{
		if (rl->type == HEREDOC)
		{
			tmp_file = gen_tmpfile_name(cmd_nbr);
			heredoc_fd = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
			free(tmp_file);
			fill_tmpfile(heredoc_fd, rl, meta);
		}
		rl = rl->next;
	}
	cmd_nbr++;
}

char	*gen_tmpfile_name(int cmd_nbr)
{
	int				digits;
	char			*tmpfile_name;
	char			*tmpfile_nbr;
	unsigned int	buf_size;

	tmpfile_nbr = ft_itoa(cmd_nbr);
	digits = count_digit_base(cmd_nbr, 10);
	buf_size = 6 + digits;
	tmpfile_name = malloc(buf_size);
	ft_memmove(tmpfile_name, "/tmp/", 6);
	ft_strlcat(tmpfile_name, tmpfile_nbr, buf_size);
	free(tmpfile_nbr);
	return (tmpfile_name);
}

void	fill_tmpfile(int fd, t_redir *r, t_meta *meta)
{
	char			*input;
	unsigned int	size;

	input = readline(">");
	if (handle_eof(input, r, fd, meta) == 1)
		return ;
	while (ft_strcmp(input, r->filename) != 0)
	{
		size = ft_strlen(input);
		if (size == 0)
			write(fd, "\n", 1);
		else
			expand_and_write(&input, fd, meta);
		free(input);
		input = readline(">");
		if (handle_eof(input, r, fd, meta) == 1)
			return ;
		if (ft_strcmp(input, r->filename) == 0)
		{
			free(input);
			write_and_close(fd);
			break ;
		}
		write(fd, "\n", 1);
	}
}
