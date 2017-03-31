#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cmd.h"

int verbosity = 0;

const char *argp_program_version = "btdc 0.1";
const char *argp_program_bug_address = "<mart@martlubbers.net>";

static char doc[] = "btdc -- A btd client";
static char args_doc[] = "[global opts] [cmd [cmd opts]]";

static struct argp_option options[] = {
	{"verbose",'v', 0, 0, "Increase verbosity", 0},
	{"quiet",'q', 0, 0, "Decrease verbosity", 0},
	{0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	switch(key)
	{
		case 'v':
			verbosity = verbosity == 3 ? 3 : verbosity+1;
			break;
		case 'q':
			verbosity = verbosity == 0 ? 0 : verbosity-1;
			break;
		case ARGP_KEY_ARG:
			if(strcasecmp("list", arg) == 0 || strcasecmp("ls", arg)) {
				cmd_list(state);
			} else {
				argp_error(state, "%s is not a valid command", arg);
			}
			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = {
	.options=options,
	.parser=parse_opt,
	.args_doc=args_doc,
	.doc=doc,
	.children=NULL,
	.help_filter=NULL,
	.argp_domain=NULL};

int main(int argc, char **argv){
	argp_parse(&argp, argc, argv, 0, 0, NULL);
	return EXIT_SUCCESS;
}
