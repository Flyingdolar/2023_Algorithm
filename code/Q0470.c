#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex {
    int64_t x;
    int64_t y;
    double ang;
} vtex;

void vPass(vtex *Send, vtex *Get);
void vAngle(vtex *Point, const vtex *Anchor);
void mgSort(vtex *Arr, int32_t len, int32_t (*cond)(vtex, vtex));
int32_t mini_YX(vtex pointA, vtex pointB);
int32_t mini_Ang(vtex pointA, vtex pointB);
int32_t ghScan(vtex *Result, vtex *List, int32_t len);
int64_t getArea(vtex *Poly, int32_t len);

// Debug
void vPrint(vtex *List, int32_t len, char *str) {
    printf("%s 列表資訊:\n", str);
    for (size_t idx = 0; idx < (size_t)len; idx++)
        printf("  %zu: ( %lld, %lld ) [%.3f]", idx, List[idx].x, List[idx].y, List[idx].ang);
    printf("\n");
    return;
}

int main() {
    int32_t num;
    int64_t Area;
    scanf("%d", &num);
    vtex Point[num + 1], Poly[num + 1], tmp;

    for (size_t idx = 0; idx < (size_t)num; idx++)
        scanf("%lld %lld", &Point[idx].x, &Point[idx].y);

    for (size_t idx = 1; idx < (size_t)num; idx++) {
        if (Point[idx].y > Point[0].y) continue;
        if (Point[idx].y == Point[0].y && Point[idx].x >= Point[0].x) continue;
        vPass(&Point[idx], &tmp), vPass(&Point[0], &Point[idx]), vPass(&tmp, &Point[0]);
    }

    for (size_t idx = 0; idx < (size_t)num; idx++)
        vAngle(&Point[idx], &Point[0]);
    mgSort(Point, num, mini_Ang);

    vPass(&Point[0], &Point[num]);
    num = ghScan(Poly, Point, num);
    Area = getArea(Poly, num);
    if (Area % 2 == 0) printf("%lld\n", Area / 2);
    if (Area % 2 == 1) printf("%lld.5\n", Area / 2);
    return 0;
}

void vPass(vtex *Send, vtex *Get) {
    Get->x = Send->x, Get->y = Send->y;
    Get->ang = Send->ang;
    return;
}

void vAngle(vtex *Point, const vtex *Anchor) {
    int64_t dist_x = Point->x - Anchor->x, dist_y = Point->y - Anchor->y;
    Point->ang = 0;
    if (dist_x != 0 || dist_y != 0) Point->ang = atan2((double)dist_y, (double)dist_x);
    return;
}

int32_t mini_Ang(vtex pointA, vtex pointB) {
    if (isnan(pointA.ang)) return 1;
    if (isnan(pointB.ang)) return 0;
    if (pointA.ang < pointB.ang) return 1;
    if (pointA.ang > pointB.ang) return 0;
    return 1;  // Case when A.ang == B.ang
}

void mgSort(vtex *Arr, int32_t len, int32_t (*cond)(vtex, vtex)) {
    if (len == 1) return;
    int32_t len_L = len / 2, len_R = len - len_L;
    vtex *arr_L = Arr, *arr_R = Arr + len_L;
    vtex *arr_M = (vtex *)malloc(len * sizeof(vtex));

    mgSort(arr_L, len_L, cond);
    mgSort(arr_R, len_R, cond);

    for (size_t idx = 0; idx < (size_t)len; idx++) {
        if (len_L && len_R) {
            if (cond(*arr_L, *arr_R)) {
                vPass(arr_L, &arr_M[idx]);
                arr_L++, len_L--;
            } else {
                vPass(arr_R, &arr_M[idx]);
                arr_R++, len_R--;
            }
        } else if (len_L) {
            vPass(arr_L, &arr_M[idx]);
            arr_L++, len_L--;
        } else if (len_R) {
            vPass(arr_R, &arr_M[idx]);
            arr_R++, len_R--;
        }
    }
    for (size_t idx = 0; idx < (size_t)len; idx++)
        vPass(&arr_M[idx], &Arr[idx]);

    free(arr_M);
    return;
}

int32_t turn(vtex nextPt, vtex prevPt) {
    double distAngle = nextPt.ang - prevPt.ang;
    if (distAngle < 0) distAngle += 2 * M_PI;
    if (distAngle < M_PI) return 1;
    if (distAngle >= M_PI) return 0;
    return -1;  // When Error Occur
}

int32_t ghScan(vtex *Result, vtex *List, int32_t len) {
    int32_t polyLen = 1;
    for (size_t idx = 0; idx <= (size_t)len; idx++) {
        if (idx == 0) {
            List->ang = 0;
            vPass(List, Result);
        } else {
            for (int32_t jdx = polyLen - 1; jdx > 0; jdx--) {
                vAngle(&List[idx], &Result[jdx]);
                if (turn(List[idx], Result[jdx])) {
                    polyLen = jdx + 1;
                    break;
                }
            }
            vPass(&List[idx], &Result[polyLen]);
            polyLen++;
        }
    }
    return polyLen;
}

int64_t getArea(vtex *Poly, int32_t len) {
    int64_t field = 0;

    for (size_t idx = 0; idx < (size_t)(len - 1); idx++) {
        field += Poly[idx].x * Poly[idx + 1].y;
        field -= Poly[idx].y * Poly[idx + 1].x;
    }
    return field;
}
