/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/18 11:09:23 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//TODO
//parse_pipeline
//parse_cmd

u_plcmd *parse_pipeline(t_token *tokens)
{
	u_plcmd *pl;

	pl = malloc(sizeof(u_plcmd *));
	if (pl == NULL)
		return NULL;
	pl->pipeline->left = parse_cmd(tokens);
	pl->pipeline->right = parse_pipeline(tokens);

	return pl;
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd *));
	if (cmd == NULL)
		return NULL;
	set_cmd(cmd);
	if (tokens->type == OPERAND && tokens->next->type == WORD)
	{
		cmd->redirects = parse_redirect(tokens);
		tokens = tokens->next->next;
	}
	else if (tokens->type == WORD)
	{
		append_wle(new_wle(tokens->literal), cmd->word_list);
		tokens = tokens->next;
	}
	else {
		ft_printf("Syntax error!");
		return NULL;
	}
}

void	set_cmd(t_cmd *cmd)
{
	cmd->pathname = NULL;
	cmd->word_list = ft_calloc(sizeof(t_wl_element **), 1);
	cmd->redirects = ft_calloc(sizeof(t_redirect **), 1);

}

t_wl_element	*new_wle(char *s)
{
	t_wl_element	*wle;

	wle = malloc(sizeof(t_wl_element *));
	if (wle == NULL)
		return NULL;
	wle->word = ft_strdup(s);
	wle->next = NULL;
}

void	append_wle(t_wl_element *w, t_wl_element **wl)
{
	if (*wl == NULL)
	{
		*wl = w;
		return ;
	}
	while ((*wl)->next != NULL)
		*wl = (*wl)->next;
	(*wl)->next = w;
	return ;
}
