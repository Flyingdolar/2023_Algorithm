#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t early(int32_t *a, int32_t *b) {
    if (a[0] <= b[0]) return 1;
    return 0;
}

int32_t bigger(int32_t *a, int32_t *b) {
    if ((a[1] - a[0]) >= (b[1] - b[0])) return 1;
    return 0;
}

void mgSort(int32_t **Arr, size_t len, int32_t (*cond)(int32_t *, int32_t *)) {
    if (len == 1) return;
    size_t len_L = len / 2, len_R = len - len_L;
    int32_t **arr_L = Arr, **arr_R = Arr + len_L;
    int32_t **arr_M = (int32_t **)malloc(len * sizeof(int32_t *));

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

void necTrack(int32_t **aList, int32_t *trackNum, int32_t *time) {
    int32_t allTrack = *trackNum;
    int32_t allTime = *time;
    int32_t idx = 0, pStart, pEnd = 0;

    *time = 0, *trackNum = 0;
    while (idx < allTrack) {
        if (aList[idx][0] > pEnd) {
            (*time) += aList[idx][0] - pEnd;
            (*trackNum)++;
            pStart = aList[idx][0];
            for (int32_t jdx = idx + 1; jdx < allTrack; jdx++) {
                if (aList[jdx][0] != pStart) break;
                if (aList[jdx][1] > aList[idx][1]) idx = jdx;
            }
            pEnd = aList[idx][1], idx++;
        } else {
            for (int32_t jdx = idx; jdx < allTrack; jdx++) {
                if (aList[jdx][0] > pEnd) break;
                if (aList[jdx][1] <= pEnd) continue;
                if (aList[jdx][1] >= aList[idx][1]) idx = jdx;
            }
            if (aList[idx][1] > pEnd) {
                pStart = aList[idx][0];
                pEnd = aList[idx][1];
                (*trackNum)++, idx++;
            } else {
                for (; idx < allTrack; idx++)
                    if (aList[idx][0] > pEnd) break;
            }
        }
    }
    (*time) += allTime - pEnd;
}

int main() {
    int32_t audioNum, timeLen;
    int32_t **aList;

    scanf("%d %d", &audioNum, &timeLen);
    aList = (int32_t **)malloc(audioNum * sizeof(int32_t *));
    for (int32_t idx = 0; idx < audioNum; idx++) {
        aList[idx] = (int32_t *)malloc(2 * sizeof(int32_t));
        scanf("%d %d", &aList[idx][0], &aList[idx][1]);
    }

    mgSort(aList, audioNum, early);
    necTrack(aList, &audioNum, &timeLen);
    printf("%d %d\n", audioNum, timeLen);
    return 0;
}
