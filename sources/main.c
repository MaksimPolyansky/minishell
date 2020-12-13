#include "parser.h"
#include <stdio.h>

/*int	main(int ac, char **av)
{
	t_parser	*pars;

	pars = parser(av);
	ft_putstr_fd(pars->cmd, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(pars->flag, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(pars->arg[0], 1);
	ft_putchar_fd('\n', 1);
	return (0);
}*/

int main(void)
{
	char		*input;
	char		output[1000];
	t_parser	*pars;

	while (1)
	{
		//ft_strdel(&input);
		//ft_strdel(**output);
		ft_putstr_fd("minishell--> ", 1);
		get_next_line(0, &input);
		pars = parser(input);
		if (pars->cmd)
			printf("cmd: %s|\n", pars->cmd);
		if (pars->flag)
			printf("flag: %s|\n", pars->flag);
		while (pars->i_arg-- > 0)
			printf("arg: %s|\n", pars->arg[pars->i_arg]);
		//command_output(/* структура */ input, output);
		free(input);

	}
	return (0);
}
