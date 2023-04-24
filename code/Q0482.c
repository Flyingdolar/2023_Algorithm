#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t comp(int32_t a, int32_t b) {
    if (a < b) return 1;
    return 0;
}

int64_t max(int64_t a, int64_t b) {
    if (a > b) return a;
    return b;
}

int64_t min(int64_t a, int64_t b) {
    if (a < b) return a;
    return b;
}

void mgSort(int32_t *Arr, size_t len, int32_t (*cond)(int32_t, int32_t)) {
    if (len == 1) return;
    size_t len_L = len / 2, len_R = len - len_L;
    int32_t *arr_L = Arr, *arr_R = Arr + len_L;
    int32_t *arr_M = (int32_t *)malloc(len * sizeof(int32_t));

    mgSort(arr_L, len_L, cond);
    mgSort(arr_R, len_R, cond);

    for (size_t idx = 0; idx < len; idx++) {
        if (len_L && len_R) {
            if (cond(*arr_L, *arr_R)) {
                arr_M[idx] = *arr_L;
                arr_L++, len_L--;
            } else {
                arr_M[idx] = *arr_R;
                arr_R++, len_R--;
            }
        } else if (len_L) {
            arr_M[idx] = *arr_L;
            arr_L++, len_L--;
        } else if (len_R) {
            arr_M[idx] = *arr_R;
            arr_R++, len_R--;
        }
    }
    for (size_t idx = 0; idx < len; idx++)
        Arr[idx] = arr_M[idx];

    free(arr_M);
    return;
}

int64_t mMPath(int32_t *list, int32_t len) {
    int64_t **arr = (int64_t **)malloc(len * sizeof(int64_t *));
    for (int32_t idx = 0; idx < len; idx++)
        arr[idx] = (int64_t *)malloc((idx + 1) * sizeof(int64_t));

    for (int32_t idx = 0; idx < len; idx++) {
        for (int32_t rdx = idx, cdx = 0; rdx < len; rdx++, cdx++) {
            if (rdx == cdx) {
                arr[rdx][cdx] = list[rdx];
                continue;
            }
            arr[rdx][cdx] = min(arr[rdx][cdx + 1] + list[cdx], arr[rdx - 1][cdx] + list[rdx]);
            for (int32_t kdx = cdx + 1; kdx < rdx; kdx++)
                arr[rdx][cdx] = min(arr[rdx][cdx], max(arr[rdx][kdx + 1], arr[kdx - 1][cdx]) + list[kdx]);
        }
    }
    return arr[len - 1][0];
}

int main() {
    int32_t len, *list;
    int64_t pathVal;

    scanf("%d", &len);
    list = (int32_t *)malloc(sizeof(int32_t) * len);
    for (int32_t idx = 0; idx < len; idx++)
        scanf("%d", &list[idx]);

    mgSort(list, len, comp);
    pathVal = mMPath(list, len);

    printf("%lld\n", pathVal);
    return 0;
}
