#include "parser.h"
#include <stdio.h>

int	counter_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int			i;
	t_minishell	*mini;
	t_parser	*tuk;

	i = -1;
	if (!(mini = (t_minishell*)ft_calloc(sizeof(t_minishell), 1)))
		return (-1);
	mini->i_env = counter_envp(envp);
	if (!(mini->env = (char**)malloc(mini->i_env * sizeof(char*) + 1)))
		return (-1);
	while (envp[++i])
	{
		if (!(mini->env[i] = ft_strdup(envp[i])))
			return (-1);
	}
	while (1)
	{
		i = 0;
		ft_putstr_fd("minishell--> ", 1);
		get_next_line(0, &mini->input);
		tuk = parser(mini);
		if (*tuk->cmd != '\0')
			printf("cmd: %s|\n", tuk->cmd);
		if (*tuk->flag != '\0')
			printf("flag: %s|\n", tuk->flag);
		while (tuk->i_arg > i)
			printf("arg: %s|\n", tuk->arg[i++]);
		while (tuk->i_arg-- > 0)
			free(tuk->arg[tuk->i_arg]);
		free(tuk->arg);
		free(tuk->cmd);
		free(tuk->flag);
		free(tuk);
		free(mini->input);
		ft_bzero(mini, sizeof(t_minishell));
	}
	while (mini->i_env-- > 0)
		free(mini->env[mini->i_env]);
	free(mini);
	return (0);
}
