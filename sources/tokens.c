#include "parse.h"

int		maybe_shield(t_minishell *mini, t_tokenizer *tokens, t_parser *parse, int len)
{
	if (mini->input[len] == '\\' && !tokens && !parse)
	{
		if (ft_isprint(mini->input[len + 1]) || mini->input[len + 1] == ' ')
			return (1);
	}
	if (!mini && !parse && len == 0 \
	&& tokens->tokens[tokens->tok_i][tokens->line_i] == '\\')
	{
		if (ft_isprint(mini->input[len + 1]) || mini->input[len + 1] == ' ')
			return (1);
	}
	return (0);
}

void	tokens_clear(t_tokenizer *tokens)
{
	tokens->line_i = 0;
	tokens->tok_i = 0;
	tokens->fail = 0;
	tokens->line = NULL;
	tokens->tokens = NULL;
}

void	sort_quote(t_tokenizer *tokens, char *line)
{
	while (line[++tokens->tok_i] != 39 && line[tokens->tok_i])
	{
		tokens->line = ft_charjoin(&tokens->line, line[tokens->tok_i]);
	}
}

int		one_sort_after_dollar(char c)
{
	if (c == 33 || c == '@' || ft_isdigit(c) || c == 42)
		return (1);
	if (c == '?')
		return (2);
	return (0);
}

void	check_env(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	int i;
	char *str;
	char *tmp;

	i = -1;
	while (mini->env[++i])
	{
		if (!(ft_strncmp(mini->env[i], line, ft_strlen(line))) && mini->env[i][ft_strlen(line)] == '=')
		{
			if (!(tmp = ft_substr(mini->env[i], ft_strlen(line) + 1, ft_strlen(mini->env[i]) - ft_strlen(line) - 1)))
				exit(EXIT_FAILURE);
			str = tokens->line;
			if (!(tokens->line = ft_strjoin(str, tmp)))
				exit(EXIT_FAILURE);
			free(str);
			free(tmp);
			return ;
		}
	}
}

void	add_exec_stat(t_minishell *mini, t_tokenizer *tokens)
{
	char	*str;
	char	*tmp;

	tokens->tok_i++;
	if (!(tmp = ft_itoa(mini->exec_stat)))
		exit(ERROR_BAD_MALLOC);
	mini->exec_stat = 0;
	str = tokens->line;
	if (!(tokens->line = ft_strjoin(str, tmp)))
		exit(ERROR_BAD_MALLOC);
	free(str);
	free(tmp);
}

void sort_dollar(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	char	*cash;

	if (!(cash = ft_strdup("")))
		exit(ERROR_BAD_MALLOC);
	if (one_sort_after_dollar(line[tokens->tok_i + 1]) == 1)
	{
		cash = ft_charjoin(&cash, line[++tokens->tok_i]);
		check_env(mini, tokens, cash);
	}
	else if (one_sort_after_dollar(line[tokens->tok_i + 1]) == 2)
		add_exec_stat(mini, tokens);
	else if (ft_isalpha(line[tokens->tok_i + 1]) || line[tokens->tok_i + 1] == '_')
	{
		while (line[++tokens->tok_i] && (ft_isalpha(line[tokens->tok_i]) || ft_isdigit(line[tokens->tok_i]) || line[tokens->tok_i] == '_'))
			cash = ft_charjoin(&cash, line[tokens->tok_i]);
		check_env(mini, tokens, cash);
		--tokens->tok_i;
	}
	else
		tokens->line = ft_charjoin(&tokens->line, line[tokens->tok_i]);
	free(cash);
}

int check_shielding(char backslash, char c, char n)
{
	if (n == 't')
	{
		if (backslash == 92 && (c == '$' || c == '\\' || c == '|' || c == ';' || c == 34 || c == 39 || c == '`' || c == '~'))
			return (1);
	}
	else if (n == 'f')
	{
		if (backslash == 92 && (c == '$' || c == '\\' || c == 34 || c == '`'))
			return (1);
	}
	return (0);
}

void sort_dquote(t_minishell *mini, t_tokenizer *tokens, char *line)
{
	while (line[++tokens->tok_i] != 34 && line[tokens->tok_i])
	{
		if (line[tokens->tok_i] == 36)
			sort_dollar(mini, tokens, line);
		else if (line[tokens->tok_i] == '\\')
		{
			if (check_shielding(line[tokens->tok_i], line[tokens->tok_i + 1], 'f'))
				tokens->line = ft_charjoin(&tokens->line, line[++tokens->tok_i]);
			else
			{
				tokens->line = ft_charjoin(&tokens->line, line[tokens->tok_i]);
				tokens->line = ft_charjoin(&tokens->line, line[++tokens->tok_i]);
			}
		}
		else
			tokens->line = ft_charjoin(&tokens->line, line[tokens->tok_i]);
	}
}

void	tokenizer(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	if (!(tokens->line = ft_strdup("")))
		exit(ERROR_BAD_MALLOC);
	i = -1;
	while (tokens->tokens[++i])
	{
		tokens->tok_i = -1;
		while (tokens->tokens[i][++tokens->tok_i])
		{
			if (tokens->tokens[i][tokens->tok_i] == 39)
				sort_quote(tokens, tokens->tokens[i]);
			else if (tokens->tokens[i][tokens->tok_i] == 34)
				sort_dquote(mini, tokens, tokens->tokens[i]);
			else if (tokens->tokens[i][tokens->tok_i] == 36)
				sort_dollar(mini, tokens, tokens->tokens[i]);
			else if (check_shielding(tokens->tokens[i][tokens->tok_i], tokens->tokens[i][tokens->tok_i + 1], 't'))
				tokens->line = ft_charjoin(&tokens->line, tokens->tokens[i][++tokens->tok_i]);
			else
				tokens->line = ft_charjoin(&tokens->line, tokens->tokens[i][tokens->tok_i]);
		}
		if (tokens->tokens[i + 1])
			tokens->line = ft_charjoin(&tokens->line, '\n');
	}
	free_dline(tokens->tokens);
	if (!(tokens->tokens = ft_split(tokens->line, '\n')))
		exit(ERROR_BAD_MALLOC);
	tokens->len_token = i;
	free_line(tokens->line);
}
