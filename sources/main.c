#include "parser.h"
#include <stdio.h>

int counter_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	t_minishell *mini;
	t_parser *tuk;
	t_tokenizer *token;

	i = -1;
	if (!(mini = (t_minishell *)ft_calloc(sizeof(t_minishell), 1)))
		return (-1);
	mini->i_env = counter_envp(envp);
	if (!(mini->env = (char **)malloc(mini->i_env * sizeof(char *) + 1)))
		return (-1);
	while (envp[++i])
	{
		if (!(mini->env[i] = ft_strdup(envp[i])))
			return (-1);
	}
	while (1)
	{
		ft_putstr_fd("minishell--> ", 1);
		get_next_line(0, &mini->input);
		token = tokenizer(mini);
		tuk = parser(token);
		printf("len: %d|\n", token->len);
		i = 0;
		while (token->len > i)
			printf("token: %s|\n", token->tokens[i++]);
		i = 0;
		printf("sort len: %d\n", token->i);
		i = 0;
		while (token->sort_tokens[i])
			printf("sort_token: %s|\n", token->sort_tokens[i++]);
		i = 0;
		free_token(token);
		if (tuk->cmd)
			printf("cmd: %s|\n", tuk->cmd);
		printf("i_arg: %d\n", tuk->i_arg);
		i = 0;
		while (i < tuk->i_arg)
			printf("arg: %s|\n", tuk->arg[i++]);
		if (tuk->sem)
		{
			if (tuk->sem->cmd)
				printf("cmd1: %s|\n", tuk->sem->cmd);
			printf("i_arg1: %d\n", tuk->sem->i_arg);
			i = 0;
			while (i < tuk->sem->i_arg)
				printf("arg1: %s|\n", tuk->sem->arg[i++]);
		}
		free_parser(tuk);
		free(mini->input);
	}
	i = 0;
	while (i <= mini->i_env)
		free(mini->env[i++]);
	free(mini);
	return (0);
}
