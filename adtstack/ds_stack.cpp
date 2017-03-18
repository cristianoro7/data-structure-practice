//
// Created by desperado on 17-3-18.
//
#include <cstdlib>
#include "hstack.h"
#include "../constant.h"

status push(SqStack &S, ElemType elemType) {
    if (S.top == MAXSIZE - 1) {
        return ERROR;
    }
    S.data[++S.top] = elemType;
    return OK;
}

status pop(SqStack &S, ElemType &e) {
    if (S.top == -1) {
        return ERROR;
    }
    e = S.data[S.top - 1];
    S.top--;
    return e;
}

status sharePush(SqShareStack &S, ElemType e, int stackNumber) {
    if (S.top1 + 1 == S.top2) {
        return ERROR;
    }
    if (stackNumber == 1) {
        S.data[++S.top1] = e;
    } else if (stackNumber == 2) {
        S.data[--S.top2] = e;
    }
    return OK;
}

status sharePop(SqShareStack &S, ElemType &e, int stackNumber) {
    if(stackNumber == 1) {
        if(S.top1 == -1) {
            return ERROR;
        }
        e = S.data[S.top1--];
    } else if(stackNumber == 2) {
        if(S.top2 == MAXSIZE) {
            return ERROR;
        }
        e = S.data[S.top2++];
    }
    return OK;
}

status sPush(LinkStack &S, ElemType e) {
    LinkStackPtr ptr = (LinkStackPtr) malloc(sizeof(StackNode));
    if(ptr == NULL) {
        return ERROR;
    }
    ptr->data = e;
    ptr->next = S.top;
    S.top = ptr;
    S.count++;
    return OK;
}

status sPop(LinkStack &S, ElemType &e) {
    if(S.top != NULL) {
        LinkStackPtr ptr;
        ptr = S.top;
        S.top = ptr->next;
        e = ptr->data;
        free(ptr);
        S.count--;
    }
    return ERROR;
}


