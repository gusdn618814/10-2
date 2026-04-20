#include <stdio.h>
#include <stdlib.h>
#include "posList.h"

void init(PosList* list) {
    list->capacity = INIT_CAPACITY;
    list->size = 0;
    list->data = (Element*)malloc(list->capacity * sizeof(Element));
    if (!list->data) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
}

int isFull(PosList* list) {
    return list->size == list->capacity;
}

int isEmpty(PosList* list) {
    return list->size == 0;
}

void grow(PosList* list) {
    int newCapacity = list->capacity * 2;
    Element* newData = (Element*)realloc(list->data, newCapacity * sizeof(Element));
    if (!newData) {
        fprintf(stderr, "realloc 실패\n");
        exit(EXIT_FAILURE);
    }
    list->data = newData;
    list->capacity = newCapacity;
}

void append(PosList* list, Element value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 추가할 수 있습니다. (입력값: %d)\n", value);
        return;
    }
    if (isFull(list)) grow(list);
    list->data[list->size++] = value;
}

/* 1. 삽입: 위치(1-based)와 양의 정수 */
void insert(PosList* list, int index, Element value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 삽입할 수 있습니다. (입력값: %d)\n", value);
        return;
    }
    /* index는 1-based로 받아서 내부에서 0-based로 변환 */
    int idx = index - 1;
    if (idx < 0 || idx > list->size) {
        printf("[오류] 잘못된 위치: %d (1 ~ %d 범위)\n", index, list->size + 1);
        return;
    }
    if (isFull(list)) grow(list);
    for (int i = list->size; i > idx; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[idx] = value;
    list->size++;
    printf("[삽입 완료] 위치 %d에 %d 삽입\n", index, value);
}

/* 2. 삭제: 위치(1-based) */
void deleteAt(PosList* list, int index) {
    if (isEmpty(list)) {
        printf("[오류] 리스트가 비어 있습니다.\n");
        return;
    }
    int idx = index - 1;
    if (idx < 0 || idx >= list->size) {
        printf("[오류] 잘못된 위치: %d (1 ~ %d 범위)\n", index, list->size);
        return;
    }
    printf("[삭제 완료] 위치 %d의 값 %d 삭제\n", index, list->data[idx]);
    for (int i = idx; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

/* 3. 변경: 위치(1-based)와 양의 정수 */
void replace(PosList* list, int index, Element value) {
    if (value <= 0) {
        printf("[오류] 양의 정수만 입력할 수 있습니다. (입력값: %d)\n", value);
        return;
    }
    int idx = index - 1;
    if (idx < 0 || idx >= list->size) {
        printf("[오류] 잘못된 위치: %d (1 ~ %d 범위)\n", index, list->size);
        return;
    }
    printf("[변경 완료] 위치 %d: %d → %d\n", index, list->data[idx], value);
    list->data[idx] = value;
}

/* 4. 출력: 위치와 함께 출력 */
void printList(PosList* list) {
    if (isEmpty(list)) {
        printf("[리스트가 비어 있습니다.]\n");
        return;
    }
    printf("┌─────────────────────────────┐\n");
    printf("│ 순차 리스트 (size=%d)         \n", list->size);
    printf("├──────┬──────────────────────┤\n");
    printf("│ 위치 │ 값                   │\n");
    printf("├──────┼──────────────────────┤\n");
    for (int i = 0; i < list->size; i++) {
        printf("│  %3d │  %d\n", i + 1, list->data[i]);
    }
    printf("└──────┴──────────────────────┘\n");
}

/* 5. 전체 삭제 */
void clearList(PosList* list) {
    list->size = 0;
    printf("[clear 완료] 리스트의 모든 값이 삭제되었습니다.\n");
}

Element get(PosList* list, int index) {
    int idx = index - 1;
    if (idx < 0 || idx >= list->size) {
        printf("[get] 잘못된 위치: %d\n", index);
        exit(EXIT_FAILURE);
    }
    return list->data[idx];
}

void destroy(PosList* list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}
