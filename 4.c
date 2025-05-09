#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 20

void display_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return;
    }

    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count == MAX_LINES) {
            printf("\nPress any key to continue...\n");
            getchar();
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s <файл1> <файл2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("--- Виведення файлу: %s ---\n", argv[i]);
        display_file(argv[i]);
    }

    return 0;
}
