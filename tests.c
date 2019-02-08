
#include "minishell.h"

void	t_print_parsed(t_token *token)
{
	while (token)
	{
		ft_putendl(token->s);
		token = token->next;
	}
}
