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

/*
	*cd_change_dir: guarda el cwd actual en *old, cambia a 'target' y guarda
	*el nuevo cwd en *now. En fallo imprime perror("cd") y limpia *old.
	*Retorno: 0 en éxito; 1 en error.
*/
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

/*
	*cd_getenv_required: obtiene una variable de entorno duplicada.
	*Si no existe, imprime el mensaje de error indicado y retorna 1.
	*Retorno: 0 en éxito; 1 si la variable no está definida o falla la reserva.

*/
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

/*
	*cd_get_target: determina el directorio objetivo para 'cd'.
	*Casos:
	*  - Sin argumento → $HOME (error si no está).
	*  - "-" → $OLDPWD y marcar print_new=1 (error si no está).
	*  - Otro → duplicar literal.
	*Retorno: 0 en éxito; 1 en error.
*/
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

/*
	*ft_cd: implementa el builtin 'cd' con actualización de PWD/OLDPWD.
	*Flujo:
	* 1) Valida nº de argumentos.
	* 2) Obtiene el destino (HOME/OLDPWD/literal)
	* y si debe imprimirse el nuevo cwd.
	* 3) Cambia de directorio y obtiene cwd previo/actual.
	* 4) Actualiza OLDPWD y PWD; si procede, imprime el nuevo cwd.
	*Retorno: 0 en éxito; 1 en error.
*/
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
