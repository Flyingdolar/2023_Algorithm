#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STAPT 0
#define TRAMOUNT 0
#define ENDPT 1
#define LEN 2

int32_t early(int32_t *a, int32_t *b) {
    if (a[0] <= b[0]) return 1;
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
    int32_t *pTrack, lenP, lenJ;
    int32_t **tList = (int32_t **)malloc(*trackNum * sizeof(int32_t *));
    for (int32_t idx = 0; idx < *trackNum; idx++)
        tList[idx] = (int32_t *)malloc(3 * sizeof(int32_t));

    for (int32_t idx = 0; idx < *trackNum; idx++) {
        if (idx == 0) {
            tList[idx][ENDPT] = aList[idx][ENDPT];
            tList[idx][LEN] = aList[idx][ENDPT] - aList[idx][STAPT];
            tList[idx][TRAMOUNT] = 1;
            continue;
        }
        for (int32_t jdx = 0; jdx < idx; jdx++) {
            if (jdx == 0) {
                pTrack = tList[jdx];
                if (aList[idx][STAPT] >= tList[jdx][ENDPT])
                    lenP = tList[jdx][LEN] + (aList[idx][ENDPT] - aList[idx][STAPT]);
                else
                    lenP = tList[jdx][LEN] + (aList[idx][ENDPT] - tList[jdx][ENDPT]);
                continue;
            }
            if (aList[idx][STAPT] >= tList[jdx][ENDPT])
                lenJ = tList[jdx][LEN] + (aList[idx][ENDPT] - aList[idx][STAPT]);
            else
                lenJ = tList[jdx][LEN] + (aList[idx][ENDPT] - tList[jdx][ENDPT]);
            if (lenP < lenJ) pTrack = tList[jdx], lenP = lenJ;
            if (lenP == lenJ && pTrack[TRAMOUNT] >= tList[jdx][TRAMOUNT])
                pTrack = tList[jdx];
        }
        if (aList[idx][ENDPT] > pTrack[ENDPT]) {
            tList[idx][TRAMOUNT] = pTrack[TRAMOUNT] + 1;
            tList[idx][LEN] = lenP;
            tList[idx][ENDPT] = aList[idx][ENDPT];
        } else {
            tList[idx][TRAMOUNT] = pTrack[TRAMOUNT];
            tList[idx][LEN] = pTrack[LEN];
            tList[idx][ENDPT] = pTrack[ENDPT];
        }
    }
    for (int32_t idx = 0; idx < *trackNum; idx++)
        printf("%d %d %d\n", tList[idx][TRAMOUNT], tList[idx][ENDPT], tList[idx][LEN]);

    (*time) -= tList[(*trackNum) - 1][LEN];
    (*trackNum) = tList[(*trackNum) - 1][TRAMOUNT];
    return;
}

int main() {
    int32_t audioNum, timeLen;
    int32_t **aList;

    scanf("%d %d", &audioNum, &timeLen);
    aList = (int32_t **)malloc(audioNum * sizeof(int32_t *));
    for (int32_t idx = 0; idx < audioNum; idx++) {
        aList[idx] = (int32_t *)malloc(2 * sizeof(int32_t));
        scanf("%d %d", &aList[idx][STAPT], &aList[idx][ENDPT]);
    }

    mgSort(aList, audioNum, early);
    necTrack(aList, &audioNum, &timeLen);
    printf("%d %d\n", audioNum, timeLen);
    return 0;
}
