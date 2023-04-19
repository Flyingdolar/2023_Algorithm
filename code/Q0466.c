#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void type1(uint32_t *list, uint32_t size) {
    int32_t posX, newVal;
    scanf("%d %d", &posX, &newVal);
    list[--posX] = newVal;
    return;
}

void type2(const uint32_t *list, uint32_t size) {
    int32_t posX, newPos = 0;
    scanf("%d", &posX);
    int32_t val = list[--posX];
    for (size_t idx = 0; idx < size; idx++) {
        if (list[idx] < val) newPos++;
        if (list[idx] == val && idx <= posX) newPos++;
    }
    printf("%d\n", newPos);
    return;
}

int main() {
    int32_t cmd, n_Amount, Q_operate;
    uint32_t *list;

    scanf("%d %d", &n_Amount, &Q_operate);
    list = (uint32_t *)malloc(n_Amount * sizeof(uint32_t));
    for (size_t idx = 0; idx < n_Amount; idx++)
        scanf("%d", &list[idx]);

    while (Q_operate--) {
        scanf("%d", &cmd);
        if (cmd == 1) type1(list, n_Amount);
        if (cmd == 2) type2(list, n_Amount);
    }

    return 0;
}
