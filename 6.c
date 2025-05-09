#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void list_subdirectories(const char *dir_name) {
    struct dirent *entry;
    struct stat statbuf;
    char *dirs[1024];
    int dir_count = 0;
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("Перевірка каталогу: %s\n", dir_name);

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (stat(path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            dirs[dir_count++] = strdup(entry->d_name);
        }
    }

    closedir(dir);

    if (dir_count > 0) {
        qsort(dirs, dir_count, sizeof(char *), compare);

        for (int i = 0; i < dir_count; i++) {
            printf("%s\n", dirs[i]);
            free(dirs[i]);
        }
    } else {
        printf("Немає підкаталогів у каталозі %s\n", dir_name);
    }
}

int main() {
    list_subdirectories(".");
    return 0;
}
