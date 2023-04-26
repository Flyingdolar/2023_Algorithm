#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 500000;
    int *arr = (int *)malloc(n * sizeof(int));

    shuffle(arr, n);

    printf("1000000 1000000000\n");
    for (int i = 0; i < 500000; i++) {
        printf("%d 500000000\n", i);
    }
    for (int i = 0; i < 500000; i++) {
        printf("500000001 %d\n", i + 500000000);
    }

    free(arr);
    return 0;
}
