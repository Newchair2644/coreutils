#include <stdio.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        FILE *file = fopen(argv[i], "w");
        if (errno == 0)
            fclose(file);
        else
            perror(argv[0]);
    }
    return 0;
}
