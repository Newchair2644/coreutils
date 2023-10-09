#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void print_file(FILE *stream, long file_size)
{

    char *buf = malloc(file_size);
    while (fgets(buf, sizeof(buf), stream))
        printf("%s", buf);

    free(buf);
}

int main(int argc, const char *argv[])
{
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            // calculate file size in bytes to be dynamically allocated
            FILE *fname = fopen(argv[i], "r");
            fseek(fname, 0, SEEK_END);
            long file_size = ftell(fname);
            fseek(fname, 0, SEEK_SET);

            print_file(fname, file_size);
            if (errno == 0) 
                fclose(fname);
            else
                perror(argv[0]);
        }
    } else {
        // 10 KiB for stdin
        print_file(stdin, 1024 * 10);
    }
    return 0;
}
