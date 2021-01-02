#include "parser.h"

void free_token(t_tokenizer *token)
{
	int i;

	if (token->cash)
		free(token->cash);
	if (token->sort_tokens)
	{
		i = 0;
		while (i < token->malloc_sort)
			free(token->sort_tokens[i++]);
		free(token->sort_tokens);
	}
	if (token->tokens)
	{
		i = 0;
		while (i < token->malloc_tok)
			free(token->tokens[i++]);
		free(token->tokens);
	}
	if (token)
		free(token);
}

void add_malloc_char(char **string, char c)
{
	char *str;

	str = (*string);
	if (!((*string) = ft_charjoin((*string), c)))
		exit(EXIT_FAILURE);
	free(str);
}

int check_shielding(char backslash, char c, char n)
{
	if (n == 'f')
	{
		if (backslash == 92 && (c == 34 || c == 39))
			return (1);
	}
	else if (n == 's')
	{
		if (backslash == 92 && (c == 34))
			return (1);
		else if (backslash == 92 && (c == 39))
			return (2);
	}
	return (0);
}

int check_tokens(t_tokenizer *token, char *line)
{
}

void check_env(t_minishell *mini, t_tokenizer *token)
{
	int i;
	char *str;
	char *tmp;

	i = -1;
	while (mini->env[++i])
		if (!(ft_strncmp(mini->env[i], token->cash, ft_strlen(token->cash))) && mini->env[i][ft_strlen(token->cash)] == 61)
		{
			str = token->sort_tokens[token->i];
			if (!(tmp = ft_substr(mini->env[i], ft_strlen(token->cash) + 1,
								ft_strlen(mini->env[i]) - ft_strlen(token->cash) - 1)))
				exit(EXIT_FAILURE);
			if (!(token->sort_tokens[token->i] =
					ft_strjoin(token->sort_tokens[token->i], tmp)))
				exit(EXIT_FAILURE);
			free(str);
			free(tmp);
			return ;
		}
}

int one_sort_after_dollar(char c)
{
	if (c == 33 || c == '@' || ft_isdigit(c) || c == 42)
		return (1);
	return (0);
}

void sort_dollar(t_minishell *mini, t_tokenizer *token, char *line)
{
	if (!(token->cash = ft_strdup("")))
		exit(EXIT_FAILURE);
	if (one_sort_after_dollar(line[token->len_i + 1]))
	{
		add_malloc_char(&token->cash, line[++token->len_i]);
		check_env(mini, token);
	}
	else if (ft_isalpha(line[token->len_i + 1]))
	{
		while (line[++token->len_i] && (ft_isdigit(line[token->len_i]) || ft_isalpha(line[token->len_i])))
			add_malloc_char(&token->cash, line[token->len_i]);
		check_env(mini, token);
		--token->len_i;
	}
	else
		add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
	free(token->cash);
}

void sort_dquote_quote(t_minishell *mini, t_tokenizer *token, char *line)
{
	add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
	while (line[++token->len_i] != 39 && line[token->len_i])
	{
		if (line[token->len_i] == 34)
			++token->len_i;
		if (line[token->len_i] == 36)
			sort_dollar(mini, token, line);
		else if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) != 0)
		{
			if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) == 1)
				add_malloc_char(&token->sort_tokens[token->i], line[++token->len_i]);
			else
			{
				add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
				add_malloc_char(&token->sort_tokens[token->i], line[++token->len_i]);
			}
		}
		else
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
	}
	add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
}

void sort_dquote(t_minishell *mini, t_tokenizer *token, char *line)
{
	while (line[++token->len_i] != 34 && line[token->len_i])
	{
		if (line[token->len_i] == 36)
			sort_dollar(mini, token, line);
		else if (line[token->len_i] == 39)
			sort_dquote_quote(mini, token, line);
		else if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) != 0)
		{
			if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) == 1)
				add_malloc_char(&token->sort_tokens[token->i], line[++token->len_i]);
			else
			{
				add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
				add_malloc_char(&token->sort_tokens[token->i], line[++token->len_i]);
			}
		}
		else
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
	}
}

void sort_quote(t_minishell *mini, t_tokenizer *token, char *line)
{
	while (line[++token->len_i] != 39 && line[token->len_i])
	{
		if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) == 2)
		{
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
			return ;
		}
		else if (check_shielding(line[token->len_i], line[token->len_i + 1], 115) == 1)
		{
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i++]);
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
		}
		else if (line[token->len_i] == 34)
		{
			while (line[++token->len_i] != 34 && line[token->len_i])
			{
				if (line[token->len_i] == 39)
					sort_dquote_quote(mini, token, line);
				else
					add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
			}
		}
		else
			add_malloc_char(&token->sort_tokens[token->i], line[token->len_i]);
	}
}

