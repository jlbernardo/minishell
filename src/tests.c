#include "includes/minishell.h"
#include <assert.h>

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
	t_token		**tokens;
	t_ast_node	**ast;

	tokens = ft_calloc(1, sizeof(t_token *));
	ast = ft_calloc(1, sizeof(t_ast_node *));

	lexer_test(tokens, ast, "echo");
	assert(ft_strncmp((*tokens)->literal, "echo", 5) == 0);
}
