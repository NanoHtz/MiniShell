/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:33:20 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/23 13:33:20 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	* get_env_value: Se hace por jerarquias
	* ha de buscar desde el ambito mas local al mas global.
	* entorno del comando, de la minishell y de bash
	* el primero que encuentre en ese orden lo devuelve.
	* por si se llaman igual en distintos ambitos.
*/
char	*get_env_value(char *key, char **cmd_env, char **own_env, char **envp)
{
	char	*val;

	if (!key)
		return (ft_strdup(""));
	val = expand(key, cmd_env);
	if (val)
		return (val);
	val = expand(key, own_env);
	if (val)
		return (val);
	val = expand(key, envp);
	if (val)
		return (val);
	return (ft_strdup(""));
}

/*
	*handle_qmark: gestiona la expansión especial "$?".
	*Acción: convierte last_status a cadena y fija *var_len=2.
	*Retorno: cadena asignada con el valor; NULL en error.
*/
char	*handle_qmark(t_mini *shell, int *var_len)
{
	char	*value;

	value = ft_itoa(shell->last_status);
	if (!value)
		return (NULL);
	*var_len = 2;
	return (value);
}

/*
	*extract_named_var: extrae y busca el valor de una variable con nombre.
	*Entrada: 'var' apunta al '$', 'j' es la longitud total consumida.
	*Acción: toma el nombre, busca en entornos y fija *var_len=j.
	*Retorno: valor asignado (o NULL si no existe o hay error de memoria).
*/
char	*extract_named_var(const char *var, int j,
				t_mini *shell, int *var_len)
{
	char	*varname;
	char	*value;

	varname = ft_substr(var, 1, j - 1);
	if (!varname)
		return (NULL);
	value = get_env_value(varname, NULL, shell->own_env, shell->env);
	free(varname);
	*var_len = j;
	return (value);
}

/*
	*scan_var_name: dada una cadena que empieza en '$', devuelve la longitud
	*total consumida por el identificador de variable (incluye el '$' inicial).
	*Formato admitido del nombre: [A-Za-z0-9_]* tras el primer carácter.
*/
int	scan_var_name(const char *var)
{
	int	j;

	j = 1;
	while (var[j] && (ft_isalnum((unsigned char)var[j]) || var[j] == '_'))
		j++;
	return (j);
}

/*
	*extract_var: obtiene el valor expandido desde el
	* primer '$' no entrecomillado.
	*Casos:
	*  - "$?" → handle_qmark().
	*  - "$NAME" con nombre válido → extract_named_var().
	*  - En otro caso → NULL (no hay expansión).
	*Nota: *var_len se fija con los caracteres consumidos (incluye '$').
*/
char	*extract_var(char *str, char **cmd_env, t_mini *shell, int *var_len)
{
	char	*var;
	int		j;

	(void)cmd_env;
	var = find_unquoted_dollar(str);
	if (!var)
		return (NULL);
	if (var[1] == '?')
		return (handle_qmark(shell, var_len));
	if (!is_valid_dollar_start(var[1]))
		return (NULL);
	j = scan_var_name(var);
	return (extract_named_var(var, j, shell, var_len));
}
