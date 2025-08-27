/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:42:21 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/08/20 10:42:21 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

/*
	*export_escaped_len: calcula la longitud necesaria para almacenar 'val'
	*escapando comillas dobles (") y barras invertidas (\) con un '\' extra.
	*Retorno: longitud total (sin contar el terminador nulo).
*/
static int	export_escaped_len(const char *val)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (val[i])
	{
		if (val[i] == '"' || val[i] == '\\')
			len++;
		len++;
		i++;
	}
	return (len);
}

/*
	*export_fill_escaped: copia 'val' a 'out' escapando " y \ con una barra
	*invertida adicional. Escribe el terminador nulo al final.
*/
static void	export_fill_escaped(const char *val, char *out)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (val[i])
	{
		if (val[i] == '"' || val[i] == '\\')
			out[k++] = '\\';
		out[k++] = val[i++];
	}
	out[k] = '\0';
}

/*
	*escape_export_value: devuelve una copia de 'val' con " y \ escapados.
	*Casos:
	*  - val == NULL → devuelve una copia de "".
	*Memoria: el llamador debe liberar la cadena resultante.
*/
static char	*escape_export_value(const char *val)
{
	char	*out;
	int		len;

	if (!val)
		return (ft_strdup(""));
	len = export_escaped_len(val);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	export_fill_escaped(val, out);
	return (out);
}

static void	print_export_entry(const char *entry)
{
	const char	*eq;
	char		*esc;
	int			keylen;

	eq = ft_strchr(entry, '=');
	if (!eq)
	{
		printf("declare -x %s\n", entry);
		return ;
	}
	keylen = (int)(eq - entry);
	esc = escape_export_value(eq + 1);
	if (!esc)
		return ;
	printf("declare -x %.*s=\"%s\"\n", keylen, entry, esc);
	free(esc);
}

void	print_export_no_args(char **env)
{
	char	**cp;
	int		i;

	cp = dup_env(env);
	if (!cp)
		return ;
	sort_strings(cp);
	i = 0;
	while (cp[i])
	{
		if (!is_underscore_entry(cp[i]))
			print_export_entry(cp[i]);
		i++;
	}
	ft_free_split(cp);
}
