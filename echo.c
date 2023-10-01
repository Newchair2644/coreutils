#include <stdio.h>

int main(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i)
        printf("%s%c", argv[i], ((i + 1) == argc) ? '\n' : ' ');
    return 0;
}
