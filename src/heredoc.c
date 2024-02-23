/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:56:18 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/23 11:28:12 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//traverse ast calling capture content on CMD nodes
int	execute_heredocs(t_ast *ast)
{
	capture_content(ast->left->data->redirects);
	if (ast->right == NULL)
		return (1);
	else
	{
		if (ast->right->type == CMD)
			capture_content(ast->right->data->redirects);
		else
			execute_heredocs(ast->right);
	}
	return 1;
}

//for each redirect that is heredoc, save the content in a file.
//if there are multiple heredocs in a command, overwrites file
void	capture_content(t_redir *rl)
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
			// O_CREAT || O_TRUNC || O_RDWR
			heredoc_fd = open(tmp_file, O_CREAT|O_RDWR|O_TRUNC, 0666);
			fill_tmpfile(heredoc_fd, rl);
			free(tmp_file);
		}
		rl = rl->next;
	}
	cmd_nbr++;
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

void	fill_tmpfile(int fd, t_redir *r)
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
			write(fd, input, size);
		free(input);
		input = readline(">");
		if (ft_strcmp(input, r->filename) == 0)
		{
			free(input);
			write(fd, "\0", 1);
			close(fd);
			break;
		}
		write(fd, "\n", 1);
	}
}
