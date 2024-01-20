/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:48:46 by julberna          #+#    #+#             */
/*   Updated: 2024/01/18 12:11:34 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// t_cmd	*cmd_last(t_cmd *cmd);
t_token	*tk_last(t_token *tk);

void	new_token(t_token **tk, int type, char *literal)
{
	t_token	*new_node;

	new_node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->literal = ft_strdup(literal);
	new_node->next = NULL;
	if (!*tk)
		*tk = new_node;
	else
		tk_last(*tk)->next = new_node;
}

// void	new_cmd(t_cmd **cmd, char *cmd_str, char *flag, char *args)
// {
// 	t_cmd	*new_node;
//
// 	new_node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
// 	if (new_node == NULL)
// 		return ;
// 	if (flag != NULL)
// 		new_node->flag = flag;
// 	new_node->cmd = ft_strdup(cmd_str);
// 	new_node->args = ft_strdup(args);
// 	new_node->next = NULL;
// 	if (*cmd == NULL)
// 		*cmd = new_node;
// 	else
// 		cmd_last(*cmd)->next = new_node;
// }
//
// t_cmd	*cmd_last(t_cmd *cmd)
// {
// 	if (cmd == NULL)
// 		return (NULL);
// 	while (cmd->next != NULL)
// 		cmd = cmd->next;
// 	return (cmd);
// }

t_token	*tk_last(t_token *tk)
{
	if (tk == NULL)
		return (NULL);
	while (tk->next != NULL)
		tk = tk->next;
	return (tk);
}
