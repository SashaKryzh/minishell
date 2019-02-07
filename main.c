/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:29:21 by okryzhan          #+#    #+#             */
/*   Updated: 2019/02/07 15:29:21 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_op(t_token *token)
{
	t_token *tmp;

	tmp = token->next;
	while (tmp)
	{
		ft_putstr(tmp->s);
		tmp = tmp->next;
		if (tmp)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	exit_op(t_token *token)
{
	if (token->next)
		exit(ft_atoi(token->next->s));
	exit(0);
}

int		token_len(char **s)
{
	int		len;

	len = 0;
	while ((*s)[len])
	{
		if (ft_isspace((*s)[len]))
			return (len);
		len++;
	}
	return (len);
}

void	add_token(t_token **token, char *s, int len)
{
	t_token *new;
	t_token *tmp;

	new = (t_token *)ft_memalloc(sizeof(t_token));
	new->s = ft_strndup(s, len);
	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	t_print_parsed(t_token *token)
{
	while (token)
	{
		ft_putendl(token->s);
		token = token->next;
	}
}

void	execute_op(t_token *token)
{
	if (ft_strequ("exit", token->s))
		exit_op(token);
	if (ft_strequ("echo", token->s))
		echo_op(token);
}

void	get_token(char *l)
{
	t_token	*token;
	int		len;

	token = NULL;
	while (*l)
	{
		while (ft_isspace(*l))
			l++;
		len = token_len(&l);
		add_token(&token, l, len);
		l += len;
	}
	// t_print_parsed(token); //
	execute_op(token);
}

void	loop(void)
{
	char	buf[1025];
	int		i;

	i = 0;
	while (read(0, &buf[i], 1))
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	buf[i] = '\0';
	get_token((char *)&buf);
}

int		main(void)
{
	while (1)
	{
		ft_putstr("$> ");
		loop();
	}
	return (0);
}
