#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void listFiles(const char *path, int showHidden, int longFormat) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!showHidden && entry->d_name[0] == '.') {
            continue; // Skip hidden files if -a option is not provided
        }

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &fileStat) == -1) {
            perror("stat");
            continue;
        }

        if (longFormat) {
            struct passwd *pwd = getpwuid(fileStat.st_uid);
            struct group *grp = getgrgid(fileStat.st_gid);
            char date[64];
            strftime(date, sizeof(date), "%b %d %H:%M", localtime(&fileStat.st_mtime));

            printf("%s %2d %s %s %5ld %s %s\n",
                   (S_ISDIR(fileStat.st_mode)) ? "d" : "-",
                   (int)fileStat.st_nlink,
                   (pwd != NULL) ? pwd->pw_name : "unknown",
                   (grp != NULL) ? grp->gr_name : "unknown",
                   (long)fileStat.st_size,
                   date,
                   entry->d_name);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int showHidden = 0;
    int longFormat = 0;
    const char *path = "."; // Default to current directory

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            showHidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            longFormat = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: ls [OPTION]... [FILE]...\n");
            printf("List information about the FILEs (the current directory by default).\n\n");
            printf("Options:\n");
            printf("  -a          do not ignore entries starting with .\n");
            printf("  -l          use a long listing format\n");
            printf("  --help      display this help and exit\n");
            return 0;
        } else {
            path = argv[i];
        }
    }

    listFiles(path, showHidden, longFormat);

    return 0;
}
