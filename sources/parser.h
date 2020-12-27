#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

typedef struct			s_tokenizer
{
	char				**sort_tokens;
	int					malloc_sort;
	int					i;
	char				**tokens;
	int					malloc_tok;
	int					len;
	int					len_i;
	char				*cash;
}						t_tokenizer;

/*
typedef struct			s_lexxer
{
	char				**tokens;
	int					len;
}						t_lexxer;
*/

typedef struct			s_parser
{
	int					i;
	char				*cmd;
	char				**arg;
	int					i_arg;
	int					malloc_arg;
	struct s_parser		*pipe;
	struct s_parser		*redir;
	struct s_parser		*sem;
}						t_parser;

typedef struct			s_minishell
{
	char				*input;
	int					flag;
	char				**env;
	int					i_env;
//	char				*home_path;
	int					line_i;
}						t_minishell;

/*
** parser
*/

t_parser				*parser(t_tokenizer *token);

/*
** lexer
*/

//t_lexxer				*lexxer(t_minishell *mini);

/*
** tokenizer
*/

t_tokenizer				*tokenizer(t_minishell *mini);

#endif
