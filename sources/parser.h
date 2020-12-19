#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"



typedef struct			s_parser
{
	char				*cmd;
	char				*flag;
	char				**arg;
	int					i_arg;
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
	char				*home_path;
	int					line_i;
}						t_minishell;

t_parser				*parser(t_minishell *mini);

#endif