t_tokenizer *sorting_tokens(t_minishell *mini, t_tokenizer *token)
{
	int i;

	if (!(token->sort_tokens = (char **)ft_calloc(sizeof(char *), (token->malloc_sort = token->len + 5))))
		exit(EXIT_FAILURE);
	i = -1;
	while (token->tokens[++i])
	{
		//check_tokens(token, token->tokens[i]);
		//token->i = 0;
		if (!(token->sort_tokens[token->i] = ft_strdup("")))
			exit(EXIT_FAILURE);
		token->len_i = -1;
		while (token->tokens[i][++token->len_i])
		{
			if (token->tokens[i][token->len_i] == 39)
				sort_quote(mini, token, token->tokens[i]);
			else if (token->tokens[i][token->len_i] == 34)
				sort_dquote(mini, token, token->tokens[i]);
			else if (token->tokens[i][token->len_i] == 36)
				sort_dollar(mini, token, token->tokens[i]);
			else if (check_shielding(token->tokens[i][token->len_i], token->tokens[i][token->len_i + 1], 102))
				add_malloc_char(&token->sort_tokens[token->i], token->tokens[i][++token->len_i]);
			else
				add_malloc_char(&token->sort_tokens[token->i], token->tokens[i][token->len_i]);
		}
		token->i++;
		//**token->sort_tokens++;
	}
	return (token);
}

void token_quote(t_minishell *mini, t_tokenizer *token)
{
	while (mini->input[mini->line_i] != 39 && mini->input[mini->line_i])
	{
		if (mini->input[mini->line_i + 1] == 39 && check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			return ;
		}
		else if (mini->input[mini->line_i] == 34)
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			while (mini->input[mini->line_i] != 34 && mini->input[mini->line_i])
			{
				if (mini->input[mini->line_i] == 39)
					token_dquote_quote(mini, token);
				else if (check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
				{
					add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
					add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
				}
				else
					add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			}
		}
		else if (check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
		}
		else
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
	}
	add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
}

void token_dquote_quote(t_minishell *mini, t_tokenizer *token)
{
	while (mini->input[mini->line_i] != 39 && mini->input[mini->line_i])
	{
		if (mini->input[mini->line_i] == 34 && mini->input[mini->line_i])
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			token_dquote(mini, token);
		}
		else if (check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
		}
		else
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
	}
	add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
}

void token_dquote(t_minishell *mini, t_tokenizer *token)
{
	while (mini->input[mini->line_i] != 34 && mini->input[mini->line_i])
	{
		if (mini->input[mini->line_i] == 39 && mini->input[mini->line_i])
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			token_dquote_quote(mini, token);
		}
		else if (check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
		}
		else
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
	}
	add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
}

void tokenizer1(t_minishell *mini, t_tokenizer *token)
{
	if (!(token->tokens[token->len] = ft_strdup("")))
		exit(EXIT_FAILURE);
	while (mini->input[mini->line_i] && mini->input[mini->line_i] != 32)
	{
		if (mini->input[mini->line_i] == 34) //dquote
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			token_dquote(mini, token);
		}
		else if (mini->input[mini->line_i] == 39) //quote
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			token_quote(mini, token);
		}
		else if (check_shielding(mini->input[mini->line_i], mini->input[mini->line_i + 1], 102))
		{
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
		}
		else
			add_malloc_char(&token->tokens[token->len], mini->input[mini->line_i++]);
	}
	token->len++;
}

int how_many_string(t_minishell *mini)
{
	int how;
	int i;

	i = -1;
	how = 1;
	while (mini->input[++i])
	{
		if (mini->input[i] == 32 && mini->input[i + 1] != 32)
			how++;
	}
	return (how + 5);
}

t_tokenizer *tokenizer(t_minishell *mini)
{
	t_tokenizer *token;
	int i;

	mini->line_i = 0;
	if (!(token = (t_tokenizer *)ft_calloc(sizeof(t_tokenizer), 1)) || !(token->tokens = (char **)ft_calloc(sizeof(char *), (token->malloc_tok = how_many_string(mini)))))
		exit(EXIT_FAILURE);
	while (mini->input[mini->line_i])
	{
		if (mini->input[mini->line_i] == 32)
			mini->line_i++;
		else if (ft_isprint(mini->input[mini->line_i]))
			tokenizer1(mini, token);
	}
//	return (token);
	return (sorting_tokens(mini, token));
}
