/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:34:33 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/28 03:29:21 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printf_numeric_error(t_shell *mns, t_cmd *cmd, const int *tmp)
{
	(void)tmp;
	ft_printf_fd(2, "bash: exit: %s: numeric argument required\n",
		cmd->cmd_arg[1]);
	close(tmp[0]);
	close(tmp[1]);
	shell_clean (mns);
	exit (2);
}

void	bi_exit(t_shell *mns, t_cmd *cmd, const int *tmp)
{
	long	code;
	int		exit_code;

	(void)tmp;
	if (isatty(STDIN_FILENO) && !mns->is_pipe)
		ft_printf_fd(STDERR_FILENO, "exit\n");
	if (cmd->arg_cnt == 1)
	{
		exit_code = mns->exitcode;
		env_shlvl_down(mns);
		close(tmp[0]);
		close(tmp[1]);
		shell_clean(mns);
		exit (exit_code);
	}
	if (!ft_atol_safe(cmd->cmd_arg[1], &code))
		printf_numeric_error(mns, cmd, tmp);
	if (cmd->arg_cnt > 2)
	{
		ft_printf_fd(STDERR_FILENO, "bash: exit: too many arguments\n");
		update_status(mns, 1);
		return ;
	}
	exit_code = (unsigned char)code;
	update_status(mns, exit_code);
	env_shlvl_down(mns);
	close(tmp[0]);
	close(tmp[1]);
	shell_clean(mns);
	exit (exit_code);
}
