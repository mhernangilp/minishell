#include "../minishell.h"
#include <string.h>

t_bridge	*test_execution()
{
	t_bridge	*bridge;

	bridge = malloc(sizeof(t_bridge));
	bridge -> infile = NULL;
	bridge -> here_doc = NULL;
	bridge -> outfile = NULL;
	bridge -> out_mode = 0;
	bridge -> ncommands = 2;
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
