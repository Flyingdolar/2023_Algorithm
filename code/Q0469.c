#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct position pos;
struct position {
    int32_t x;
    int32_t y;
};

int32_t rootTwo(int32_t value) {
    int32_t retVal = 0;
    while (value > 1) retVal++, value /= 2;
    return retVal;
}

pos setPos(int32_t posX, int32_t posY);
int32_t setQuad(pos target, pos anchor);
void setTan(pos sqCenter, pos qPoint, int32_t paintNum);
void printTab(int32_t tabLen);
void tansCover(int32_t tabLen, int32_t bkNum);
void placeTan(pos start, pos range, pos block);

int32_t **SQTable, paintNum, SQLen;
pos *bkList;

int main() {
    int32_t blockN, tabLen;
    paintNum = 0;

    scanf("%d %d", &blockN, &tabLen);
    SQLen = tabLen;
    bkList = (pos *)malloc(blockN * sizeof(pos));
    SQTable = (int32_t **)malloc(tabLen * sizeof(int32_t *));

    for (size_t idx = 0; idx < (size_t)tabLen; idx++)
        SQTable[idx] = (int32_t *)malloc(tabLen * sizeof(int32_t));
    for (size_t idx = 0; idx < (size_t)blockN; idx++)
        scanf("%d %d", &bkList[idx].x, &bkList[idx].y);

    tansCover(tabLen, blockN);
    printTab(tabLen);

    free(bkList);
    free(SQTable);

    return 0;
}

void tansCover(int32_t tabLen, int32_t bkNum) {
    int32_t partLen = tabLen / sqrt(bkNum);
    pos partRange = {.x = partLen, .y = partLen};

    for (size_t idx = 0; idx < (size_t)bkNum; idx++) {
        int32_t secX = (bkList[idx].x / partLen) * partLen;
        int32_t secY = (bkList[idx].y / partLen) * partLen;
        placeTan(setPos(secX, secY), partRange, bkList[idx]);
    }
    return;
}

void placeTan(pos start, pos range, pos block) {
    pos center1 = setPos(start.x + range.x / 2, start.y + range.y / 2);
    pos center2 = setPos(center1.x - 1, center1.y);
    pos center3 = setPos(center1.x - 1, center1.y - 1);
    pos center4 = setPos(center1.x, center1.y - 1);
    int32_t quadrant = setQuad(block, center1);

    if (range.x > 2 && range.y > 2) {
        range.x /= 2, range.y /= 2;
        pos stQuad1 = setPos(start.x + range.x, start.y + range.y);
        pos stQuad2 = setPos(start.x, start.y + range.y);
        pos stQuad3 = setPos(start.x, start.y);
        pos stQuad4 = setPos(start.x + range.x, start.y);

        if (quadrant == 1)
            placeTan(stQuad1, range, block);
        else
            placeTan(stQuad1, range, center1);
        if (quadrant == 2)
            placeTan(stQuad2, range, block);
        else
            placeTan(stQuad2, range, center2);
        if (quadrant == 3)
            placeTan(stQuad3, range, block);
        else
            placeTan(stQuad3, range, center3);
        if (quadrant == 4)
            placeTan(stQuad4, range, block);
        else
            placeTan(stQuad4, range, center4);
    }

    paintNum++;
    if (quadrant == 1) setTan(center1, center1, paintNum);
    if (quadrant == 2) setTan(center1, center2, paintNum);
    if (quadrant == 3) setTan(center1, center3, paintNum);
    if (quadrant == 4) setTan(center1, center4, paintNum);

    printTab(SQLen);
    printf("\n");
    return;
}

void printTab(int32_t tabLen) {
    for (size_t posY = 0; posY < (size_t)tabLen; posY++) {
        for (size_t posX = 0; posX < (size_t)tabLen; posX++) {
            if (posX != 0) printf(" ");
            printf("%d", SQTable[posX][posY]);
        }
        printf("\n");
    }

    return;
}

pos setPos(int32_t posX, int32_t posY) {
    pos spot = {.x = posX, .y = posY};
    return spot;
}

void setTan(pos sqCenter, pos qPoint, int32_t paintNum) {
    int32_t quad = setQuad(qPoint, sqCenter);
    if (quad != 1) SQTable[sqCenter.x][sqCenter.y] = paintNum;
    if (quad != 2) SQTable[sqCenter.x - 1][sqCenter.y] = paintNum;
    if (quad != 3) SQTable[sqCenter.x - 1][sqCenter.y - 1] = paintNum;
    if (quad != 4) SQTable[sqCenter.x][sqCenter.y - 1] = paintNum;
    return;
}

int32_t setQuad(pos target, pos anchor) {
    if (target.x >= anchor.x) {
        if (target.y >= anchor.y) return 1;
        if (target.y < anchor.y) return 4;
    }
    if (target.x < anchor.x) {
        if (target.y >= anchor.y) return 2;
        if (target.y < anchor.y) return 3;
    }
    return 0;
}
