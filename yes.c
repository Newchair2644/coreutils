#include <stdio.h>

int main(int argc, const char *argv[])
{
    for (;;) {
        if (argc == 1) {
            puts("y");
        } else {
            for (int i = 1; i < argc; ++i)
                printf("%s%c", argv[i], (i == argc - 1) ? '\n' : ' ');
        }
    }

    return 0;
}
