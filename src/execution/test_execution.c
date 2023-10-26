#include "../../minishell.h"
#include <stdlib.h>
#include <string.h>

// "ls -l | cat -e"
t_bridge	*test_execution()
{
	t_bridge	*bridge;

	//Initialize bridge
	bridge = (t_bridge *)malloc(sizeof(t_bridge));
	//Initialize redirect
	bridge -> redirect = (t_cmdred *)malloc(2 * sizeof(t_cmdred));
	bridge -> redirect[0].inred = NULL;
	bridge -> redirect[0].outred = NULL;
	bridge -> redirect[1].inred = NULL;
	bridge -> redirect[1].outred = NULL;
	//Initialize commands
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

// "< in.txt cat -e | cat -e > out.txt"
t_bridge	*test_execution2()
{
	t_bridge	*bridge;

	//Initialize bridge
	bridge = (t_bridge *)malloc(sizeof(t_bridge));
	//Initialize redirect
	bridge -> redirect = (t_cmdred *)malloc(2 * sizeof(t_cmdred));
	//Initialize first command redirects
	bridge -> redirect[0].inred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[0].inred -> num = 1;
	bridge -> redirect[0].inred -> file = (char **)malloc(1 * sizeof(char *));
	bridge -> redirect[0].inred -> file[0] = strdup("in.txt");
	bridge -> redirect[0].inred -> type = (int *)malloc(1 * sizeof(int));
	bridge -> redirect[0].inred -> type[0] = NORMAL;
	bridge -> redirect[0].outred = NULL;
	//Initialize second command redirects
	bridge -> redirect[1].inred = NULL;
	bridge -> redirect[1].outred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[1].outred -> num = 1;
	bridge -> redirect[1].outred -> file = (char **)malloc(1 * sizeof(char *));
	bridge -> redirect[1].outred -> file[0] = strdup("out.txt");
	bridge -> redirect[1].outred -> type = (int *)malloc(1 * sizeof(int));
	bridge -> redirect[1].outred -> type[0] = NORMAL;
	//Initialize commands
	bridge -> n_cmds = 2;
	bridge -> commands = malloc(2 * sizeof(char *));
	bridge -> commands[0] = malloc(3 * sizeof(char *));
	bridge -> commands[0][0] = strdup("cat");
	bridge -> commands[0][1] = strdup("-e");
	bridge -> commands[0][2] = NULL;
	bridge -> commands[1] = malloc(3 * sizeof(char *));
	bridge -> commands[1][0] = strdup("cat");
	bridge -> commands[1][1] = strdup("-e");
	bridge -> commands[1][2] = NULL;
	printf("Finished creating execution test struct\n");
	return (bridge);
}

// "< uno.txt < dos.txt cat -e > out.txt | cat -e
t_bridge	*test_execution3()
{
	t_bridge	*bridge;

	//Initialize bridge
	bridge = (t_bridge *)malloc(sizeof(t_bridge));
	//Initialize redirect
	bridge -> redirect = (t_cmdred *)malloc(2 * sizeof(t_cmdred));
	//Initialize first command redirects
	bridge -> redirect[0].inred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[0].inred -> num = 2;
	bridge -> redirect[0].inred -> file = (char **)malloc(2 * sizeof(char *));
	bridge -> redirect[0].inred -> file[0] = strdup("uno.txt");
	bridge -> redirect[0].inred -> file[1] = strdup("dos.txt");
	bridge -> redirect[0].inred -> type = (int *)malloc(2 * sizeof(int));
	bridge -> redirect[0].inred -> type[0] = NORMAL;
	bridge -> redirect[0].inred -> type[1] = NORMAL;
	bridge -> redirect[0].outred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[0].outred -> num = 1;
	bridge -> redirect[0].outred -> file = (char **)malloc(1 * sizeof(char *));
	bridge -> redirect[0].outred -> file[0] = strdup("out.txt");
	bridge -> redirect[0].outred -> type = (int *)malloc(1 * sizeof(int));
	bridge -> redirect[0].outred -> type[0] = NORMAL;
	//Initialize second command redirects
	bridge -> redirect[1].inred = NULL;
	bridge -> redirect[1].outred = NULL;
	//Initialize commands
	bridge -> n_cmds = 2;
	bridge -> commands = malloc(2 * sizeof(char *));
	bridge -> commands[0] = malloc(3 * sizeof(char *));
	bridge -> commands[0][0] = strdup("cat");
	bridge -> commands[0][1] = strdup("-e");
	bridge -> commands[0][2] = NULL;
	bridge -> commands[1] = malloc(3 * sizeof(char *));
	bridge -> commands[1][0] = strdup("cat");
	bridge -> commands[1][1] = strdup("-e");
	bridge -> commands[1][2] = NULL;
	printf("Finished creating execution test struct\n");
	return (bridge);
}

// "< uno.txt << EOF cat -e >> out.txt | < dos.txt cat -e
t_bridge	*test_execution4()
{
	t_bridge	*bridge;

	//Initialize bridge
	bridge = (t_bridge *)malloc(sizeof(t_bridge));
	//Initialize redirect
	bridge -> redirect = (t_cmdred *)malloc(2 * sizeof(t_cmdred));
	//Initialize first command redirects
	bridge -> redirect[0].inred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[0].inred -> num = 2;
	bridge -> redirect[0].inred -> file = (char **)malloc(2 * sizeof(char *));
	bridge -> redirect[0].inred -> file[0] = strdup("uno.txt");
	bridge -> redirect[0].inred -> file[1] = strdup("EOF");
	bridge -> redirect[0].inred -> type = (int *)malloc(2 * sizeof(int));
	bridge -> redirect[0].inred -> type[0] = NORMAL;
	bridge -> redirect[0].inred -> type[1] = HEREDOC;
	bridge -> redirect[0].outred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[0].outred -> num = 1;
	bridge -> redirect[0].outred -> file = (char **)malloc(1 * sizeof(char *));
	bridge -> redirect[0].outred -> file[0] = strdup("out.txt");
	bridge -> redirect[0].outred -> type = (int *)malloc(1 * sizeof(int));
	bridge -> redirect[0].outred -> type[0] = APPEND;
	//Initialize second command redirects
	bridge -> redirect[1].inred = (t_red *)malloc(sizeof(t_red));
	bridge -> redirect[1].inred -> num = 0;
	bridge -> redirect[1].inred -> file = (char **)malloc(1 * sizeof(char *));
	bridge -> redirect[1].inred -> file[0] = strdup("dos.txt");
	bridge -> redirect[1].inred -> type = (int *)malloc(1 * sizeof(int));
	bridge -> redirect[1].inred -> type[0] = NORMAL;
	bridge -> redirect[1].outred = NULL;
	//Initialize commands
	bridge -> n_cmds = 2;
	bridge -> commands = malloc(2 * sizeof(char *));
	bridge -> commands[0] = malloc(3 * sizeof(char *));
	bridge -> commands[0][0] = strdup("cat");
	bridge -> commands[0][1] = strdup("-e");
	bridge -> commands[0][2] = NULL;
	bridge -> commands[1] = malloc(3 * sizeof(char *));
	bridge -> commands[1][0] = strdup("cat");
	bridge -> commands[1][1] = strdup("-e");
	bridge -> commands[1][2] = NULL;
	printf("Finished creating execution test struct\n");
	return (bridge);
}
