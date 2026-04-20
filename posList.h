#ifndef POSLIST_H
#define POSLIST_H

#define INIT_CAPACITY 4

typedef int Element;

typedef struct {
    Element* data;
    int size;
    int capacity;
} PosList;

void init(PosList* list);
int isFull(PosList* list);
int isEmpty(PosList* list);
void grow(PosList* list);
void append(PosList* list, Element value);
void insert(PosList* list, int index, Element value);   // 1. 삽입
void deleteAt(PosList* list, int index);                 // 2. 삭제
void replace(PosList* list, int index, Element value);  // 3. 변경
void printList(PosList* list);                           // 4. 출력
void clearList(PosList* list);                           // 5. 전체 삭제
void destroy(PosList* list);
Element get(PosList* list, int index);

#endif
