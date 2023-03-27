#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct XY_cordinate_dot* pDot;
typedef struct XY_cordinate_dot {
    int32_t posX;
    int32_t posY;
    int32_t len;
    pDot Next;
    pDot Prev;
} nDot;

pDot new_Head() {
    pDot Head = (pDot)malloc(sizeof(nDot));
    return Head;
}

void print_Head(pDot Head) {
    pDot node = Head->Next;
    int32_t counter = 0;

    printf("Head 儲存節點資訊(長度＝%d)：\n", Head->len);
    if (node == NULL) {
        printf("  查無節點\n\n");
        return;
    };

    printf("  正序輸出： ");
    do {
        printf(" %d:(%d,%d)  ", counter, node->posX, node->posY);
        counter++;
        node = node->Next;
    } while (node != Head->Next);
    printf("\n");

    printf("  反序輸出： ");
    do {
        counter--;
        node = node->Prev;
        printf(" %d:(%d,%d)  ", counter, node->posX, node->posY);
    } while (node != Head->Next);
    printf("\n");

    return;
}

pDot new_node(int32_t valueX, int32_t valueY) {
    pDot node = (pDot)malloc(sizeof(nDot));
    node->posX = valueX;
    node->posY = valueY;
    return node;
}

void add_node(pDot Head, pDot node, int32_t pos) {
    pDot first = Head->Next;

    if (first == NULL) {
        Head->Next = node;
        Head->len = 1;
        node->Next = node;
        node->Prev = node;
        return;
    }

    if (pos == 0)
        Head->Next = node;
    else if (pos > 0)
        while (pos--) first = first->Next;
    else
        while (++pos) first = first->Prev;

    (Head->len)++;
    node->Next = first;
    node->Prev = first->Prev;
    first->Prev->Next = node;
    first->Prev = node;
    return;
}

void move_node(pDot ori_Head, int32_t ori_pos, pDot dest_Head, int32_t dest_pos);

pDot mxSort(pDot Head) {
    pDot ListA, ListB, nodeA, nodeB;
    pDot node = Head->Next, nPtr;
    int32_t idx = 0;

    if (Head->len == 1) return Head;
    ListA = new_Head(), ListB = new_Head();
    ListA->len = Head->len / 2;
    ListB->len = Head->len - ListA->len;
    do {
        nPtr = node->Next;
        if (idx < ListA->len) add_node(ListA, node, -1);
        if (idx >= ListA->len) add_node(ListB, node, -1);
        idx++;
        node = nPtr;
    } while (node != Head->Next);
    ListA = mxSort(ListA), ListB = mxSort(ListB);
    nodeA = ListA->Next, nodeB = ListB->Next;
    Head->len = 0, Head->Next = NULL;

    while (ListA->len && ListB->len) {
        if (nodeA->posX < nodeB->posX) {
            nPtr = nodeA->Next;
            add_node(Head, nodeA, -1);
            (ListA->len)--, nodeA = nPtr;
        }
        if (nodeB->posX < nodeA->posX) {
            nPtr = nodeB->Next;
            add_node(Head, nodeB, -1);
            (ListB->len)--, nodeB = nPtr;
        }
        if (nodeB->posX == nodeA->posX) {
            if (nodeA->posY <= nodeB->posY) {
                nPtr = nodeA->Next;
                add_node(Head, nodeA, -1);
                (ListA->len)--, nodeA = nPtr;
            } else {
                nPtr = nodeB->Next;
                add_node(Head, nodeB, -1);
                (ListB->len)--, nodeB = nPtr;
            }
        }
    }
    while (ListA->len) {
        nPtr = nodeA->Next;
        add_node(Head, nodeA, -1);
        (ListA->len)--, nodeA = nPtr;
    }
    while (ListB->len) {
        nPtr = nodeB->Next;
        add_node(Head, nodeB, -1);
        (ListB->len)--, nodeB = nPtr;
    }
    return Head;
}

int main() {
    int32_t nodeNum, inputX, inputY;
    pDot node, NodeList = new_Head();

    scanf("%d", &nodeNum);
    while (nodeNum--) {
        scanf("%d %d", &inputX, &inputY);
        node = new_node(inputX, inputY);
        add_node(NodeList, node, -1);
    }
    NodeList = mxSort(NodeList);
    print_Head(NodeList);

    return 0;
}
