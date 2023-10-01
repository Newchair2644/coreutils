#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void help_msg() {
    puts("mkdir: missing operand\n\
Try mkdir --help for more information");
}

void mkdir_wrapper(char *dir, mode_t perms, bool v_flag) {
    mkdir(dir, 0775);
    if (v_flag)
        printf("mkdir: created directory '%s\n'", dir);
}

void mkdir_p(char *dir, mode_t perms, bool v_flag) {
    for (int i = 0; dir[i]; ++i) {
        if (dir[i] == '/' || dir[i + 1] == '\0') {
            dir[i + (dir[i + 1] == '\0')] = '\0';
            mkdir_wrapper(dir, perms, v_flag);
            dir[i] = '/';
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 || (strcmp(argv[1], "--help") == 0)) {
        help_msg();
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
        if (p_flag)
            mkdir_p(pargv[i], 0775, v_flag);
        else
            mkdir_wrapper(pargv[i], 0775, v_flag);

        if (errno != 0)
            perror(argv[0]);
    }
    return 0;
}
