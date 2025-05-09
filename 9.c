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
