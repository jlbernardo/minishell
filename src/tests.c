#include "includes/minishell.h"
#include <assert.h>
#include <stdio.h>

int	lexer_test(t_token **tokens, t_ast_node **ast, char *string)
{
	char	*input;
	t_lexer	lex;

	*tokens = NULL;
	*ast = NULL;
	input = string;
	set_lexer(&lex, input);
	while (lex.read_pos < lex.size && lex.success == TRUTH)
	{
		read_char(&lex);
		find_token(&lex, tokens, 1);
	}
	if (!lex.success)
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
	// free(input);
	return (lex.success);
}

t_ast_node	*parse_pipeline_test(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*pl_node;

	set_pl(&pl_node, &parent, tokens);
	if (!pl_node)
		return (NULL);
	pl_node->left = parse_cmd(tokens, pl_node);
	if (pl_node->left == NULL)
		return (NULL);
	if (*tokens == NULL)
		return (pl_node);
	else if (!ft_strncmp((*tokens)->literal, "|", 1) && has_other_pipes(*tokens)
		&& ft_strncmp((*tokens)->next->literal, "|", 1))
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_pipeline(tokens, pl_node);
	}
	else if (!ft_strncmp((*tokens)->literal, "|", 1)
		&& !has_other_pipes(*tokens) && (*tokens)->next != NULL)
	{
		*tokens = (*tokens)->next;
		pl_node->right = parse_cmd(tokens, pl_node);
	}
	else
		ft_printf("Syntax error near token %s\n", (*tokens)->literal);
	return (pl_node);
}

t_ast_node	*parse_cmd_test(t_token **tokens, t_ast_node *parent)
{
	t_ast_node	*cmd_node;

	set_cmd(&cmd_node, &parent);
	while (*tokens != NULL && ft_strncmp((*tokens)->literal, "|", 1))
	{
		if ((*tokens)->type == REDIRECT && (*tokens)->next->type == WORD)
		{
			append_redirect(new_redirect(*tokens), cmd_node->data->redirects);
			*tokens = (*tokens)->next->next;
		}
		else if ((*tokens)->type == WORD)
		{
			append_wle(new_wle((*tokens)->literal), cmd_node->data->word_list);
			*tokens = (*tokens)->next;
		}
		else
		{
			ft_printf("Syntax error near token %s\n", (*tokens)->literal);
			free_data(cmd_node->data);
			free(cmd_node);
			return (NULL);
		}
	}
	return (cmd_node);
}

