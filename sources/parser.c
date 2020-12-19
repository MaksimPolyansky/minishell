#include "parser.h"

t_parser	*parser_malloc(void)
{
	t_parser	*tuk;

	if (!(tuk = (t_parser*)ft_calloc(sizeof(t_parser), 1)) \
	|| !(tuk->cmd = ft_strdup("")) || !(tuk->flag = ft_strdup("")) \
	|| !(tuk->arg = (char**)ft_calloc(sizeof(char*), 1)))
		return (NULL);
	return (tuk);
}

char		*search_dquote(t_minishell *mini, t_parser *parser)
{
	while (mini->input[mini->line_i] && mini->input[mini->line_i] != 34)
	{

	}
}

char		*search_quote(t_minishell *mini, t_parser *parser)
{
	while (mini->input[mini->line_i] && mini->input[mini->line_i] != 39)
	{

	}
}

char		*check_line(t_minishell *mini, t_parser *tuk, char c)
{
	char	*tmp1;
	char	*tmp2;
	char	*cash;

	if (!(cash = ft_strdup("")))
		return (NULL);
	while (mini->input[mini->line_i] && mini->input[mini->line_i] != c)
	{
		if (mini->input[mini->line_i] == 34)
		{
			mini->line_i++;
			tmp1 = cash;
			tmp2 = search_dquote(mini, tuk);
			cash = ft_strjoin(cash, tmp2);
			free(tmp1);
			free(tmp2);
		}
		else if (mini->input[mini->line_i] == 39)
		{
			mini->line_i++;
			tmp1 = cash;
			tmp2 = search_quote(mini, tuk);
			cash = ft_strjoin(cash, tmp2);
			free(tmp1);
			free(tmp2);
		}
		else
		{
			tmp1 = cash;
			cash = ft_charjoin(cash, mini->input[mini->line_i++]);
			free(tmp1);
		}
	}
	return (cash);
}

t_parser		*parser(t_minishell *mini)
{
	t_parser	*tuk;
	char		*cash;

	if (!(tuk = parser_malloc()))
		return (NULL);
	while (mini->input[mini->line_i])
	{
		if (mini->input[mini->line_i] == 32)
			mini->line_i++;
		else
		{
			if (*tuk->cmd == '\0')
			{
				//cash = ;
				tuk->cmd = check_line(mini, tuk, 32);
				//free(cash);
			}
			else if (*tuk->cmd != '\0')
			{
				//cash = ;
				tuk->arg[tuk->i_arg] = check_line(mini, tuk, 32);
				//free(cash);
				tuk->i_arg++;
			}
		}
	}
	return (tuk);
}
