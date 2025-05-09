#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];
    char answer;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.' && strstr(entry->d_name, ".c") != NULL) {
            snprintf(path, sizeof(path), "./%s", entry->d_name);
            if (stat(path, &statbuf) == 0) {
                printf("Знайдена програма: %s\n", entry->d_name);
                if ((statbuf.st_mode & S_IRUSR) == 0) {
                    printf("Дозвіл на читання відсутній. Надати доступ (y/n)? ");
                    scanf(" %c", &answer);
                    if (answer == 'y' || answer == 'Y') {
                        if (chmod(path, statbuf.st_mode | S_IRUSR) == 0) {
                            printf("Дозвіл на читання надано.\n");
                        } else {
                            perror("chmod");
                        }
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
