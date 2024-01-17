/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/17 18:31:40 by iusantos         ###   ########.fr       */
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
	if (tokens->type == OPERAND && tokens->next->type == WORD)
	{
		cmd->redirects = parse_redirect(tokens);
		tokens = tokens->next->next;
	}
	else if (tokens->type == WORD)
	{
		append_word(tokens->literal, cmd);
		tokens = tokens->next;
	}
	else {
		ft_printf("Syntax error!");
		return NULL;
	}
}
