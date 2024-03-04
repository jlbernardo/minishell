/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juliany Bernardo <julberna@student.42sp    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:33:55 by Juliany Ber       #+#    #+#             */
/*   Updated: 2024/03/04 14:12:19 by Juliany Ber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	expand_and_write(char **input, int fd, t_meta *meta)
{
	expand_variable(input, meta);
	write(fd, *input, ft_strlen(*input));
}

void	write_and_close(int fd)
{
	write(fd, "\n\0", 2);
	close(fd);
}
