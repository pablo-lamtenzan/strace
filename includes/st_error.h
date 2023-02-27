
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

#define EFMT_OPTARGNULL PFX_ERROR "option '%s': missing arguments.\n"
#define EFMT_OPTNOTFOUND PFX_ERROR "no such option '%s'.\n"
#define EFMT_OPTATTACH PFX_ERROR "option '%s': no such process (pid: %d).\n"
