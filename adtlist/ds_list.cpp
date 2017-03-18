//
// Created by desperado on 17-2-28.
//
#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "../constant.h"
status initList(SqList &L) {
    for (int i = 0; i <= MAXSIZE; ++i) {
        L.data[i] = 0;
    }
    L.length = 0;
    return OK;
}

status getElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length || L.length == 0) {
        return ERROR;
    }
    e = L.data[i - 1];
    return OK;
}

status insert(SqList &L, int i, ElemType e) {
    if (L.length == MAXSIZE) {
        return ERROR;
    }
    if (i < 1 || i > L.length) {
        return ERROR;
    }

    if (L.length >= i) {
        for (int j = L.length - 1; j >= i - 1; j--) {
            L.data[j + 1] = L.data[j];
        }
    }
    L.data[i - 1] = e;
    L.length++;
    return OK;
}

int length(SqList L) {
    return L.length;
}

status isEmpty(SqList L) {
    if (L.length == 0) {
        return TRUE;
    }
    return FALSE;
}

status add(SqList &L, ElemType e) {
    if (L.length >= MAXSIZE) {
        return ERROR;
    }
    L.data[L.length] = e;
    L.length++;
    return OK;
}

status clear(SqList &L) {
    for (int i = 0; i < L.length; ++i) {
        L.data[i] = 0;
    }
    L.length = 0;
    return OK;
}

int locateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

status deleteElem(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length + 1) {
        return ERROR;
    }
    if(L.length == 0) {
        return ERROR;
    }

    e = L.data[i - 1];

    if(i < L.length) {
        for (int j = i - 1; j <= L.length; ++j) {
            L.data[j] = L.data[j + 1];
        }
    }
    L.length--;
    return OK;
}

void printAll(SqList L) {
    for (int i = 0; i < L.length; ++i) {
        printf("%d\n", L.data[i]);
    }
}

//=========链式实现========\\

status initLinkList(LinkList &L) {
    L = (Node *) malloc(sizeof(Node));
    if(L == NULL) {
        return ERROR;
    }
    L->next = NULL;
    L->length = 0;
    return OK;
}

status lInsertElem(LinkList &L, int i, ElemType e) {
    if(i < 1) {
        return ERROR;
    }
    int j = 1;
    LinkList p;
    p = L->next;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    //第i个结点不存在
    if(!p || j > i) {
        return ERROR;
    }
    LinkList s = (LinkList) malloc(sizeof(Node));
    if(s == NULL) {
        return ERROR;
    }
    s->e = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

status lGetElem(LinkList L, int i, ElemType &e) {
    int j;
    LinkList p;
    p = L->next;
    j = 1;

    while(p && j < i) {
        p = p->next;
        j++;
    }

    if(!p || j > i) {
        return ERROR;
    }
    e = p->e;
    return OK;
}

status lDeleteElem(LinkList &L, int i, ElemType &e) {
    int j = 1;
    LinkList p, q;

    p = L;

    while(p->next && j < i) {
        p = p->next;
        j++;
    }

    if(!(p->next) || j > i) {
        return ERROR;
    }

    q = p->next;
    p->next = q->next;
    e = q->e;
    free(q);
}

status lCreateLinkListHead(LinkList &L, int n) {
    LinkList p;
    L = (LinkList) malloc(sizeof(Node));
    if(NULL == L) {
        return ERROR;
    }
    L->next = NULL;
    for (int j = 0; j < n; ++j) {
        p = (LinkList) malloc(sizeof(Node));
        if(NULL == p) {
            return ERROR;
        }
        p->e = 0;
        //插到表头
        p->next = L->next;
        L->next = p;
    }
    return OK;
}

status lCreateLinkListTail(LinkList &L, int n) {
    LinkList p,r;
    L = (LinkList) malloc(sizeof(Node));
    if(L == NULL) {
        return ERROR;
    }
    L->next;
    r = L; //表尾
    for (int i = 0; i < n; ++i) {
        p = (LinkList) malloc(sizeof(Node));
        if(p == NULL) {
            return ERROR;
        }
        r->next = p;
        r = p;
    }
    r->next = NULL;
    return OK;
}

status lClearLinkList(LinkList &L) {
    LinkList p, q;
    p = L->next;
    while(p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
}

status initStaticLinkList(StaticLinkList &L) {
    for (int i = 0; i < STATIC_MAXSIZE - 1; ++i) {
        L[i].cur = i + 1;
    }
    L[STATIC_MAXSIZE - 1].cur = 0;
    L->length = 0;
    return OK;
}

status staticInsert(StaticLinkList &L, int i, ElemType e) {
    int k = STATIC_MAXSIZE - 1;
    if(i < 1 || i > L->length + 1) {
        return ERROR;
    }
    int j = mallocFreeIndex(L);
    if(j) {
        L[j].data = e;
        for (int l = 1; l <= i - 1; ++l) {
            k = L[k].cur;
        }
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

status mallocFreeIndex(StaticLinkList &L) {
    int i = L[0].cur; //当前数组第一个元素的cur值，就是返回第一个备用空闲下表
    if(L[0].cur) {
        L[0].cur = L[i].cur; //设置下一个空闲下表分量
    }
    return i;
}

status freeIndex(StaticLinkList &L, int k) {
    L[k].cur = L[0].cur; //把第一个元素从cur赋值给要删除的cur分量
    L[0].cur = k;
}

status staticDelete(StaticLinkList &L, int i, ElemType e) {
    if(i < 1 || i > L->length) {
        return ERROR;
    }
    int k = STATIC_MAXSIZE - 1;
    for (int j = 1; j < i - 1; ++j) {
        k = L[k].cur;
    }
    int j;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    freeIndex(L, j);
    return OK;
}

int main() {
    SqList L;
    initList(L);
    add(L, 3);
    add(L, 50);
    add(L, 64);
    add(L, 501);
    add(L, 634);
    add(L, 502);
    add(L, 643);
    ElemType  e;
    deleteElem(L, 7, e);
    printf("delete %d\n", e);
//    insert(L, 4, 44);
    printAll(L);
}