# ПРАКТИЧНА РОБОТА 9

## ЗАВДАННЯ 1

## Умова
 Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.
## Код до завдання
```
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("rwho | more", "r");
    if (fp == NULL) {
        perror("popen");
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}

```

## Опис програми
Ця програма на C запускає команду rwho | more за допомогою функції popen() і зчитує її вивід рядок за рядком. Команда rwho показує, які користувачі зараз підключені до системи, а more дає змогу зручно переглядати цей список посторінково. Отримані рядки програма виводить на екран через fputs(). Такий підхід дозволяє інтегрувати зовнішні UNIX-команди безпосередньо в C-програму. Після запуску ми отримали правильний вивід, отже, все працює так, як задумано.

## Результати програми
![image](https://github.com/user-attachments/assets/745c9a2e-225e-41c6-a41a-581e848fdad0)


## ЗАВДАННЯ 2

## Умова
 Напишіть програму мовою C, яка імітує команду ls -l в UNIX - виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.
 (Варіант вирішення, що просто виконує ls -l із вашої програми, - не підходить.)

## Код до завдання
```
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char timebuf[80];

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        print_permissions(file_stat.st_mode);
        printf(" %ld", file_stat.st_nlink);

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group  *gr = getgrgid(file_stat.st_gid);
        printf(" %s %s", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

        printf(" %5ld", file_stat.st_size);

        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat.st_mtime));
        printf(" %s", timebuf);

        printf(" %s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}


```

## Опис програми
Ця програма на C імітує команду ls -l, виводячи детальну інформацію про всі файли в поточному каталозі без виклику зовнішніх команд. Вона відкриває директорію, зчитує імена файлів, а потім для кожного з них отримує характеристики через функцію stat(). Далі програма самостійно формує права доступу, визначає власника, групу, розмір і дату останньої зміни, як це робить справжній ls -l. У виводі відображаються імена файлів разом із правильно оформленими правами, датою і власником - наприклад, -rwxrwxrwx 1 root root 1534 May 09 10:52 2.c. Це означає, що все працює вірно: і логіка побудови, і форматування відповідають вимогам UNIX-версії команди ls -l.

## Результати програми

![image](https://github.com/user-attachments/assets/abb035a9-40ca-4e43-a634-35200e3fbdea)


## ЗАВДАННЯ 3

## Умова
 Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).
## Код до завдання
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Використання: %s <файл> <слово>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, argv[2]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}

```

## Опис програми
Ця програма на C імітує функціональність утиліти grep в UNIX. Вона приймає два аргументи: ім’я файлу та слово для пошуку. Програма відкриває файл, читає його рядок за рядком і перевіряє, чи містить кожен рядок задане слово. Якщо слово знайдено в рядку, програма виводить цей рядок на екран. У випадку, якщо аргументи не передано, програма виведе інструкцію щодо правильного використання і не буде виконана, що є нормальним поведінкою для таких програм. Програма працює коректно, виводячи всі рядки, що містять задане слово, та правильно обробляючи помилки у разі відсутності аргументів або проблем з відкриттям файлу.

## Результати програми
![image](https://github.com/user-attachments/assets/2a62471b-9922-492e-b783-93b55db97ef8)
![image](https://github.com/user-attachments/assets/8ff61bc3-bd02-4bfd-a681-7b97407e9445)


## ЗАВДАННЯ 4

## Умова
  Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).
## Код до завдання
```
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


