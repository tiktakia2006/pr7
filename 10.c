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
