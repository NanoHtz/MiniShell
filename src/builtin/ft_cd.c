/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:17:03 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/19 14:17:03 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

int	cd_change_dir(const char *target, char **old, char **now)
{
	*old = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(*old);
		*old = NULL;
		return (1);
	}
	*now = getcwd(NULL, 0);
	if (!*now)
	{
		perror("cd");
		free(*old);
		*old = NULL;
		return (1);
	}
	return (0);
}

int	env_normi(t_mini *shell, const char *name, const char *errmsg, char **out)
{
	*out = ms_getenv_dup(shell, name);
	if (!*out)
	{
		ft_putstr_fd(errmsg, 2);
		return (1);
	}
	return (0);
}

int	cd_get_target(t_cmd *cmd, t_mini *shell, char **out, int *print_new)
{
	*print_new = 0;
	*out = NULL;
	if (!cmd->av[1])
		return (env_normi(shell, "HOME", "cd: HOME not set\n", out));
	if (ft_strcmp(cmd->av[1], "-") == 0)
	{
		if (env_normi(shell, "OLDPWD", "cd: OLDPWD not set\n", out))
			return (1);
		*print_new = 1;
		return (0);
	}
	*out = ft_strdup(cmd->av[1]);
	if (!*out)
		return (1);
	return (0);
}

int	ft_cd(t_cmd *cmd, t_mini *shell)
{
	char	*target;
	char	*old;
	char	*now;
	int		print_new;

	if (cmd->ac > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (cd_get_target(cmd, shell, &target, &print_new) != 0)
		return (1);
	if (cd_change_dir(target, &old, &now) != 0)
	{
		free(target);
		return (1);
	}
	ms_setenv(shell, "OLDPWD", old);
	ms_setenv(shell, "PWD", now);
	if (print_new)
		ft_putendl_fd(now, 1);
	free(target);
	free(old);
	free(now);
	return (0);
}
