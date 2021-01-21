#include "parse.h"

int counter_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	clear_mini(t_minishell *mini)
{
	mini->env = NULL;
	mini->exec_stat = 0;
	mini->flag = 0;
	mini->home_path = NULL;
	mini->i_env = 0;
	mini->input = NULL;
	mini->line_i = 0;
}

int main(int argc, char **argv, char **envp)
{
	int i;
	t_minishell mini;

	clear_mini(&mini);
	i = -1;
	mini.i_env = counter_envp(envp);
	if (!(mini.env = (char**)malloc(mini.i_env * sizeof(char*))))
		return (-1);
	while (envp[++i])
	{
		if (!(mini.env[i] = ft_strdup(envp[i])))
			return (-1);
	}
	while (1)
	{
		mini.line_i = 0;
		ft_putstr_fd("minishell--> ", 1);
		get_next_line(0, &mini.input);
		check_input(&mini);
		free(mini.input);
	}
	i = -1;
	while (++i < mini.i_env)
		free(mini.env[i]);
	free(mini.env);
	return (0);
}
