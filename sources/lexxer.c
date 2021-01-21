#include "parse.h"

int		error_lexxer(t_minishell *mini, t_tokenizer *tokens, char *fail)
{
	free(tokens->line);
	tokens->line = NULL;
	mini->exec_stat = 258;
	ft_putendl_fd(fail, 2);
	return (0);
}

void	dquote_or_quote(t_minishell *mini, t_tokenizer *tokens)
{
	char	c;

	c = mini->input[mini->line_i];
	tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i]);
	while (mini->input[++mini->line_i] != c)
	{
		if (mini->input[mini->line_i] == '\\')
		{
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i++]);
			if (mini->input[mini->line_i] == 39)
				break ;
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i]);
		}
		else
			tokens->line = ft_charjoin(&tokens->line, \
			mini->input[mini->line_i]);
	}
	tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i++]);
}

int		skipping_spaces(t_minishell *mini, t_tokenizer *tokens, char c)
{
	while (mini->input[mini->line_i] == ' ' && mini->input[mini->line_i])
		mini->line_i++;
	if (mini->input[mini->line_i] && *tokens->line != '\0' && c == 'a')
		return (1);
	if (mini->input[mini->line_i] == ';' && c == 'b')
		return (1);
	if (mini->input[mini->line_i] == '|' && c == 'c')
		return (1);
	if ((mini->input[mini->line_i] == '>' || \
	mini->input[mini->line_i] == '<') && c == 'd')
		return (1);
	if (mini->input[mini->line_i] == '\0' && c == 'e')
		return (1);
	return (0);
}

int		maybe_sem(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == ';')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' \
		&& tokens->line[0] != '\0')
			if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
				exit(ERROR_BAD_MALLOC);
		if (!(tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i++])))
			exit(ERROR_BAD_MALLOC);
		return (1);
	}
	return (0);
}

int		maybe_pipe(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == '|')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' && tokens->line[0] != '\0')
			if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
				exit(ERROR_BAD_MALLOC);
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			exit(ERROR_BAD_MALLOC);
		if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
			exit(ERROR_BAD_MALLOC);
	}
	return (0);
}

int		maybe_redir(t_tokenizer *tokens, t_minishell *mini)
{
	if (mini->input[mini->line_i] == '>' || mini->input[mini->line_i] == '<')
	{
		if (tokens->line[ft_strlen(tokens->line) - 1] != '\n' && tokens->line[0] != '\0')
			tokens->line = ft_charjoin(&tokens->line, '\n');
		while (ft_strchr(ONLY_REDIR, mini->input[mini->line_i]))
			tokens->line = ft_charjoin(&tokens->line, mini->input[mini->line_i++]);
		if (!(tokens->line = ft_charjoin(&tokens->line, '\n')))
			exit(ERROR_BAD_MALLOC);
	}
	return (0);
}

int		lexxer_next(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	if (!(tokens->tokens = ft_split(tokens->line, '\n')))
		exit(ERROR_BAD_MALLOC);
	i = -1;
	tokens->len_token = 1;
	while (tokens->line[++i] != '\0')
	{
		if (tokens->line[i] != '\n')
			tokens->len_token++;
	}
	free_line(tokens->line);
	return (1);
}

int		lexxer_utils(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[mini->line_i] == 39 \
	|| mini->input[mini->line_i] == 34)
		dquote_or_quote(mini, tokens);
	if (maybe_sem(tokens, mini) || maybe_pipe(tokens, mini) \
	|| maybe_redir(tokens, mini))
		return (lexxer_next(mini, tokens));
	if (maybe_shield(mini, NULL, NULL, mini->line_i))
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])) \
		|| !(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			exit(ERROR_BAD_MALLOC);
	}
	if (!ft_strchr(SYM_CHAR, mini->input[mini->line_i]))
	{
		if (!(tokens->line = ft_charjoin(&tokens->line, \
		mini->input[mini->line_i++])))
			exit(ERROR_BAD_MALLOC);
	}
	return (0);
}

int		lexxer(t_minishell *mini, t_tokenizer *tokens)
{
	if (check_before_lexxer(mini, tokens))
		return (0);
	if (!(tokens->line = ft_strdup("")))
		exit(ERROR_BAD_MALLOC);
	while (mini->input[mini->line_i] != '\0')//check error
	{
		if (skipping_spaces(mini, tokens, 'a'))
			tokens->line = ft_charjoin(&tokens->line, '\n');
		while (mini->input[mini->line_i] != '\0' && mini->input[mini->line_i] != ' ')
			if (lexxer_utils(mini, tokens))
				return (1);
	}
	return (lexxer_next(mini, tokens));
}
