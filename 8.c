#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char filename[256];
    char choice;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Не вдалося відкрити каталог");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("Знайдений файл: %s\n", entry->d_name);
            printf("Чи хочете видалити цей файл? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                if (remove(entry->d_name) == 0) {
                    printf("Файл %s успішно видалено.\n", entry->d_name);
                } else {
                    perror("Помилка при видаленні файлу");
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
