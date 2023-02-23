
#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef enum
{
	SUCCESS,
	E_SYSCALL,
	E_ARGUMENT,
} err_t;

#ifndef __progname
# define __progname "strace"
#endif

#define ERROR(msg) fprintf(stderr, msg)
#define FERROR(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

#define PFX_ERROR __progname ": error: "
#define PFX_WARNING __progname ": warning: "

#define ERAISE_ERRNO(name) \
	FERROR( \
		PFX_ERROR "%s: %s (errno: %d).\n", \
		name, strerror(errno), errno \
	)
