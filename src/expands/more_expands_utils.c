/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_expands_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:23:05 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/25 18:23:05 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*look_for_expands: busca el primer '$' no protegido por comillas simples
	*y aplica la expansión de variable, reconstruyendo la cadena resultante.
	*Flujo:
	* 1) Si no hay '$' “válido”, devuelve una copia de 'str'.
	* 2) Extrae el valor y la longitud consumida (var_len) con extract_var().
	*    Si no hay valor expandible, devuelve una copia de 'str'.
	* 3) Construye: prefix = str[0 .. pos), suffix = pos + var_len.
	* 4) Devuelve join_free(join_free(prefix, value), suffix).
	*Retorno: nueva cadena asignada que el llamador debe liberar.
*/
char	*look_for_expands(char *str, char **cmd_env, t_mini *shell)
{
	char	*value;
	char	*prefix;
	char	*suffix;
	char	*pos;
	int		var_len;

	pos = find_unquoted_dollar(str);
	if (!pos)
		return (ft_strdup(str));
	value = extract_var(str, cmd_env, shell, &var_len);
	if (!value)
		return (ft_strdup(str));
	prefix = ft_substr(str, 0, pos - str);
	suffix = ft_strdup(pos + var_len);
	prefix = join_free(prefix, value);
	prefix = join_free(prefix, suffix);
	return (prefix);
}

t_cmd	*expand_commands(t_cmd *cmds, t_mini *shell)
{
	t_cmd	*head;
	int		i;
	char	*expanded;

	head = cmds;
	while (head)
	{
		i = 0;
		while (head->av && head->av[i])
		{
			if (needs_process(head->av[i]))
			{
				expanded = look_for_expands(head->av[i], head->cmd_env, shell);
				if (!expanded)
					expanded = ft_strdup("");
				free(head->av[i]);
				head->av[i] = expanded;
			}
			i++;
		}
		head = head->next;
	}
	return (cmds);
}

static ssize_t	handle_dollar_at(const char *p, char **out,
								char **cmd_env, t_mini *shell)
{
	ssize_t	n;

	if (p[1] == '?')
	{
		if (xcat_take(out, ft_itoa(shell->last_status)) < 0)
			return (-1);
		return (2);
	}
	n = append_name_at(out, p + 1, cmd_env, shell);
	if (n < 0)
		return (-1);
	return (1 + n);
}

static int	expand_line_hd_loop(const char *s, char **out,
								char **cmd_env, t_mini *shell)
{
	size_t	i;
	ssize_t	n;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$'
			&& is_valid_dollar_start((unsigned char)s[i + 1]))
		{
			n = handle_dollar_at(s + i, out, cmd_env, shell);
			if (n < 0)
				return (-1);
			i += (size_t)n;
		}
		else
		{
			if (xcat_take(out, ft_substr(s, i, 1)) < 0)
				return (-1);
			i++;
		}
	}
	return (1);
}

char	*expand_line_heredoc(const char *s, char **cmd_env, t_mini *shell)
{
	char	*out;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	if (expand_line_hd_loop(s, &out, cmd_env, shell) < 0)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
