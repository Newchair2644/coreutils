#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define PROG_NAME "mkdir"
#define HELP_MSG "mkdir: missing operand\n\
Try mkdir --help for more information"


static void verbose(bool v_flag, const char *dir) {
    if (v_flag && !errno)
        printf("%s: created directory '%s'\n", PROG_NAME, dir);
}

void mkdir_p(char *dir, mode_t perms, bool v_flag) {
    for (int i = 0; dir[i]; ++i) {
        if (dir[i] == '/' || dir[i + 1] == '\0') {
            dir[i + (dir[i + 1] == '\0')] = '\0';
            mkdir(dir, perms);
            verbose(v_flag, dir);
            dir[i] = '/';
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 || (strcmp(argv[1], "--help") == 0)) {
        puts(HELP_MSG);
        return 1;
    }

    char **pargv = argv + 1;
    bool p_flag = false, v_flag = false;
    for ( ; *pargv && **pargv == '-'; ++pargv) {
        for ( ; **pargv != '\0'; ++(*pargv)) {
            if (**pargv == 'p')
                p_flag = true;
            if (**pargv == 'v')
                v_flag = true;

        }
    }

    for (int i = 0; pargv[i]; ++i) {
        if (p_flag) {
            mkdir_p(pargv[i], 0775, v_flag);
        } else {
            mkdir(pargv[i], 0775);
            verbose(v_flag, pargv[i]);
        }

        if (errno)
            perror(PROG_NAME);
    }
    return 0;
}
