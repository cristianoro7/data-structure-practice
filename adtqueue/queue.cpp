//
// Created by desperado on 17-3-18.
//
#include <cstdlib>
#include "hqueue.h"
#include "../constant.h"
status init(SqQueue &Q) {
    Q.front = 0;
    Q.rear = 0;
    return OK;
}
status length(SqQueue Q) {
    return ((Q.rear - Q.front + MAXSIZE) % MAXSIZE);
}

status enQueue(SqQueue &Q, ElemType e) {
    if((Q.rear + 1) % MAXSIZE == Q.front) {
        return ERROR;
    }
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return OK;
}

status deQueue(SqQueue &Q, ElemType &e) {
    if(Q.front == Q.rear) {
        return ERROR;
    }
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return OK;
}

status sEnQueue(LinkQueue &Q, ElemType e) {
    QueuePrt p = (QueuePrt) malloc(sizeof(QNode));
    if(p == NULL) {
        return ERROR;
    }
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

status sDeQueue(LinkQueue &Q, ElemType &e) {
    if(Q.front == Q.rear) {
        return ERROR;
    }
    QueuePrt p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    /*如果被删除的结点是最后一个的话，将尾指针指向头结点*/
    if(Q.rear == p) {
        Q.rear = Q.front;
    }
    free(p);
    return OK;
}