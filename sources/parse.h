#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <stdio.h>

# define ERROR_BAD_MALLOC 1
# define SYNTAX_ERROR_SEM_ONE "minishell: syntax error near unexpected token `;'"
# define SYNTAX_ERROR_SEM_TWO "minishell: syntax error near unexpected token `;;'"
# define SYNTAX_ERROR_PIPE_ONE "minishell: syntax error near unexpected token `|'"
# define SYNTAX_ERROR_PIPE_TWO "minishell: syntax error near unexpected token `||'"
# define SYNTAX_ERROR_REDIR_LEFT "minishell: syntax error near unexpected token `<'"
# define SYNTAX_ERROR_REDIR_DLEFT "minishell: syntax error near unexpected token `<<'"
# define SYNTAX_ERROR_REDIR_TLEFT "minishell: syntax error near unexpected token `<<<'"
# define SYNTAX_ERROR_REDIR_RIGHT "minishell: syntax error near unexpected token `>'"
# define SYNTAX_ERROR_REDIR_RIGHT_PIPE "minishell: syntax error near unexpected token `>|'"
# define SYNTAX_ERROR_REDIR_DRIGHT "minishell: syntax error near unexpected token `>>'"
# define SYNTAX_ERROR_REDIR_ALONE "minishell: syntax error near unexpected token `newline'"
# define SYM_CHAR "<;>|"
# define FOR_SEM ";|"
# define ONLY_REDIR "<>"

typedef struct			s_tokenizer
{
	char				**tokens;
	int					tok_i;
	int					len_token;
	char				*line;
	int					line_i;
	int					fail;
}						t_tokenizer;

typedef struct			s_parser
{
	char				*cmd;
	char				**arg;
	int					i_arg;
	char				*ard_red;
	struct s_parser		*pipe;
	struct s_parser		*redir;
	int					type;
	int					fail;
}						t_parser;

typedef struct			s_minishell
{
	char				*input;
	int					flag;
	char				**env;
	int					i_env;
	char				*home_path;
	int					line_i;
	int					exec_stat;
}						t_minishell;

//void					check_input(t_minishell *mini);
//t_parser				*parser(t_minishell *mini, t_tokenizer *tokens);




void					check_input(t_minishell *mini);
int						lexxer(t_minishell *mini, t_tokenizer *tokens);
void					tokenizer(t_minishell *mini, t_tokenizer *tokens);
int						free_dline(char **line);
int						free_line(char *line);
t_parser				*parser(t_minishell *mini, t_tokenizer *tokens);
void					my_print(t_parser *parse);
void					tokens_clear(t_tokenizer *tokens);
void					free_tokens(t_tokenizer *tokens);
void					free_parse(t_parser *parse);
int						skipping_spaces(t_minishell *mini, t_tokenizer *tokens, char c);
int						check_before_lexxer(t_minishell *mini, t_tokenizer *tokens);
int						maybe_shield(t_minishell *mini, t_tokenizer *tokens, t_parser *parse, int len);


void					command_output(t_parser *data, t_minishell *in);

#endif
