#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int16_t checkZero(const int32_t *array, int32_t size) {
    int32_t value = 0;
    while (size--) {
        value += *array;
        if (value > 0) return 1;
        array++;
    }
    return 0;
}

int main() {
    int32_t partN, dayM, *mapT;
    int32_t pStart, pEnd, prog;
    int32_t isDone = -1;

    scanf("%d %d", &partN, &dayM);
    mapT = (int32_t *)malloc(partN * sizeof(int32_t));

    for (size_t idx = 0; idx < partN; idx++)
        scanf("%d", &mapT[idx]);
    for (size_t idx = partN - 1; idx > 0; idx--)
        mapT[idx] -= mapT[idx - 1];

    for (size_t idx = 1; idx <= dayM; idx++) {
        scanf("%d %d %d", &pStart, &pEnd, &prog);
        if (isDone < 0) {
            mapT[pStart] -= prog;
            if (pEnd < partN - 1) mapT[pEnd + 1] += prog;

            if (checkZero(mapT, partN) == 0)
                isDone = idx;
        }
    }
    printf("%d\n", isDone);
    free(mapT);
    return 0;
}
