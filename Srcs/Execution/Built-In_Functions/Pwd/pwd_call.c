/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:36:00 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/10 22:06:18 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_logic_pwd(const char *old, const char *target)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(old, "/");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, target);
	free(tmp);
	if (!joined)
		return (NULL);
	return (joined);
}

static char	*safe_getcwd_pwd(t_shell *mns)
{
	char	*cwd;
	char	*fallback;

	cwd = getcwd(NULL, 0);
	if (cwd)
		return (cwd);
	fallback = get_env_val(mns, "PWD");
	if (fallback)
		return (ft_strdup(fallback));
	return (NULL);
}

void	bi_pwd(t_shell *mns, t_cmd *cmd)
{
	char	*path;

	(void)cmd;
	path = safe_getcwd_pwd(mns);
	if (path)
	{
		ft_printf_fd(1, "%s\n", path);
		free(path);
		update_status(mns, 0);
	}
	else
	{
		perror("pwd");
		update_status(mns, 1);
	}
}
