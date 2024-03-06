/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:53:46 by iusantos          #+#    #+#             */
/*   Updated: 2023/08/18 15:16:06 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif //BUFFER_SIZE

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

/* get_next_line_utils.c */
size_t	gnl_strlen(char *s1);
char	*gnl_strjoin(char *s1, char *s2);
int		find_first_newline(char *s1);

#endif
