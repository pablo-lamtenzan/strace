
#include <st_error.h>
#include <st_parse.h>

#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>

/* Parse '-p' | '--attach' argument */
static err_t parse_arg_attach(parse_t* const dest, const char** arg)
{
	bool st = SUCCESS;
	const pid_t pid = (pid_t)strtol(*arg, NULL, 10);
	
	if (kill(pid, 0) < 0)
	{
		if (errno == -ESRCH)
		{
			FERROR(EFMT_OPTATTACH, *(arg - 1), pid);
			st = E_ARGUMENT;
		}
		else
		{
			ERAISE_ERRNO("kill");
			st = E_SYSCALL;
		}
	}
	else
		dest->pid = pid;

	return st;
}

/* Parse '-P' | '--trace-path' argument */
static err_t parse_arg_path(parse_t* const dest, const char** arg)
{
	(void)dest;
	(void)arg;
	return SUCCESS;
}

static const struct
{
	const char* opt_short;
	const char* opt_long;
} opt_names[] = {
	{O_ATTACH_SHORT, O_ATTACH_LONG},
	{O_PATH_SHORT, O_PATH_LONG},
	{O_VERSION_SHORT, O_VERSION_LONG},
	{O_HELP_SHORT, O_HELP_LONG},
	{O_STATS_SHORT, O_STATS_LONG},
	{O_ERR_SHORT, O_ERROR_LONG},
	{O_NOERR_SHORT, O_NOERR_LONG}
};

typedef err_t (*const parse_arg_t)(parse_t* const, const char**);

static const parse_arg_t opt_handlers[] = {
	&parse_arg_attach,
	&parse_arg_path
};

/**
 * @brief Parse arguments from CLI.
 * 
 * Matches CLI input ( @p cli ) to options names, in case of a negative match an error is raised.
 * Some options take an argument, these options names are aligned with 'opt_handlers' handling functions.
 * In the case of an invalid argument, an error is raised, otherwise the argument is stored.
 * For all options, if matches succed a bit flag is set in the @p result::opts field.
 * The @p cli pointed pointer is incremented during the call.
 * 
 * @param result Where the result is stored.
 * @param cli A pointer to the CLI which from the result is built.
 */
err_t parse_cli_opts(parse_t* const result, const char** cli[])
{
	err_t		st = SUCCESS;
	uint64_t	cli_idx = 0;
	bool		found;

	while ((*cli)[cli_idx])
	{
		found = false;
		for (uint64_t opt_idx = 0 ; opt_idx < sizeof(opt_names) / sizeof(*opt_names) ; opt_idx++)
		{
			if (strcmp((*cli)[cli_idx], opt_names[opt_idx].opt_short) == 0
			|| strcmp((*cli)[cli_idx], opt_names[opt_idx].opt_long) == 0)
			{
				if (opt_idx < sizeof(opt_handlers) / sizeof(*opt_handlers))
				{
					if ((*cli)[++cli_idx] == NULL)
					{
						FERROR(EFMT_OPTARGNULL, (*cli)[cli_idx - 1]);
						st = E_ARGUMENT;
						goto error;
					}
					st = opt_handlers[opt_idx](result, &(*cli)[cli_idx]);
					if (st != SUCCESS)
						goto error;
				}
				found = true;
				result->opts |= (1 << opt_idx);
				break ;
			}
		}
		if (found == false)
		{
			FERROR(EFMT_OPTNOTFOUND, (*cli)[cli_idx]);
			st = E_ARGUMENT;
			goto error;
		}
		cli_idx++;
	}

	*cli += cli_idx;
error:
	return st;
}