int main(void)
{
	int i = 0;
	t_token		**tokens;
	t_ast_node	**ast;

	tokens = ft_calloc(1, sizeof(t_token *));
	ast = ft_calloc(1, sizeof(t_ast_node *));


	//0
	ft_printf("Lexer: No input\n");
	ft_printf("%d - Lexer - Testing input: \\n ", i++);
	lexer_test(tokens, ast, "");
	assert(*tokens == NULL);
	ft_printf("\033[32mOK\033[0m\n");

	//1
	ft_printf("Lexer: One token\n");
	ft_printf("%d - Lexer - Testing input: echo - ", i++);
	lexer_test(tokens, ast, "echo");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//2
	ft_printf("%d - Lexer - Testing input: \"texto\" - ", i++);
	lexer_test(tokens, ast, "\"texto\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"texto\"", 8) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//3
	ft_printf("%d - Lexer - Testing input: \"\'texto\'\" - ", i++);
	lexer_test(tokens, ast, "\"\'texto\'\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\'texto\'\"", 10) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//4
	ft_printf("%d - Lexer - Testing input: \"\"texto1\"texto2\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\"texto2\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\"texto2\"", 17) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//5
	ft_printf("%d - Lexer - Testing input: echo \"echo > arq1\" > arq1 - ", i++);
	lexer_test(tokens, ast, "echo \"echo > arq1\" > arq1");
	assert((*tokens)->type == WORD);
	assert(ft_strcmp((*tokens)->literal, "echo") == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strcmp((*tokens)->next->literal, "\"echo > arq1\"") == 0);
	assert((*tokens)->next->next->type == REDIRECT);
	assert(ft_strcmp((*tokens)->next->next->literal, ">") == 0);
	assert((*tokens)->next->next->next->type == WORD);
	assert(ft_strcmp((*tokens)->next->next->literal, "arq1") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//6
	ft_printf("%d - Lexer - Testing input: \"\"texto1\" texto2\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\" texto2\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\" texto2\"", 19) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//6
	ft_printf("%d - Lexer - Testing input: \"\"texto1\" \'texto2\'\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\" \'texto2\'\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\" \'texto2\'\"", 19) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//7
	ft_printf("%d - Lexer - Testing input: \"\'texto1\' \"texto2\"\" - ", i++);
	lexer_test(tokens, ast, "\"\'texto1\' \"texto2\"\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\'texto1\' \"texto2\"\"", 50) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	ft_printf("Lexer: Multiple tokens\n");
	//8
	ft_printf("%d - Lexer - Testing input: echo texto - ", i++);
	lexer_test(tokens, ast, "echo texto");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "texto", 6) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//9
	ft_printf("%d - Lexer - Testing input: echo > - ", i++);
	lexer_test(tokens, ast, "echo >");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	assert((*tokens)->next->type == REDIRECT);
	assert(ft_strncmp((*tokens)->next->literal, ">", 1) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//10
	ft_printf("%d - Lexer - Testing input: echo texto > arq1 - ", i++);
	lexer_test(tokens, ast, "echo texto > arq1");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "texto", 6) == 0);
	assert((*tokens)->next->next->type == REDIRECT);
	assert(ft_strncmp((*tokens)->next->next->literal, ">", 1) == 0);
	assert((*tokens)->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->literal, "arq1", 5) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//11
	ft_printf("%d - Lexer - Testing input: echo texto | grep texto - ", i++);
	lexer_test(tokens, ast, "echo texto | grep texto");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "texto", 6) == 0);
	assert((*tokens)->next->next->type == REDIRECT);
	assert(ft_strncmp((*tokens)->next->next->literal, "|", 1) == 0);
	assert((*tokens)->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->literal, "grep", 5) == 0);
	assert((*tokens)->next->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->next->literal, "texto", 5) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//12
	ft_printf("%d - Lexer - Testing input:  <arq1 cat - ", i++);
	lexer_test(tokens, ast, "<arq1 cat");
	assert((*tokens)->type == REDIRECT);
	assert(ft_strncmp((*tokens)->literal, "<", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "arq1", 5) == 0);
	assert((*tokens)->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->literal, "cat", 5) == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//13
	ft_printf("%d - Lexer - Testing input: < arq1 ls -al | wc -l     >arq2 - ", i++);
	lexer_test(tokens, ast, "< arq1 ls -al | wc -l     >arq2");
	assert((*tokens)->type == REDIRECT);
	assert(ft_strncmp((*tokens)->literal, "<", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "arq1", 5) == 0);
	assert((*tokens)->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->literal, "ls", 5) == 0);
	assert((*tokens)->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->literal, "-al", 5) == 0);
	assert((*tokens)->next->next->next->next->type == REDIRECT);
	assert(ft_strncmp((*tokens)->next->next->next->next->literal, "|", 5) == 0);
	assert((*tokens)->next->next->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->next->next->literal, "wc", 5) == 0);
	assert((*tokens)->next->next->next->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->next->next->next->literal, "-l", 5) == 0);
	assert((*tokens)->next->next->next->next->next->next->next->type == REDIRECT);
	assert(ft_strncmp((*tokens)->next->next->next->next->next->next->next->literal, ">", 5) == 0);
	assert((*tokens)->next->next->next->next->next->next->next->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->next->next->next->next->next->next->next->literal, "arq2", 5) == 0);
	ft_printf("\033[32mOK\033[0m\n");
}
