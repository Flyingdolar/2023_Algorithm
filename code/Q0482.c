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

int64_t mMPath(int32_t *list, size_t len) {
    int64_t left = 0, right = 0;
    size_t ldx = 0, rdx = 0;

    if (len == 0) return 0;
    if (len == 1) return (int64_t)list[0];
    for (size_t idx = 1; idx < len; idx++)
        right += list[idx];
    for (size_t idx = 1; idx < len; idx++) {
        left += list[idx - 1], right -= list[idx];
        if (left >= right) {
            if (left == right) ldx = idx, rdx = idx;
            if (left > right) ldx = idx, rdx = idx - 1;
            break;
        }
    }
    left = list[ldx] + max(mMPath(&list[0], ldx), mMPath(&list[ldx + 1], len - ldx - 1));
    right = list[rdx] + max(mMPath(&list[rdx + 1], len - rdx - 1), mMPath(&list[0], rdx));
    if (ldx == rdx) return max(left, right);
    return min(left, right);
}

int main() {
    size_t len;
    int32_t *list;
    int64_t pathVal;

    scanf("%zu", &len);
    list = (int32_t *)malloc(sizeof(int32_t) * len);
    for (size_t idx = 0; idx < len; idx++)
        scanf("%d", &list[idx]);

    mgSort(list, len, comp);
    pathVal = mMPath(list, len);

    printf("%lld\n", pathVal);
    return 0;
}
