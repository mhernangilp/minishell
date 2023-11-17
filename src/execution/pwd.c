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
#include <linux/limits.h>
#include <unistd.h>

int	pwd()
{
	char	pwd[PATH_MAX];

	if(!getcwd(pwd, PATH_MAX))
		return (1);
	printf("%s\n", pwd);
	return (0);
}
