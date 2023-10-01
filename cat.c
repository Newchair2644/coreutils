#include <stdio.h>
#include <string.h>
#include <errno.h>

void print_file(FILE *stream)
{
    // 10 KiB input, TODO this is obviously insufficient for bigger files
    char buf[10 * 1024];
    while (fgets(buf, sizeof(buf), stream)) {
        printf("%s", buf);
    }
}

int main(int argc, const char *argv[])
{
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            FILE *fname = fopen(argv[i], "r");
            print_file(fname);
            if (errno == 0) 
                fclose(fname);
            else
                perror(argv[0]);
        }
    } else {
        print_file(stdin);
    }
    return 0;
}
