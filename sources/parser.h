#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

typedef struct			s_env
{
	char				**env;

}						t_env;


typedef struct			s_parser
{
	char				*cmd;
	char				*flag;
	char				**arg;
	int					i_arg;
	int					i;
	struct s_parser		*pipe;
	struct s_parser		*redir;
	struct s_parser		*sem;
}						t_parser;

t_parser				*parser(char *line);

#endif
