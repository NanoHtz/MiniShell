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
	*join_free: concatena 'a' y 'b' con ft_strjoin y libera ambas entradas.
	*Retorno: nueva cadena resultante; NULL si ft_strjoin falla.
	*Nota: siempre libera 'a' y 'b', incluso si la concatenación falla.
*/
char	*join_free(char *a, char *b)
{
	char	*res;

	res = ft_strjoin(a, b);
	free(a);
	free(b);
	return (res);
}

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

/*
	* expand_commands: Recorre la lista de comandos
	* si encuentra la llamada a una variable $
	* busca su valor y lo sustituye liberando el anterior av
*/
int	needs_process(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '$' || *s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
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

// Devuelve una nueva cadena con $VAR y $? expandidos para here-doc.
// Reglas: ignora comillas; usa cmd_env -> own_env -> env del shell.
// helper seguro: concatena y libera solo el left
static char	*cat_free_left(char *left, const char *right)
{
	char	*cat;

	cat = ft_strjoin(left, right);
	free(left);
	return (cat);
}

char	*expand_line_heredoc(const char *s, char **cmd_env, t_mini *shell)
{
	size_t 	i;
	size_t	j;
	char	*out;
	char	*tmp;
	char	*key;
	char	*val;

	out = ft_strdup("");
	i = 0;
	if (!out)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && is_valid_dollar_start((unsigned char)s[i + 1]))
		{
			if (s[i + 1] == '?')
			{
				tmp = ft_itoa(shell->last_status);
				if (!tmp)
				{
					free(out);
					return (NULL);
				}
                out = cat_free_left(out, tmp);
                free(tmp);
				if (!out)
					return (NULL);
				i += 2;
				continue ;
			}
			j = i + 1;
			while (s[j] && (ft_isalnum((unsigned char)s[j]) || s[j] == '_'))
				j++;
            key = ft_substr(s + i + 1, 0, j - (i + 1));
			if (!key)
			{
				free(out);
				return (NULL);
			}
			val = get_env_value(key, cmd_env, shell->own_env, shell->env);
			free(key);
			if (!val)
			{
				free(out);
				return (NULL);
			}
			out = cat_free_left(out, val);
			free(val);
			if (!out)
				return (NULL);
			i = j;
			continue ;
		}
		tmp = ft_substr(s, i, 1);
		if (!tmp)
		{
			free(out);
			return (NULL);
		}
        out = cat_free_left(out, tmp);
        free(tmp);
        if (!out)
			return (NULL);
		i++;
	}
	return (out);
}
