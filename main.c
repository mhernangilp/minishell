#include "minishell.h"

int main(int argc, char **argv) 
{
	char *input;
	//(void) argv;
	if (argc != 1)
	{
		printf("Wrong parameters\n");
		exit(1);
	}
	while (1)
	{
		input = readline(ENTRADA_MS);
		// Verificar si se presionó Ctrl+D para salir del bucle
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(input);
		builtins(input);
		if (ft_strcmp(input, "ls") > 0)
		{
			execve("/bin/ls", argv, NULL);
			printf("Este comando que coñi es?\n");
		}
		free(input);
	}

	return (0);
}


void builtins(char *input)
{
	char *buffer;
	
	buffer = malloc (sizeof (size_t));
	if (ft_strcmp(input, "exit") > 0)
	{
		printf("exit\n");
		exit(1);
	}
	else if (ft_strcmp(input, "pwd") > 0)
	{
		if (getcwd(buffer, 1024) != NULL)
		{
			printf("%s\n", buffer);
			free(buffer);
		}
	}
}

int ft_strcmp(char *str, char *cmp)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != cmp[i])
			return (-1);
	}
	if (cmp[i])
		return (-1);
	return (i);
}