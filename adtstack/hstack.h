//
// Created by desperado on 17-3-18.
//

#ifndef DATASTRUCT_HSTACK_H
#define DATASTRUCT_HSTACK_H

#define MAXSIZE 100

typedef int status;
typedef int ElemType;

//顺序储存结构
typedef struct {
    ElemType data[MAXSIZE];
    int top;
}SqStack;

/**
 * 入栈
 * @param S
 * @param e
 * @return
 */
status push(SqStack &S, ElemType e);

/**
 * 出栈
 * @param S
 * @param e
 * @return
 */
status pop(SqStack &S, ElemType &e);

/**
 * 共享栈结构体
 */
typedef struct {
    ElemType data[MAXSIZE];
    int top1;
    int top2;
}SqShareStack;

/**
 * 共享栈push操作
 * @param S
 * @param e
 * @param stackNumber
 * @return
 */
status sharePush(SqShareStack &S, ElemType e, int stackNumber);

/**
 * 共享栈pop操作
 * @param S
 * @param e
 * @param stackNumber
 * @return
 */
status sharePop(SqShareStack &S, ElemType &e, int stackNumber);

//链式储存结构
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack {
    LinkStackPtr top;
    int count;
}LinkStack;

/**
 * 入栈
 * @param S
 * @param e
 * @return
 */
status sPush(LinkStack &S, ElemType e);

/**
 * 出栈
 * @param S
 * @param e
 * @return
 */
status sPop(LinkStack &S, ElemType &e);

#endif //DATASTRUCT_HSTACK_H
