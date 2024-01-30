#include "includes/minishell.h"
#include <assert.h>
#include <stdio.h>

int	lexer_test(t_token **tokens, t_ast_node **ast, char	*string)
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

int main(void)
{
	int i = 1;
	t_token		**tokens;
	t_ast_node	**ast;

	tokens = ft_calloc(1, sizeof(t_token *));
	ast = ft_calloc(1, sizeof(t_ast_node *));

	printf("Lexer: One token\n");
	printf("%d - Lexer - Testing input: echo - ", i++);
	lexer_test(tokens, ast, "echo");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"texto\" - ", i++);
	lexer_test(tokens, ast, "\"texto\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"texto\"", 8) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"\'texto\'\" - ", i++);
	lexer_test(tokens, ast, "\"\'texto\'\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\'texto\'\"", 10) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"\"texto1\"texto2\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\"texto2\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\"texto2\"", 17) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"\"texto1\" texto2\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\" texto2\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\" texto2\"", 19) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"\"texto1\" \'texto2\'\" - ", i++);
	lexer_test(tokens, ast, "\"\"texto1\" \'texto2\'\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\" texto2\"", 50) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("%d - Lexer - Testing input: \"\'texto1 \"texto2\"\" - ", i++);
	lexer_test(tokens, ast, "\"\'texto1 \"texto2\"\"");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "\"\"texto1\" \'texto2\'\"", 50) == 0);
	printf("\033[32mOK\033[0m\n");

	printf("Lexer: Multiple tokens\n");
	printf("%d - Lexer - Testing input: echo texto - ", i++);
	lexer_test(tokens, ast, "echo texto");
	assert((*tokens)->type == WORD);
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
	assert((*tokens)->next->type == WORD);
	assert(ft_strncmp((*tokens)->next->literal, "texto", 6) == 0);
	printf("\033[32mOK\033[0m\n");
}
