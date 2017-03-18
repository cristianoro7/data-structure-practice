//
// Created by desperado on 17-3-18.
//

#ifndef DATASTRUCT_HQUEUE_H
#define DATASTRUCT_HQUEUE_H
#define 100 MAXSIZE
typedef int ElemType;
typedef int status;
/**
 * 循环队列的顺序结构
 */
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
}SqQueue;

/**
 * 初始化队列
 * @param Q
 * @return
 */
status init(SqQueue &Q);

int length(SqQueue Q);

/**
 * 入队操作
 * @param q
 * @param e
 * @return
 */
status enQueue(SqQueue &Q, ElemType e);

/**
 * 入队操作
 * @param Q
 * @param e
 * @return
 */
status deQueue(SqQueue &Q, ElemType &e);

/**
 * 链队列
 */
typedef struct QNode {
    ElemType data;
    struct QNode *next;
}QNode, *QueuePrt;

typedef struct {
    QueuePrt front, rear;
}LinkQueue;

status sEnQueue(LinkQueue &Q, ElemType e);

status sDeQueue(LinkQueue &Q, ElemType &e);
#endif //DATASTRUCT_HQUEUE_H
