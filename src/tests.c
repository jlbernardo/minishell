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
	int			i = 0;
	int			j = 0;
	t_token		*temp;
	t_token		*tokens;
	t_ast_node	*ast;

	tokens = ft_calloc(1, sizeof(t_token));
	ast = ft_calloc(1, sizeof(t_ast_node));
	temp = tokens;


	//0
	ft_printf("Lexer: No input\n");
	ft_printf("%d - Lexer - Testing input: \\n ", i++);
	lexer_test(&tokens, &ast, "");
	assert(tokens == NULL);
	ft_printf("\033[32mOK\033[0m\n");

	//1
	ft_printf("\nLexer: One token\n");
	ft_printf("%d - Lexer - Testing input: echo - ", i++);
	lexer_test(&tokens, &ast, "echo");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "echo") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//2
	ft_printf("%d - Lexer - Testing input: \"texto\" - ", i++);
	lexer_test(&tokens, &ast, "\"texto\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"texto\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//3
	ft_printf("%d - Lexer - Testing input: \"\'texto\'\" - ", i++);
	lexer_test(&tokens, &ast, "\"\'texto\'\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"\'texto\'\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//4
	ft_printf("%d - Lexer - Testing input: \"\"texto1\"texto2\" - ", i++);
	lexer_test(&tokens, &ast, "\"\"texto1\"texto2\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"\"texto1\"texto2\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//5
	int		types1[4] = {WORD, WORD, REDIRECT, WORD};
	char	*words1[5] = {"echo", "\"echo > arq1\"", ">", "arq1", NULL};
	ft_printf("%d - Lexer - Testing input: echo \"echo > arq1\" > arq1 - ", i++);
	lexer_test(&tokens, &ast, "echo \"echo > arq1\" > arq1");
	while (words1[j] != NULL)
	{
		assert(tokens->type == types1[j]);
		assert(ft_strcmp(tokens->literal, words1[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//6
	int		types2[4] = {WORD, WORD, REDIRECT, WORD};
	char	*words2[5] = {"echo", "\"echo >> arq1\"", ">", "arq1", NULL};
	ft_printf("%d - Lexer - Testing input: echo \"echo >> arq1\" > arq1 - ", i++);
	lexer_test(&tokens, &ast, "echo \"echo >> arq1\" > arq1");
	while (words2[j] != NULL)
	{
		assert(tokens->type == types2[j]);
		assert(ft_strcmp(tokens->literal, words2[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//7
	ft_printf("%d - Lexer - Testing input: \"\"texto1\" texto2\" - ", i++);
	lexer_test(&tokens, &ast, "\"\"texto1\" texto2\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"\"texto1\" texto2\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//8
	ft_printf("%d - Lexer - Testing input: \"\"texto1\" \'texto2\'\" - ", i++);
	lexer_test(&tokens, &ast, "\"\"texto1\" \'texto2\'\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"\"texto1\" \'texto2\'\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	//9
	ft_printf("%d - Lexer - Testing input: \"\'texto1\' \"texto2\"\" - ", i++);
	lexer_test(&tokens, &ast, "\"\'texto1\' \"texto2\"\"");
	assert(tokens->type == WORD);
	assert(ft_strcmp(tokens->literal, "\"\'texto1\' \"texto2\"\"") == 0);
	ft_printf("\033[32mOK\033[0m\n");

	ft_printf("\nLexer: Multiple tokens\n");
	//10
	int		types3[2] = {WORD, WORD};
	char	*words3[3] = {"echo", "texto", NULL};
	ft_printf("%d - Lexer - Testing input: echo texto - ", i++);
	lexer_test(&tokens, &ast, "echo texto");
	while (words3[j] != NULL)
	{
		assert(tokens->type == types3[j]);
		assert(ft_strcmp(tokens->literal, words3[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//11
	int		types4[2] = {WORD, REDIRECT};
	char	*words4[3] = {"echo", ">", NULL};
	ft_printf("%d - Lexer - Testing input: echo > - ", i++);
	lexer_test(&tokens, &ast, "echo >");
	while (words4[j] != NULL)
	{
		assert(tokens->type == types4[j]);
		assert(ft_strcmp(tokens->literal, words4[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//12
	int		types5[4] = {WORD, WORD, REDIRECT, WORD};
	char	*words5[5] = {"echo", "texto", ">", "arq1", NULL};
	ft_printf("%d - Lexer - Testing input: echo texto > arq1 - ", i++);
	lexer_test(&tokens, &ast, "echo texto > arq1");
	while (words5[j] != NULL)
	{
		assert(tokens->type == types5[j]);
		assert(ft_strcmp(tokens->literal, words5[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//13
	int		types6[5] = {WORD, WORD, REDIRECT, WORD, WORD};
	char	*words6[6] = {"echo", "texto", "|", "grep", "texto", NULL};
	ft_printf("%d - Lexer - Testing input: echo texto | grep texto - ", i++);
	lexer_test(&tokens, &ast, "echo texto | grep texto");
	while (words6[j] != NULL)
	{
		assert(tokens->type == types6[j]);
		assert(ft_strcmp(tokens->literal, words6[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//14
	int		types7[3] = {REDIRECT, WORD, WORD};
	char	*words7[4] = {"<", "arq1", "cat", NULL};
	ft_printf("%d - Lexer - Testing input:  <arq1 cat - ", i++);
	lexer_test(&tokens, &ast, "<arq1 cat");
	while (words7[j] != NULL)
	{
		assert(tokens->type == types7[j]);
		assert(ft_strcmp(tokens->literal, words7[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	j = 0;

	//15
	int		types8[9] = {REDIRECT, WORD, WORD, WORD, REDIRECT, WORD, WORD, REDIRECT, WORD};
	char	*words8[10] = {"<", "arq1", "ls", "-al", "|", "wc", "-l", ">", "arq2", NULL};
	ft_printf("%d - Lexer - Testing input: < arq1 ls -al | wc -l     >arq2 - ", i++);
	lexer_test(&tokens, &ast, "< arq1 ls -al | wc -l     >arq2");
	while (words8[j] != NULL)
	{
		assert(tokens->type == types8[j]);
		assert(ft_strcmp(tokens->literal, words8[j]) == 0);
		tokens = tokens->next;
		j++;
	}
	ft_printf("\033[32mOK\033[0m\n");
	tokens = temp;
	finisher(tokens, ast);
}
