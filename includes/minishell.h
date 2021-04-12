/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <wphylici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:01:56 by wphylici          #+#    #+#             */
/*   Updated: 2021/02/01 16:57:49 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include <signal.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

int						ft_strcmp(char *s1, char *s2);
void					ft_free_array(t_parser *data, char **array);
char					*ft_strcpy(char *dest, char *src);
void					free_struct(void);
char					*del_char_in_str(char *str, char c);
void					str_free(char **s);
int						counter_dbl_arr(char **arr);
int						check_availability(void);
void					free_double_array(char **arr);
int						check(t_parser *data, char *arg, int j);
char					*trim_str(char *str);
void					invalid_identifier(t_parser *data, int i);
void					sig_handler(int sig);
int						change_env(t_parser *data, int i, int j);
int						check_name(t_parser *data, int i);
int						output(int i, int j);
int						redirect(t_parser *data);
int						check_valid(t_parser *data, int i);
void					del_few_env(t_parser *data, int j);
int						processing_error_cmd(t_parser *data);
int						error_redir(t_parser *tmp);
void					save_home_path(void);
int						init_cmd_path(t_parser *data);
void					list_counter(t_parser *data);
void					ft_pipe(t_parser *data);
void					command_output(t_parser *data);
void					my_exit(t_parser *data, int exit_status);
int						cmd_not_found_cmd(t_parser *data);
int						no_such_file_cmd(t_parser *data);
int						red_type_3(t_parser *tmp);
int						red_type_2(t_parser *tmp);
int						red_type_1(t_parser *tmp);
void					strjoin_cmd_path(t_parser *data, int i);
int						clean_oldpwd(void);
void					after_command_output(void);

/*
**	cmd
*/

void					cmd_cd(t_parser *data);
void					cmd_echo(t_parser *data);
void					cmd_env(void);
void					cmd_exit(t_parser *data);
void					cmd_pwd(void);
int						cmd_export(t_parser *data);
void					cmd_unset(t_parser *data);
int						cmd_execve(t_parser *data);

#endif
