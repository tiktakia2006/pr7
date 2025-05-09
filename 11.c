#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int is_executable(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return st.st_mode & S_IXUSR;
}

int is_elf(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return 0;
    unsigned char buf[4];
    int n = read(fd, buf, 4);
    close(fd);
    return n == 4 && buf[0] == 0x7f && buf[1] == 'E' && buf[2] == 'L' && buf[3] == 'F';
}

int main() {
    DIR *d = opendir(".");
    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(d)) != NULL) {
        snprintf(path, sizeof(path), "%s", entry->d_name);
        if (is_executable(path) && !is_elf(path)) {
            printf("Аномальний виконуваний файл: %s\n", path);
        }
    }

    closedir(d);
    return 0;
}
