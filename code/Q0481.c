#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int calc(int tarN) {
    int32_t **arr = (int32_t **)malloc(sizeof(int32_t *) * (tarN + 1));
    for (size_t idx = 0; idx <= (size_t)tarN; idx++)
        arr[idx] = (int32_t *)malloc(sizeof(int32_t) * 25);

    for (size_t idx = 0; idx <= (size_t)tarN; idx++) {
        for (size_t jdx = 0; jdx < 25; jdx++) {
            if (jdx == 0) {
                arr[idx][jdx] = 1;
            } else {
                arr[idx][jdx] = arr[idx][jdx - 1];
                if (idx >= (size_t)pow(2, jdx)) {
                    arr[idx][jdx] += arr[idx - (size_t)pow(2, jdx)][jdx];
                    arr[idx][jdx] = arr[idx][jdx] % 1000000007;
                }
            }
        }
    }
    return arr[tarN][24];
}

int calc2(int tarN) {
    int32_t *arr = (int32_t *)malloc(sizeof(int32_t) * (tarN + 1));
    for (size_t idx = 0; idx <= (size_t)tarN; idx++)
        arr[idx] = 1;

    for (size_t idx = 2; idx <= (size_t)tarN; idx *= 2) {
        for (size_t jdx = idx; jdx <= (size_t)tarN; jdx++) {
            arr[jdx] += arr[jdx - idx];
            arr[jdx] %= 1000000007;
        }
    }
    return arr[tarN];
}

int main() {
    int32_t Input, Output;
    scanf("%d", &Input);
    // Output = calc(Input);
    // printf("%d\n", Output);
    Output = calc2(Input);
    printf("%d\n", Output);
    return 0;
}
