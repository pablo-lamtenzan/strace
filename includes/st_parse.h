
#pragma once

#include "st_error.h"
#include <inttypes.h>
#include <sys/types.h>

/**
 * @struct parse_t
 * @brief Represent a parsed CLI.
 * 
 * @var parse_t::opts -> Bit flag options.
 * @var parse_t::pid -> Attached pid (-p | --attach)
 * @var parse_t::path -> Filter path (-P | --trace-path)
 */
typedef struct
{
    uint8_t		opts;
	struct
	{
		pid_t		pid;	
		const char*	path;
	};
} parse_t;

/* Display version */
#define O_VERSION_SHORT "-V"
#define O_VERSION_LONG "--version"

/* Display help */
#define O_HELP_SHORT "-h"
#define O_HELP_LONG "--help"

/* Display statistics */
#define O_STATS_SHORT "-c"
#define O_STATS_LONG "--count"

/* Attach to runnig process */
#define O_ATTACH_SHORT "-p"
#define O_ATTACH_LONG "--attach"

/* Filter by path */
#define O_PATH_SHORT "-P"
#define O_PATH_LONG "--trace-path"

/* Filter by failure */
#define O_ERR_SHORT "-z"
#define O_ERROR_LONG "--error"

/* Filter by success */
#define O_NOERR_SHORT "-Z"
#define O_NOERR_LONG "--no-error"

err_t	parse_cli_opts(parse_t* const result, const char** cli[]);
