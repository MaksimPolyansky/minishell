/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:06:17 by wphylici          #+#    #+#             */
/*   Updated: 2021/01/30 17:53:53 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <stdio.h>

# define ERROR_BAD_MALLOC 1
# define SESO "minishell: syntax error near unexpected token `;'"
# define SEST "minishell: syntax error near unexpected token `;;'"
# define SEPO "minishell: syntax error near unexpected token `|'"
# define SEPT "minishell: syntax error near unexpected token `||'"
# define SERL "minishell: syntax error near unexpected token `<'"
# define SERDL "minishell: syntax error near unexpected token `<<'"
# define SERTL "minishell: syntax error near unexpected token `<<<'"
# define SERR "minishell: syntax error near unexpected token `>'"
# define SERRP "minishell: syntax error near unexpected token `>|'"
# define SERDR "minishell: syntax error near unexpected token `>>'"
# define SERALONE "minishell: syntax error near unexpected token `newline'"
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
	char				*arg_red;
	struct s_parser		*pipe;
	struct s_parser		*redir;
	int					type;
	int					fail;
}						t_parser;

typedef struct			s_minishell
{
	struct stat			*buf_exec;
	struct stat			*buf;
	int					flag_execve;
	int					count_list;
	int					stdin;
	int					stdout;
	int					flag_input;
	int					fd[2];
	int					exec_stat;
	char				*save_cmd;
	int					line_i;
	char				**cmd_path;
	char				*home_path;
	char				*correct_home;
	int					flag;
	int					i_env;
	char				**env;
	char				*input;

}						t_minishell;

extern t_minishell		*g_in;

/*
**tokens
*/

void					sort_dquote(t_minishell *mini, t_tokenizer *tokens, \
						char *line);
int						check_shield_dquote(t_tokenizer *tokens);
void					sort_dollar_dquote(t_minishell *mini, \
						t_tokenizer *tokens, char *line);
void					sort_dollar_dquote1(t_minishell *mini, \
						t_tokenizer *tokens, char *line, char **cash);
void					add_exec_stat(t_minishell *mini, t_tokenizer *tokens);
void					check_env(t_minishell *mini, t_tokenizer *tokens, \
						char *line);
int						one_sort_after_dollar(char c);
int						maybe_shield(t_minishell *mini, t_tokenizer *tokens, \
						t_parser *parse, int len);
void					sort_quote(t_tokenizer *tokens, char *line);
void					sort_dollar(t_minishell *mini, t_parser *parse, \
						t_tokenizer *tokens);
void					sort_dollar1(t_minishell *mini, t_parser *parse, \
						t_tokenizer *tokens, char **cash);
void					check_env_dollar(t_minishell *mini, t_parser *parse, \
						t_tokenizer *tokens, char *line);
void					check_env_dollar1(t_parser *parse, \
						t_tokenizer *tokens, char *line);
int						after_dollar_alone(t_minishell *mini, t_parser *parse, \
						t_tokenizer *tokens, char **cash);
void					error_tokens(t_tokenizer *tokens, t_parser *parse);
void					tokens_clear(t_tokenizer *tokens);
void					sort_shield(t_tokenizer *tokens);
void					tokenizer(t_minishell *mini, t_parser *parse, \
						t_tokenizer *tokens);
void					free_tokens(t_tokenizer *tokens);
int						free_line_tokens(t_tokenizer *tokens);
int						free_dline_tokens(t_tokenizer *tokens);

/*
**parser
*/

void					free_parse(t_parser *parse);
int						check_sem(t_tokenizer *tokens);
t_parser				*check_pipe(t_minishell *mini, t_tokenizer *tokens);
void					check_redir_left(t_tokenizer *tokens, \
						t_parser *pars);
t_parser				*redir_left(t_minishell *mini, t_tokenizer *tokens, \
						t_parser *pars);
t_parser				*redir_right(t_minishell *mini, t_tokenizer *tokens, \
						t_parser *pars);
t_parser				*redir_dright(t_minishell *mini, t_tokenizer *tokens, \
						t_parser *pars);
t_parser				*check_redir(t_minishell *mini, t_tokenizer *tokens, \
						t_parser *pars);
t_parser				*parser(t_minishell *mini, t_tokenizer *tokens);
void					free_dline_parse(t_parser *parse);

/*
**lexxer
*/

int						maybe_sem(t_tokenizer *tokens, t_minishell *mini);
int						skipping_spaces(t_minishell *mini, \
						t_tokenizer *tokens, char c);
void					dquote_or_quote(t_minishell *mini, \
						t_tokenizer *tokens);
int						error_lexxer(t_minishell *mini, t_tokenizer *tokens, \
						char *fail);
int						maybe_pipe(t_tokenizer *tokens, t_minishell *mini);
int						maybe_redir(t_tokenizer *tokens, t_minishell *mini);
int						lexxer_next(t_tokenizer *tokens);
int						lexxer_utils(t_minishell *mini, t_tokenizer *tokens);
int						lexxer(t_minishell *mini, t_tokenizer *tokens);

/*
**before lexxer
*/

int						check_before_lexxer(t_minishell *mini, \
						t_tokenizer *tokens);
int						skip_space(t_minishell *mini, \
						t_tokenizer *tokens, char c);
int						maybe_before_shield(t_minishell *mini, \
						int len);
int						error_before_lexxer(t_minishell *mini, \
						char *fail);
int						redirs(t_minishell *mini, t_tokenizer *tokens);
int						redirs_right(t_minishell *mini, t_tokenizer *tokens);
int						redirs_right1(t_minishell *mini, \
						t_tokenizer *tokens, int c);
int						redirs_left(t_minishell *mini, t_tokenizer *tokens);
int						check_left2(t_minishell *mini, t_tokenizer *tokens);
int						quotes(t_minishell *mini, t_tokenizer *tokens);
int						before_spaces(t_minishell *mini, \
						t_tokenizer *tokens, int c);
int						pipes(t_minishell *mini, t_tokenizer *tokens);
int						sems(t_minishell *mini, t_tokenizer *tokens);
int						check_left1(t_minishell *mini, t_tokenizer *tokens);
void					redir_utils(t_parser *pars, t_tokenizer *tokens);
int						redirs_right_error(t_minishell *mini, \
						t_tokenizer *tokens);
int						check_error_syntax(t_minishell *mini, \
						t_tokenizer *tokens);

/*
**delete next string
*/

void					check_input(t_minishell *mini);

#endif
