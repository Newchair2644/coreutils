#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: missing operand\n", argv[0]);
        return 1;
    }

    for (int j = 1; j < argc; ++j) {
        const char *fname = argv[j];
        int dir_end = 0;
        for (int i = strlen(fname); i >= 0; --i) {
            if (fname[i] == '/' && fname[i - 1] != '/') {
                dir_end = i;
                break;
            }
        }
        for (int k = 0; k < dir_end; ++k)
            putchar(fname[k]);
        putchar('\n');
    }
    return 0;
}
