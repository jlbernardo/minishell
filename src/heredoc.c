/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:56:18 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/26 16:53:24 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//traverse ast calling capture content on CMD nodes
int	execute_heredocs(t_ast *ast, t_meta *meta)
{
	//TODO: change signal handlers for CTRL+C e CTRL+D
	capture_content(ast->left->data->redirects, meta);
	if (ast->right == NULL)
		return (1);
	else
	{
		if (ast->right->type == CMD)
			capture_content(ast->right->data->redirects, meta);
		else
			execute_heredocs(ast->right, meta);
	}
	return 1;
}

//for each redirect that is heredoc, save the content in a file.
//if there are multiple heredocs in a command, overwrites file
void	capture_content(t_redir *rl, t_meta *meta)
{
	static int	cmd_nbr;
	char *tmp_file;
	int	heredoc_fd;

	while(rl != NULL)
	{
		if (rl->type == HEREDOC)
		{
			//open file, call readline, close file;
			tmp_file = gen_tmpfile_name(cmd_nbr);
			heredoc_fd = open(tmp_file, O_CREAT|O_RDWR|O_TRUNC, 0666);
			fill_tmpfile(heredoc_fd, rl, meta);
			free(tmp_file);
		}
		rl = rl->next;
		cmd_nbr++;
	}
	cmd_nbr = 0;
}

char	*gen_tmpfile_name(int cmd_nbr)
{
	char			*tmpfile_name;
	char			*tmpfile_nbr;
	int				digits;
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
	char	*input;
	unsigned int	size;

	input = readline(">");
	//r->filename is actually the delimiter
	while (ft_strcmp(input, r->filename) != 0)
	{
		size = ft_strlen(input);
		if (size == 0)
			write(fd, "\n", 1);
		else
		{
			expand_variable(&input, meta);
			write(fd, input, ft_strlen(input));
		}
		free(input);
		input = readline(">");
		if (ft_strcmp(input, r->filename) == 0)
		{
			free(input);
			write(fd, "\n\0", 2);
			close(fd);
			break;
		}
		write(fd, "\n", 1);
	}
}
