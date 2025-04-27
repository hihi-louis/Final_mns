/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_call.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:33:28 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/27 16:53:59 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	for_home(char *target)
{
	if (!target)
	{
		ft_printf_fd(STDERR_FILENO, "cd: HOME not set\n");
		return (1);
	}
	return (0);
}

static char	*get_cd_target(t_shell *mns, char **args)
{
	char	*target;

	if (mns->cmd_group->arg_cnt == 1 
		|| (mns->cmd_group->arg_cnt == 2 && (!ft_strcmp(args[1], "~") 
		|| !ft_strcmp(args[1], "--"))))
	{
		target = get_env_val(mns, "HOME");
		for_home(target);
	}
	else if (mns->cmd_group->arg_cnt == 2 && (!ft_strcmp(args[1], "-")))
	{
		target = get_env_val(mns, "OLDPWD");
		if (!target)
			return (ft_printf_fd(2, "cd: OLDPWD not set\n"), NULL);
		printf("%s\n", target);
	}
	else if (mns->cmd_group->arg_cnt > 2)
	{
		ft_printf_fd(STDERR_FILENO, "bash: cd: too many arguments\n");
		return (update_status(mns, 1), NULL);
	}
	else
		target = args[1];
	return (target);
}

static void	update_pwd(t_shell *mns, char *target)
{
	char	*logic_pwd;
	char	*cur_pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_val(&mns->env, "PWD", cwd);
	}
	else
	{
		ft_printf_fd(2, "cd: error retrieving current directory:");
		ft_printf_fd(2, " getcwd: cannot access parent directories:");
		ft_printf_fd(2, " No such file or directory\n");
		cur_pwd = get_env_val(mns, "PWD");
		logic_pwd = resolve_logic_pwd(cur_pwd, target);
		if (logic_pwd)
		{
			set_env_val(&mns->env, "PWD", logic_pwd);
			free(logic_pwd);
		}
	}
}

static void	bi_cd_helper(t_shell *mns, char *oldpwd,
	char *target, char *expanded)
{
	set_env_val(&mns->env, "OLDPWD", oldpwd);
	update_pwd(mns, target);
	update_status(mns, 0);
	if (expanded != target)
		free(expanded);
}

int	bi_cd(t_shell *mns, t_cmd *cmd)
{
	char	*oldpwd;
	char	*target;
	char	**args;
	char	*expanded;

	args = cmd->cmd_arg;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(get_env_val(mns, "PWD"));
	if (!oldpwd)
		return (perror("getcwd"), 1);
	target = get_cd_target(mns, args);
	if (!target)
		return (update_status(mns, 1), free(oldpwd), 1);
	expanded = expand_titled(mns, target);
	if (chdir(expanded) != 0)
	{
		ft_printf_fd(2, "bash: cd: %s: No such file or directory\n", expanded);
		if (expanded != target)
			free(expanded);
		return (update_status(mns, 1), free(oldpwd), 1);
	}
	bi_cd_helper(mns, oldpwd, target, expanded);
	return (free(oldpwd), 0);
}
