#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "libbtd.h"
#include "cmd_list.h"

extern char *version;

struct addrinfo *addr;

const char *argp_program_version = "btdc 0.1";
const char *argp_program_bug_address = "<mart@martlubbers.net>";

static char doc[] = "btdc -- A btd client";
static char args_doc[] = "[global opts] [cmd [cmd opts]]";

static struct argp_option options[] = {
	{"host",'h', "ADDRESS", 0, "Increase verbosity", 0},
	{"verbose",'v', 0, 0, "Increase verbosity", 0},
	{"quiet",'q', 0, 0, "Decrease verbosity", 0},
	{0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	switch(key)
	{
		case 'h':
	//		btd_free_addrinfo(addr);
			addr = btd_get_addrinfo(arg);
			break;
		case 'v':
			btd_incr_log();
			break;
		case 'q':
			btd_decr_log();
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
	FILE *fd;

	char *dp = btd_get_data_path();
	char *sp = safe_strcat(2, dp, "/btd.socket");
	addr = btd_get_addrinfo(sp);
	safe_free(2, sp, dp);

	btd_init_log();
	argp_parse(&argp, argc, argv, ARGP_IN_ORDER, 0, NULL);

	if ((fd = btd_connect(addr)) == NULL){
		return EXIT_FAILURE;
	}
	btd_log(1, "Connected to a btd version %s\n", version);

	free(btd_bye(fd));
	safe_fclose(fd);

	return EXIT_SUCCESS;
}
