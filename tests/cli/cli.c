#include <st_parse.h>

static void print_parse(parse_t* const target)
{
    fprintf(stdout, "OPTS: %hhu\nPID: %hu\nPATH: %s\n",
        target->opts, target->pid, target->path);
}

int main(int ac, const char* av[])
{
    (void)ac;
    ++av;

    parse_t res = {};

    err_t st = parse_cli_opts(&res, &av);
    print_parse(&res);
    
    return st;
}
