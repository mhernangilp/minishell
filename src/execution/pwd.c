/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhernang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:43:51 by mhernang          #+#    #+#             */
/*   Updated: 2023/11/12 20:52:54 by mhernang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	pwd(void)
{
	char	pwd[4096];

	printf("HOLA\n");
	if(!getcwd(pwd, sizeof(pwd)))
	{
		printf("Error\n");
		return (1);
	}
	printf("%s", pwd);
	return (0);
}
