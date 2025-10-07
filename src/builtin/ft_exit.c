/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:28:46 by fgalvez-          #+#    #+#             */
/*   Updated: 2025/06/21 15:28:46 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Inc/minishell.h"

static int	parse_sign(const char *s, int *i_out, int *neg_out)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		neg = (s[i] == '-');
		i++;
	}
	*i_out = i;
	*neg_out = neg;
	return (1);
}

static int	would_overflow(unsigned long long acc, unsigned int d, int neg)
{
	unsigned long long	lim;

	if (neg)
		lim = LIM_NEG;
	else
		lim = LIM_POS;
	if (acc > lim / 10)
		return (1);
	if (acc == lim / 10 && (unsigned long long)d > lim % 10)
		return (1);
	return (0);
}

static int	parse_digits(const char *s, int i, int neg, unsigned long long *out)
{
	unsigned long long	acc;
	unsigned int		d;

	acc = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		d = (unsigned int)(s[i] - '0');
		if (would_overflow(acc, d, neg))
			return (0);
		acc = acc * 10 + d;
		i++;
	}
	*out = acc;
	return (1);
}

static int	parse_ll_with_overflow(const char *s, long long *out)
{
	int					i;
	int					neg;
	unsigned long long	acc;

	if (!s || !s[0])
		return (0);
	parse_sign(s, &i, &neg);
	if (!ft_isdigit((unsigned char)s[i]))
		return (0);
	if (!parse_digits(s, i, neg, &acc))
		return (0);
	if (neg)
		*out = -(long long)acc;
	else
		*out = (long long)acc;
	return (1);
}

int	ft_exit(t_cmd *cmd, t_mini *shell)
{
	long long	ll;

	if (cmd->ac == 1)
	{
		write(1, "exit\n", 5);
		exit(shell->last_status);
	}
	if (!parse_ll_with_overflow(cmd->av[1], &ll))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (cmd->ac == 2)
	{
		write(1, "exit\n", 5);
		exit(ft_atoi(cmd->av[1]));
	}
	if (cmd->ac > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	exit((int)(unsigned char)ll);
}
