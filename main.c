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
		// Leer una línea de entrada utilizando readline
		input = readline("Ingrese un comando: ");

		// Verificar si se presionó Ctrl+D para salir del bucle
		if (input == NULL)
		{
			printf("\nSaliendo...\n");
			break;
		}
		add_history(input);
		printf("Has ingresado: %s\n", input);
		if (ft_strcmp(input, "ls") > 0)
		{
			execve("/bin/ls", argv, NULL);
			printf("Este comando que coñi es?\n");
		}
		free(input);
	}

	return (0);
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
	return (i);
}
