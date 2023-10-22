#include "../../minishell.h"
#include <string.h>

t_bridge	*test_execution()
{
	t_bridge	*bridge;

	bridge = malloc(sizeof(t_bridge));
	bridge -> redirect = malloc(2 * sizeof(char *));
	bridge -> redirect[0] = malloc(4 * sizeof(char *));
	bridge -> redirect[0][0] = NULL;
	bridge -> redirect[0][1] = NULL;
	bridge -> redirect[0][2] = NULL;
	bridge -> redirect[0][3] = "-1";
	bridge -> redirect[1] = malloc(4 * sizeof(char *));
	bridge -> redirect[1][0] = NULL;
	bridge -> redirect[1][1] = NULL;
	bridge -> redirect[1][2] = NULL;
	bridge -> redirect[1][3] = "-1";
	bridge -> n_cmds = 2;
	bridge -> commands = malloc(2 * sizeof(char *));
	bridge -> commands[0] = malloc(3 * sizeof(char *));
	bridge -> commands[0][0] = strdup("ls");
	bridge -> commands[0][1] = strdup("-l");
	bridge -> commands[0][2] = NULL;
	bridge -> commands[1] = malloc(3 * sizeof(char *));
	bridge -> commands[1][0] = strdup("cat");
	bridge -> commands[1][1] = strdup("-e");
	bridge -> commands[1][2] = NULL;
	printf("Finished creating execution test struct\n");
	return (bridge);
}
