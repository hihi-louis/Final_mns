/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caonguye <caonguye@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:44:37 by tripham           #+#    #+#             */
/*   Updated: 2025/04/19 20:03:36 by caonguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**found_envp_path(char **envp)
{
	char	**cwd;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp ||!ft_strcmp(*envp, "PATH="))
	{
		cwd = (char **)ft_calloc(2, sizeof(char *));
		if (!cwd)
			return (NULL);
		cwd[0] = getcwd(NULL, 0);
		if (!cwd[0])
		{
			ft_free_2d((void **)cwd);
			return (NULL);
		}
		return (cwd);
	}
	return (ft_split(*envp + 5, ':'));
}

static char	*join_command_path(char *envp_path, char *command)
{
	char	*command_directories;
	char	*command_path;

	command_directories = ft_strjoin(envp_path, "/");
	if (!command_directories)
		return (NULL);
	command_path = ft_strjoin(command_directories, command);
	if (!command_path)
	{
		free(command_directories);
		return (NULL);
	}
	free(command_directories);
	return (command_path);
}

static char	*get_command_path(char **envp_paths, char *command)
{
	char	*command_path;

	while (*envp_paths)
	{
		command_path = join_command_path(*(envp_paths)++, command);
		if (!command_path || access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

static int	cmd_check(t_shell *mns, char *cmd)
{
	struct stat	sb;

	if (!cmd || !cmd[0] || !ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (check_error (mns, cmd));
	else if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			exec_error(mns, NULL, cmd, "Is a directory");
		if (access(cmd, F_OK) != 0)
			return (check_error (mns, cmd));
		if (access(cmd, X_OK) != 0)
			exec_error(mns, NULL, cmd, "Permission denied");
	}
	return (EXIT_SUCCESS);
}

char	*found_command_path(t_shell *mns, char *cmd)
{
	char	**envp_paths;
	char	*command_path;

	if (cmd_check(mns, cmd) == EXIT_FAILURE)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	envp_paths = found_envp_path(mns->env);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, cmd);
	ft_free_3d((void ***)&envp_paths);
	if (!command_path)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd);
	else if (access(command_path, X_OK) != 0)
		exec_error(mns, NULL, cmd, "Permission denied");
	return (command_path);
}
