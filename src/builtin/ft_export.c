/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:28:12 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/22 13:28:12 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* remove_entry: elimina una variable.
*/
void	remove_entry(char ***env, int index)
{
	char	**new_env;

	if (!env || !*env)
		return ;
	new_env = copy_env_without_index(*env, index);
	if (!new_env)
		return ;
	free(*env);
	*env = new_env;
}

/*
	* export_keyval: añade una variable a un entorno
	* lo borra del otro.
*/
static void	export_keyval(char *arg, t_mini *shell)
{
	char	*key;
	int		idx;

	key = get_key(arg);
	if (!key)
		return ;
	idx = find_key_index(shell->own_env, key);
	if (idx != -1)
		remove_entry(&shell->own_env, idx);
	idx = find_key_index(shell->env, key);
	if (idx != -1)
		replace_entry(shell->env, idx, arg);
	else
		append_entry(&shell->env, arg);
	free(key);
}

/*
	* export_variable: añade una variable a un entorno
	* lo borra del otro.
*/
static void	export_variable(char *arg, t_mini *shell)
{
	int		idx;
	char	*kv;

	idx = find_key_index(shell->own_env, arg);
	if (idx != -1)
	{
		append_entry(&shell->env, shell->own_env[idx]);
		remove_entry(&shell->own_env, idx);
		return ;
	}
	if (find_key_index(shell->env, arg) == -1)
	{
		kv = ft_strjoin(arg, "=");
		if (!kv)
			return ;
		append_entry(&shell->env, kv);
		free(kv);
	}
}

/*
	*process_export_arg: procesa un argumento de 'export'.
	*Comportamiento:
	*  - Si contiene '=', valida la clave (get_key + ms_is_valid_ident).
	*    En caso válido, llama a export_keyval(arg, shell).
	*    En caso inválido, imprime ms_export_err_ident y marca *had_err=1.
	*  - Si no contiene '=', valida el identificador completo; si es válido,
	*    llama a export_variable(arg, shell); si no,
	* reporta error y marca *had_err.
	*Memoria:
	*  - Libera 'key' devuelto por get_key en todos los caminos donde proceda.
*/
static void	process_export_arg(char *arg, t_mini *shell, int *had_err)
{
	char	*key;

	if (ft_strchr(arg, '='))
	{
		key = get_key(arg);
		if (!key || !ms_is_valid_ident(key))
		{
			ms_export_err_ident(arg);
			*had_err = 1;
			if (key)
				free(key);
			return ;
		}
		free(key);
		export_keyval(arg, shell);
		return ;
	}
	if (!ms_is_valid_ident(arg))
	{
		ms_export_err_ident(arg);
		*had_err = 1;
		return ;
	}
	export_variable(arg, shell);
}

/*
	*ft_export: implementa el builtin 'export'.
	*Casos:
	*  - Sin argumentos (o args[1] NULL): lista el entorno exportable.
	*  - Con argumentos: procesa cada 'clave' o 'clave=valor' validando
	*    identificadores y reportando errores de forma acumulada.
	*Retorno:
	*  - 0 si todos los argumentos fueron válidos o no había argumentos.
	*  - 1 si al menos un argumento fue inválido.
*/
int	ft_export(char **args, t_mini *shell)
{
	int	i;
	int	had_err;

	i = 1;
	had_err = 0;
	if (!args || !args[1])
	{
		print_export_no_args(shell->env);
		return (0);
	}
	while (args[i])
	{
		process_export_arg(args[i], shell, &had_err);
		i++;
	}
	if (had_err)
		return (1);
	return (0);
}
