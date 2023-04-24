#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _line_ *pLine;
typedef struct _line_ {
    int32_t posX, posY;
    int8_t cross;
    pLine Prev, Next;
} sLine;

typedef struct _cross_ *pCross;
typedef struct _cross_ {
    pLine LineX, LineY;
    pCross Prev, Next;
} sCross;

void addLine(pLine *ptrLine, int32_t posX, int32_t posY) {
    pLine node = (pLine)malloc(sizeof(sLine));
    node->posX = posX, node->posY = posY;
    node->cross = 0;
    node->Prev = *ptrLine, node->Next = NULL;
    (*ptrLine)->Next = node, *ptrLine = node;
    return;
}

void addCross(pCross *ptrCross, pLine lineX, pLine lineY) {
    pCross node = (pCross)malloc(sizeof(sCross));
    node->LineX = lineX, node->LineY = lineY;
    node->Prev = *ptrCross, node->Next = NULL;
    (*ptrCross)->Next = node, *ptrCross = node;
    return;
}

void rmLine(pLine *ptrLine) {
    pLine node = *ptrLine;

    *ptrLine = node->Prev;
    (*ptrLine)->Next = node->Next;
    if (node->Next) node->Next->Prev = (*ptrLine);
    free(node);
    return;
}

void rmCross(pCross *ptrCross) {
    pCross node = *ptrCross;

    *ptrCross = node->Prev;
    (*ptrCross)->Next = node->Next;
    if (node->Next) node->Next->Prev = (*ptrCross);
    free(node);
    return;
}

int collision(pLine lineA, pLine lineB) {
    if (lineA->posX == lineB->posX || lineA->posY == lineB->posY)
        return 1;
    if (lineA->posX > lineB->posX && lineA->posY < lineB->posY)
        return 1;
    if (lineA->posX < lineB->posX && lineA->posY > lineB->posY)
        return 1;
    return 0;
}

size_t minCut(pLine arrLine, pCross arrCross, size_t lineNum) {
    pLine pLI = arrLine, pLmax;
    pCross pC;

    while (arrCross->Next) {
        pLI = arrLine, pLmax = NULL;
        while ((pLI = pLI->Next) != NULL) {
            if (pLI->cross > 0) {
                if (pLmax != NULL) {
                    if (pLmax->cross < pLI->cross)
                        pLmax = pLI;
                } else
                    pLmax = pLI;
            } else
                rmLine(&pLI);
        }
        pC = arrCross;
        while (((pC = pC->Next) != NULL) && (pLmax != NULL)) {
            if (pC->LineX == pLmax || pC->LineY == pLmax) {
                pC->LineX->cross--, pC->LineY->cross--;
                rmCross(&pC);
            }
        }
        if (pLmax != NULL)
            rmLine(&pLmax), lineNum--;
    }
    return lineNum;
}

int main() {
    size_t numX, numY, lineNum;
    int32_t posX, posY;
    pLine arrLine = (pLine)malloc(sizeof(sLine));
    pCross arrCross = (pCross)malloc(sizeof(sCross));
    pLine pLx = arrLine, pLy = arrLine;
    pCross pC = arrCross;

    scanf("%zu %zu", &numX, &numY);
    scanf("%zu", &lineNum);
    for (size_t idx = 0; idx < lineNum; idx++) {
        scanf("%d %d", &posX, &posY);
        addLine(&pLx, posX, posY);
    }
    pLx = arrLine;
    for (size_t idx = 0; idx < lineNum - 1; idx++) {
        pLx = pLx->Next, pLy = pLx;
        for (size_t jdx = idx + 1; jdx < lineNum; jdx++) {
            pLy = pLy->Next;
            if (collision(pLx, pLy)) {
                addCross(&pC, pLx, pLy);
                pLx->cross++, pLy->cross++;
            }
        }
    }
    lineNum = minCut(arrLine, arrCross, lineNum);
    printf("%zu\n", lineNum);
    return 0;
}
