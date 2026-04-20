#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "posList.h"

/* 희소행렬의 0이 아닌 원소 하나를 표현 */
typedef struct {
    int row;
    int col;
    int value;
} MatrixEntry;

/* 교수님 양식: sparseMatrix = row + col + arrayList* */
typedef struct {
    int row;          /* 행 수 */
    int col;          /* 열 수 */
    MatrixEntry** entries;  /* 포인터 배열 (다단계 포인터) */
    int count;        /* 0이 아닌 원소 수 */
    int capacity;
} SparseMatrix;

void sm_init(SparseMatrix** sm, int row, int col);
void sm_add(SparseMatrix* sm, int row, int col, int value);
void sm_print(SparseMatrix* sm);
SparseMatrix* sm_transpose(SparseMatrix* sm, int* moveCount);
void sm_destroy(SparseMatrix** sm);

#endif
