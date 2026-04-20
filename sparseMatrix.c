#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

#define INIT_SM_CAP 20

/* 다단계 포인터: SparseMatrix** sm 으로 초기화 */
void sm_init(SparseMatrix** sm, int row, int col) {
    *sm = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    if (!*sm) { fprintf(stderr, "malloc 실패\n"); exit(EXIT_FAILURE); }
    (*sm)->row = row;
    (*sm)->col = col;
    (*sm)->count = 0;
    (*sm)->capacity = INIT_SM_CAP;
    /* entries: MatrixEntry* 의 배열 → 다단계 포인터 활용 */
    (*sm)->entries = (MatrixEntry**)malloc(INIT_SM_CAP * sizeof(MatrixEntry*));
    if (!(*sm)->entries) { fprintf(stderr, "malloc 실패\n"); exit(EXIT_FAILURE); }
}

void sm_add(SparseMatrix* sm, int row, int col, int value) {
    if (value == 0) return;
    if (sm->count >= sm->capacity) {
        sm->capacity *= 2;
        sm->entries = (MatrixEntry**)realloc(sm->entries, sm->capacity * sizeof(MatrixEntry*));
        if (!sm->entries) { fprintf(stderr, "realloc 실패\n"); exit(EXIT_FAILURE); }
    }
    /* 각 원소도 포인터로 동적 할당 */
    MatrixEntry* entry = (MatrixEntry*)malloc(sizeof(MatrixEntry));
    entry->row = row;
    entry->col = col;
    entry->value = value;
    sm->entries[sm->count++] = entry;
}

void sm_print(SparseMatrix* sm) {
    printf("\n[희소행렬] %d x %d, 0이 아닌 원소 수: %d\n", sm->row, sm->col, sm->count);
    printf("┌────────┬────────┬────────┐\n");
    printf("│  행    │  열    │  값    │\n");
    printf("├────────┼────────┼────────┤\n");
    for (int i = 0; i < sm->count; i++) {
        printf("│  %3d   │  %3d   │  %3d   │\n",
            sm->entries[i]->row,
            sm->entries[i]->col,
            sm->entries[i]->value);
    }
    printf("└────────┴────────┴────────┘\n");
}

/* 전치행렬: col↔row 교환, 데이터 이동 횟수 카운트 */
SparseMatrix* sm_transpose(SparseMatrix* sm, int* moveCount) {
    SparseMatrix* trans;
    sm_init(&trans, sm->col, sm->row);  /* 행/열 뒤집기 */
    *moveCount = 0;

    for (int i = 0; i < sm->count; i++) {
        /* row ↔ col 교환 → 데이터 이동 1회 */
        sm_add(trans, sm->entries[i]->col, sm->entries[i]->row, sm->entries[i]->value);
        (*moveCount)++;
    }
    return trans;
}

void sm_destroy(SparseMatrix** sm) {
    for (int i = 0; i < (*sm)->count; i++) {
        free((*sm)->entries[i]);   /* 각 원소 포인터 해제 */
    }
    free((*sm)->entries);          /* 포인터 배열 해제 */
    free(*sm);                     /* 구조체 해제 */
    *sm = NULL;
}