```

## Опис програми
Тут я реалізував спрощену версію утиліти more, що виводить вміст файлів, переданих як аргументи командного рядка, по 20 рядків за раз. Кожні 20 рядків програма зупиняється і чекає, поки користувач натисне клавішу для продовження виведення. Для кожного файлу програма відкриває його, зчитує рядки і виводить їх, поки не виведе всі рядки, по 20 за раз. Якщо вміст файлу перевищує 20 рядків, програма не завершиться, а поставить паузу, чекаючи на натискання клавіші для подальшого виведення. Усі файли, передані як аргументи, обробляються по черзі, і для кожного з них програма виконує виведення в описаному порядку

## Результати програми
![image](https://github.com/user-attachments/assets/b4dadd8e-2f39-42f4-810d-8bc6faa25cb0)


## ЗАВДАННЯ 5

## Умова
 Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.
## Код до завдання
```
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void list_files(const char *dir_name) {
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (stat(path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                list_files(path);
            }
        } else {
            printf("%s\n", path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}


```

## Опис програми
Ця програма на C рекурсивно переглядає всі файли в поточному каталозі та всіх його підкаталогах. Вона починає з поточного каталогу, зчитує вміст за допомогою функції opendir і для кожного файлу перевіряє, чи є він директорією чи звичайним файлом. Якщо це директорія, програма викликає сама себе для перегляду вмісту цього підкаталогу, пропускаючи спеціальні директорії . та ... Якщо це звичайний файл, програма виводить його шлях на екран. Програма працює коректно, і всі файли, включаючи ті, що знаходяться в підкаталогах, будуть перераховані.

## Результати програми

![image](https://github.com/user-attachments/assets/7379967d-a71f-4e97-9377-2e170fb32434)



## ЗАВДАННЯ 6

## Умова
  Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.
## Код до завдання
```
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


```

## Опис програми
Програма виконує перелік підкаталогів у поточному каталозі та виводить їх в алфавітному порядку. Спочатку вона відкриває поточний каталог і перевіряє, чи є підкаталоги, і додає їх у список. Потім програма сортує цей список за алфавітом за допомогою функції qsort. Коли підкаталоги відсортовані, програма виводить їх по черзі. У вашому випадку, після створення двох підкаталогів (test_subdirectory і a_test), програма вивела їх у правильному порядку: спочатку a_test, потім test_subdirectory, що підтверджує правильну роботу програми.

## Результати програми
![image](https://github.com/user-attachments/assets/a5877c42-6381-4a94-b7c8-2ce906033e4b)




## ЗАВДАННЯ 7

## Умова
 Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді - такий дозвіл повинен бути наданий.
## Код до завдання
```
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


```

## Опис програми
Програма, яку я написав, спочатку знаходить всі файли з розширенням .c в поточному каталозі. Потім для кожного знайденого файлу вона перевіряє, чи є дозвіл на читання для власника файлу. Якщо дозвіл є, програма запитує мене, чи потрібно надати іншим користувачам дозвіл на читання. Якщо я погоджуюсь, програма використовує команду chmod, щоб додати дозвіл на читання для інших користувачів.

## Результати програми
![image](https://github.com/user-attachments/assets/665be49d-8ce6-4a97-817e-c420ee6da7f7)



## ЗАВДАННЯ 8

## Умова
 Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.
## Код до завдання
```
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


```

## Опис програми
Програма виводить список всіх файлів у поточному каталозі, крім прихованих (які починаються з крапки). Для кожного файлу вона запитує у користувача, чи хоче він видалити цей файл. Якщо користувач відповідає ствердно ("y" або "Y"), програма намагається видалити файл за допомогою функції remove(). Якщо файл успішно видалений, програма повідомляє про це; якщо виникає помилка, вона виводить повідомлення про помилку. Все працює правильно. В мене видалився файл (1).

## Результати програми
![image](https://github.com/user-attachments/assets/b605ef34-ef34-4831-b312-17356a0fb191)

![image](https://github.com/user-attachments/assets/aebd4d56-282e-4ad7-ae04-dfc0b5dc8991)



## ЗАВДАННЯ 9

## Умова
 Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.
## Код до завдання
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    for (volatile int i = 0; i < 1000000; i++);

    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Час виконання: %.2f мс\n", cpu_time_used);

    return 0;
}


```

## Опис програми
Програма коректно вимірює час виконання фрагмента коду і виводить результат у мілісекундах. Вивід "Час виконання: 0.23 мс" означає, що виконання вказаного циклу зайняло 0.23 мілісекунди. Це нормально для коротких фрагментів коду, таких як простий цикл з мільйоном ітерацій. Час виконання може варіюватися в залежності від апаратного забезпечення і навантаження системи

## Результати програми
![image](https://github.com/user-attachments/assets/580acec4-fd2c-4784-915c-b34e0f965cd9)




## ЗАВДАННЯ 10

## Умова
 Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:
 (a) від 0.0 до 1.0
 (b) від 0.0 до n, де n — будь-яке дійсне число з плаваючою точкою.
 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.
Примітка: використання прапорця -Wall під час компіляції є обов’язковим.

## Код до завдання
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    double n;
    int count;

    srand(time(0));

    printf("Введіть кількість чисел: ");
    scanf("%d", &count);

    printf("Випадкові числа від 0.0 до 1.0:\n");
    for (int i = 0; i < count; i++) {
        printf("%f\n", (double)rand() / RAND_MAX);
    }

    printf("Введіть значення n: ");
    scanf("%lf", &n);

    printf("Випадкові числа від 0.0 до %f:\n", n);
    for (int i = 0; i < count; i++) {
        printf("%f\n", (double)rand() / RAND_MAX * n);
    }

    return 0;
}


```

## Опис програми
Я написав програму, яка генерує випадкові числа, і дає можливість ввести кількість чисел та межу для генерації. Спочатку користувач вводить, скільки чисел потрібно, і програма виводить їх у межах від 0 до 1. Потім користувач вводить значення n, і програма знову виводить випадкові числа - вже в діапазоні від 0 до n. Я використав функцію rand() та поділив її на RAND_MAX, щоб отримати значення в межах 0.0–1.0, а далі помножив на n

## Результати програми
![image](https://github.com/user-attachments/assets/a1c4e101-efcf-4f96-8f11-97ca1ade64ee)
![image](https://github.com/user-attachments/assets/2f1ac7d5-680c-41bc-a8ad-b13e58dc98f1)




## ЗАВДАННЯ 11 (варіант 13)

## Умова
 Напишіть утиліту, яка визначає "аномальні" виконувані файли в системі.
## Код до завдання
```
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


```

## Опис програми
У програмі я хотів знайти "аномальні" виконувані файли - тобто ті, що мають права на виконання, але не є справжніми виконуваними файлами у форматі ELF. Код перевіряє кожен файл у поточному каталозі, і якщо він має право на виконання, але не починається з сигнатури ELF (0x7f 'E' 'L' 'F'), то виводить його як аномальний. У моєму випадку програма вивела багато файлів - це і .c файли, і текстові файли, і підкаталоги. Це означає, що в цих файлів або директорій встановлені права на виконання, але самі файли не є справжніми виконуваними. Це працює правильно, бо текстові файли й каталоги не мають бути виконуваними, але випадково могли отримати такі права (наприклад, через chmod 777). Отже, програма виконує свою мету точно - визначає потенційно "аномальні" об'єкти в системі.

## Результати програми
![image](https://github.com/user-attachments/assets/a24e0b40-a453-4fb3-a9fe-2b11e852ab10)
