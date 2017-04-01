#include <argp.h>
#include <stdlib.h>
#include <string.h>

#include "libbtd.h"

static struct argp_option options[] = {
	{0}
};

static error_t parse_list(int key, char *arg, struct argp_state *state)
{
	switch(key)
	{
		default:
			return ARGP_ERR_UNKNOWN;
	}

	(void)arg;
	(void)state;
	return 0;
}

static struct argp argp = {
	.options=options,
	.parser=parse_list,
	.args_doc="[opts]",
	.doc="List the items available",
	.children=NULL,
	.help_filter=NULL,
	.argp_domain=NULL};

void cmd_list(struct argp_state *state)
{
	int    argc = state->argc - state->next + 1;
	char** argv = &state->argv[state->next - 1];
	char*  argv0 =  argv[0];
	argv[0] = safe_strcat(3, state->name, " list");
	argp_parse(&argp, argc, argv, ARGP_IN_ORDER, &argc, NULL);
	free(argv[0]);
	argv[0] = argv0;
}
