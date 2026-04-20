#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

int main(void) {
    SparseMatrix* sm;
    sm_init(&sm, 10, 10);

    /* 10x10 희소행렬, 0이 아닌 원소 20개 초기화 */
    int data[20][3] = {
        {0,1,3}, {0,4,7}, {1,2,5}, {1,7,2},
        {2,0,9}, {2,5,1}, {3,3,4}, {3,8,6},
        {4,1,8}, {4,6,3}, {5,0,2}, {5,9,5},
        {6,2,7}, {6,4,1}, {7,3,9}, {7,7,4},
        {8,5,6}, {8,8,2}, {9,1,3}, {9,6,8}
    };

    for (int i = 0; i < 20; i++) {
        sm_add(sm, data[i][0], data[i][1], data[i][2]);
    }

    printf("\n==============================\n");
    printf("   과제 2: 희소행렬\n");
    printf("==============================\n");
    sm_print(sm);

    /* 전치행렬 */
    int moveCount = 0;
    SparseMatrix* trans = sm_transpose(sm, &moveCount);

    printf("\n[전치행렬]\n");
    sm_print(trans);
    printf("\n데이터 이동 횟수: %d회\n", moveCount);

    sm_destroy(&sm);
    sm_destroy(&trans);

    return 0;
}
