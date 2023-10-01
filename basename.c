#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: missing operand\n", argv[0]);
        return 1;
    }
    const char *fname = argv[1];

    int dir_end = 0;
    for (int i = strlen(fname); i >= 0 && fname[i] != '/'; --i)
        dir_end = i;
    for (int i = dir_end; fname[i]; ++i)
        putchar(fname[i]);
    putchar('\n');

    return 0;
}
