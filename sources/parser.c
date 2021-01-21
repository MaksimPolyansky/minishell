#include "parse.h"

void	check_input(t_minishell *mini)
{
	t_tokenizer		tokens;
	t_parser		*parse;

	tokens_clear(&tokens);
	if (lexxer(mini, &tokens))
	{
		tokenizer(mini, &tokens);
		tokens.tok_i = -1;
		parse = parser(mini, &tokens);
		free_tokens(&tokens);
		my_print(parse);
		free_parse(parse);
		if (mini->input[mini->line_i])
			check_input(mini);
	}
}
