#include <argp.h>

void cmd_list(struct argp_state *state)
{
	int    argc = state->argc - state->next + 1;
	char** argv = &state->argv[state->next - 1];
	char*  argv0 =  argv[0];
	(void)argc;
	(void)argv;
	(void)argv0;
	printf("list: argv0: %s\n", argv0);
}
