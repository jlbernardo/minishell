/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iusantos <iusantos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:55:58 by iusantos          #+#    #+#             */
/*   Updated: 2024/01/18 11:59:16 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//TODO
//parse_pipeline
//parse_cmd

u_plcmd *parse_pipeline(t_token *tokens, u_plcmd *parent)
{
	u_plcmd *pl;

	pl = malloc(sizeof(u_plcmd *));
	if (pl == NULL)
		return NULL;
	pl->pipeline->parent = parent;
	pl->pipeline->left = parse_cmd(tokens, pl->pipeline);
	pl->pipeline->right = parse_pipeline(tokens, pl);

	return pl;
}

t_cmd	*parse_cmd(t_token *tokens, t_pipeline *parent)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd *));
	if (cmd == NULL)
		return NULL;
	set_cmd(cmd, parent);
	while (tokens->next != NULL)
	{
		if (tokens->type == OPERAND && tokens->next->type == WORD)
		{
			append_redirect(new_redirect(tokens), cmd->redirects);
			tokens = tokens->next->next;
		}
		else if (tokens->type == WORD)
		{
			append_wle(new_wle(tokens->literal), cmd->word_list);
			tokens = tokens->next;
		}
		else
		{
			ft_printf("Syntax error!");
			return NULL;
		}
	}
	return (cmd);
}

t_redirect	*new_redirect(t_token *tokens)
{
	t_redirect *redir;

	redir = malloc(sizeof(t_redirect *));
	if (redir == NULL)
		return (NULL);
	if (ft_strncmp(tokens->literal, ">", 1) == 0)
	{
		redir->type = REDOUT;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, ">>", 2) == 0)
	{
		redir->type = APPEND;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, "<", 1) == 0)
	{
		redir->type = REDIN;
		redir->filename = ft_strdup(tokens->next->literal);
	}
	else if (ft_strncmp(tokens->literal, "<<", 2) == 0)
	{
		redir->type = HEREDOC;
		redir->filename = ft_strdup(tokens->next->literal); //talvez heredoc nao seja aqui
	}
	redir->next = NULL;
	return (redir);
}

void	append_redirect(t_redirect *r, t_redirect **rl)
{
	if (*rl == NULL)
	{
		*rl = r;
		return ;
	}
	while ((*rl)->next != NULL)
		*rl = (*rl)->next;
	(*rl)->next = r;
	return ;
}

void	set_cmd(t_cmd *cmd, t_pipeline *parent)
{
	cmd->parent = parent;
	cmd->pathname = NULL;
	cmd->redirects = ft_calloc(sizeof(t_redirect **), 1);
	cmd->word_list = ft_calloc(sizeof(t_wl_element **), 1);
}

t_wl_element	*new_wle(char *s)
{
	t_wl_element	*wle;

	wle = malloc(sizeof(t_wl_element *));
	if (wle == NULL)
		return NULL;
	wle->word = ft_strdup(s);
	wle->next = NULL;
	return (wle);
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
