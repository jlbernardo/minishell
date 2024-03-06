/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:53:31 by iusantos          #+#    #+#             */
/*   Updated: 2023/08/21 11:30:24 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_enough(int fd, char *output_buffer)
{
	int		bytes_read;
	char	*read_buffer;

	read_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(read_buffer);
		return (NULL);
	}
	if (bytes_read == 0)
	{
		free(read_buffer);
		return (output_buffer);
	}
	read_buffer[bytes_read] = '\0';
	output_buffer = gnl_strjoin(output_buffer, read_buffer);
	free(read_buffer);
	if (find_first_newline(output_buffer) == -1)
		return (read_enough(fd, output_buffer));
	return (output_buffer);
}

char	*extract_retstr(char *output_buffer)
{
	char	*retstr;
	char	*real_retstr;
	size_t	size;
	int		newline_pos;

	if (output_buffer == NULL)
		return (NULL);
	newline_pos = find_first_newline(output_buffer);
	if (newline_pos != -1)
		size = newline_pos + 2;
	else
		size = ft_strlen(output_buffer) + 1;
	retstr = (char *) malloc(size * sizeof(char));
	real_retstr = retstr;
	while (*output_buffer != '\n' && *output_buffer != '\0')
		*retstr++ = *output_buffer++;
	if (*output_buffer == '\n')
	{
		*retstr++ = '\n';
		*retstr = '\0';
		return (real_retstr);
	}
	if (*output_buffer == '\0')
		*retstr = '\0';
	return (real_retstr);
}

char	*update_remainder(char	*output_buffer)
{
	char	*remainder;
	char	*real_remainder;
	int		nl_pos;
	char	*og_output_buffer;

	og_output_buffer = output_buffer;
	nl_pos = find_first_newline(output_buffer);
	if ((nl_pos != -1 && output_buffer[nl_pos + 1] == '\0') || nl_pos == -1)
	{
		free(output_buffer);
		return (NULL);
	}
	else
	{
		remainder = (char *) malloc(
				(ft_strlen(output_buffer) - nl_pos) * sizeof(char));
		real_remainder = remainder;
		while (*output_buffer != '\n')
			output_buffer++;
		while (*++output_buffer != '\0')
			*remainder++ = *output_buffer;
		*remainder = '\0';
		free(og_output_buffer);
		return (real_remainder);
	}
}

char	*get_next_line(int fd)
{
	static char	*output_buffer[4096];
	char		*return_string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (find_first_newline(output_buffer[fd]) == -1 || !output_buffer[fd])
		output_buffer[fd] = read_enough(fd, output_buffer[fd]);
	if (ft_strlen(output_buffer[fd]) != 0)
		return_string = extract_retstr(output_buffer[fd]);
	else
		return (NULL);
	output_buffer[fd] = update_remainder(output_buffer[fd]);
	return (return_string);
}
