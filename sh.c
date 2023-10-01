#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    char input[MAX_INPUT_SIZE];
    char current_directory[MAX_INPUT_SIZE];

    while (1) {
        getcwd(current_directory, sizeof(current_directory));
        printf("$:%s> ", current_directory);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove trailing newline character from fgets
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strncmp(input, "cd ", 3) == 0) {
            char *dir = input + 3;
            if (chdir(dir) != 0) {
                perror("chdir");
            }
        } else {
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(1);
            } else if (pid == 0) {
                char *args[MAX_INPUT_SIZE];
                char *token = strtok(input, " ");
                int i = 0;

                while (token != NULL) {
                    args[i] = token;
                    token = strtok(NULL, " ");
                    i++;
                }

                args[i] = NULL; // Null-terminate the argument list
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            } else {
                int status;
                waitpid(pid, &status, 0);

                if (!WIFEXITED(status)) {
                    perror("waitpid");
                }
            }
        }
    }

    return 0;
}
