#include "parse.h"

int		error_before_lexxer(t_minishell *mini, char *fail)
{
	mini->exec_stat = 258;
	ft_putendl_fd(fail, 2);
	return (0);
}

int		maybe_before_shield(t_minishell *mini, int len)
{
	if (ft_isprint(mini->input[len]) && len != 0 \
	&& mini->input[len - 1] == '\\')
		return (1);
	return (0);
}

int		skip_space(t_minishell *mini, t_tokenizer *tokens, char c)
{
	while (mini->input[tokens->line_i] == ' ' && mini->input[tokens->line_i])
		tokens->line_i++;
	if (mini->input[tokens->line_i] == '\0' && c == 'e')
		return (1);
	if (mini->input[tokens->line_i] == '|' && c == 'c')
		return (1);
	if (mini->input[tokens->line_i] == ';' && c == 'b')
		return (1);
	if (maybe_shield(mini, NULL, NULL, tokens->line_i) && c == 'a')
		return (1);
	return (0);
}

int		quotes(t_minishell *mini, t_tokenizer *tokens)
{
	char	c;

	if (mini->input[tokens->line_i] == 39 || mini->input[tokens->line_i] == 34)
	{
		c = mini->input[tokens->line_i];
		while (mini->input[++tokens->line_i] != c)
		{
			if (!mini->input[tokens->line_i])
				return (1);
			if (mini->input[tokens->line_i] == '\\')
			{
				if (mini->input[++tokens->line_i] == 39)
					break ;
			}
		}
		++tokens->line_i;
	}
	else if (mini->input[tokens->line_i] == '\\' \
	&& mini->input[tokens->line_i + 1] == '\0')
		return (1);
	return (0);
}

int		before_spaces(t_minishell *mini, t_tokenizer *tokens, int c)
{
	int		i;

	i = tokens->line_i - 1;
	while (i >= 0 && mini->input[i] == ' ')
		i--;
	if (maybe_before_shield(mini, i) && c == 6)
		return (1);
	if (i != -1 && ft_strchr(ONLY_REDIR, mini->input[i]) && c == 5)//e
		return (1);
	if (i != -1 && ft_strchr(SYM_CHAR, mini->input[i]) && c == 4)//d
		return (1);
	if (i != -1 && mini->input[i] == '|' && c == 3)//c
		return (1);
	if (i != -1 && mini->input[i] == ';' && c == 2)//b
		return (1);
	if (i == -1 && c == 1)//a
		return (1);
	return (0);
}

int		pipes(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == '|')
	{
		if (mini->input[tokens->line_i + 1] == '|')
			return (error_before_lexxer(mini, SYNTAX_ERROR_PIPE_TWO));
		else if (before_spaces(mini, tokens, 1) \
		|| ((before_spaces(mini, tokens, 4)) && !before_spaces(mini, tokens, 6)))
			return (error_before_lexxer(mini, SYNTAX_ERROR_PIPE_ONE));
		tokens->line_i++;
		if (skip_space(mini, tokens, 'e') \
		|| ft_strchr(SYM_CHAR, mini->input[tokens->line_i]))
			return (error_before_lexxer(mini, SYNTAX_ERROR_PIPE_ONE));
	}
	return (1);
}

int		sems(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == ';')
	{
		if (mini->input[tokens->line_i + 1] == ';')
			return (error_before_lexxer(mini, SYNTAX_ERROR_SEM_TWO));
		else if (before_spaces(mini, tokens, 1) \
		|| (before_spaces(mini, tokens, 5) && !before_spaces(mini, tokens, 6)))
			return (error_before_lexxer(mini, SYNTAX_ERROR_SEM_ONE));
		tokens->line_i++;
		if (skip_space(mini, tokens, 'b'))
			return (error_before_lexxer(mini, SYNTAX_ERROR_SEM_ONE));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	return (1);
}

int		check_left1(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '<')
		i++;
	if (i == 1 || i == 2 || i == 3)
	{
		tokens->line_i += i;
		if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
		else if (skip_space(mini, tokens, 'b'))
			return (sems(mini, tokens));
		if (mini->input[tokens->line_i - 1] == ' ')
			tokens->line_i--;
		if (i == 1)
			return (1);
		return (0);
	}
	if (i == 4)
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_LEFT));
	if (i == 5)
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_DLEFT));
	else
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_TLEFT));
}

int		check_left2(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '<')
		i++;
	if (i == 1)
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_LEFT));
	if (i == 2)
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_DLEFT));
	else
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_TLEFT));
}

int		redirs_left(t_minishell *mini, t_tokenizer *tokens)
{
	if (before_spaces(mini, tokens, 6) || !before_spaces(mini, tokens, 5))
	{
		if (!check_left1(mini, tokens))
			return (0);
		else if (skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_ALONE));
	}
	else if (before_spaces(mini, tokens, 5) && !before_spaces(mini, tokens, 6))
		return (check_left2(mini, tokens));
	return (1);
}

int		redirs_right1(t_minishell *mini, t_tokenizer *tokens, int c)
{
	if (c == 1)
	{
		tokens->line_i++;
		if (mini->input[tokens->line_i] == '|' \
		|| skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_ALONE));
		else if (skip_space(mini, tokens, 'b'))
			return (sems(mini, tokens));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	if (c == 2)
	{
		tokens->line_i += 2;
		if (skip_space(mini, tokens, 'e'))
			return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_ALONE));
		if (sems(mini, tokens))
			return (sems(mini, tokens));
		else if (skip_space(mini, tokens, 'c'))
			return (pipes(mini, tokens));
	}
	return (1);
}

int		redirs_right(t_minishell *mini, t_tokenizer *tokens)
{
	int		i;

	i = 0;
	while (mini->input[tokens->line_i + i] == '>')
		i++;
	if (i == 1)
		return (redirs_right1(mini, tokens, 1));
	if (i == 2)
		return (redirs_right1(mini, tokens, 2));
	if (i == 3)
	{
		if (mini->input[tokens->line_i + i] == '|')
			return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_RIGHT_PIPE));
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_RIGHT));
	}
	else if (i >= 4)
		return (error_before_lexxer(mini, SYNTAX_ERROR_REDIR_DRIGHT));
	return (1);
}

int		redirs(t_minishell *mini, t_tokenizer *tokens)
{
	if (mini->input[tokens->line_i] == '<')
		return (redirs_left(mini, tokens));
	else if (mini->input[tokens->line_i] == '>')
		return (redirs_right(mini, tokens));
	return (1);
}

int		check_before_lexxer(t_minishell *mini, t_tokenizer *tokens)
{
	if (skip_space(mini, tokens, 'e'))
		return (1);
	while (mini->input[tokens->line_i] != '\0')
	{
		if (skip_space(mini, tokens, 'e'))
			break ;
		if (quotes(mini, tokens))
			return (1);
		else if (!pipes(mini, tokens))
			return (1);
		else if (!sems(mini, tokens))
			return (1);
		else if (!redirs(mini, tokens))
			return (1);
		if (maybe_shield(mini, NULL, NULL, tokens->line_i))
			tokens->line_i += 2;
		else
			tokens->line_i++;
	}
	return (0);
}
