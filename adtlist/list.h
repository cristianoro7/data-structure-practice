//
// Created by desperado on 17-2-28.
//

#ifndef DATASTRUCT_CONTANTS_H

#define DATASTRUCT_CONTANTS_H
#define OK 1
#define ERROR 0
#define TRUE 1
#define MAXSIZE 20
//静态链表的最大空间
#define STATIC_MAXSIZE 1000
#define FALSE 0
typedef int status;
typedef int ElemType;

/**
 * 顺序储存结构
 */
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;

/**
 * 链式储存结构
 */
typedef struct Node {
    ElemType e;
    struct Node *next;
    int length;
} Node, *LinkList;

/**
 * 用数组实现的静态链表
 */
 typedef struct {
     ElemType data;
     int cur; //游标,为0时表示无指向
     int length;
 } StaticLinkList[STATIC_MAXSIZE];

//==========顺序储存结构==========\\

/**
 * 初始化线性表
 * @param list
 * @return
 */
status initList(SqList &list);

/**
 * 判断线性表是否为空
 * @param L
 * @return
 */
status isEmpty(SqList L);

/**
 * 清空线性表
 * @param L
 */
status clear(SqList &L);

/**
 * 获得线性表中特定的位置的元素并返回
 * @param L
 * @param i
 * @param e
 * @return
 */
ElemType getElem(SqList L, int i, ElemType &e);

/**
 * 定位元素在线性表总的位置
 * @param L
 * @param e
 * @return 存在的话返回对应的位置，不存在的话返回0
 */
int locateElem(SqList L, ElemType e);

/**
 * 向线性表中插入元素
 * @param L
 * @param e
 */
status insert(SqList &L, ElemType e, int i);

/**
 * 删除线性表中第i个位置的元素
 * @param L
 * @param i
 * @param e
 * @return
 */
status deleteElem(SqList &L, int i, ElemType &e);

/**
 * 线性表的长度
 * @param L
 * @return
 */
int length(SqList L);

/**
 * 向表位添加元素
 * @param L
 * @return
 */
status add(SqList &L, ElemType e);

//==========链式储存============\\

/**
 * 初始化链表
 */
status initLinkList(LinkList &L);

/**
 *  获得指定的index下的元素
 * @param L
 * @param i
 * @param e
 * @return
 */
status lGetElem(LinkList L, int i, ElemType &e);

/**
 *  向链表中插入元素
 * @param L
 * @param i
 * @param e
 * @return
 */
status lInsertElem(LinkList &L, int i, ElemType e);

/**
 * 删除指定位置的元素
 * @param L
 * @param i
 * @param e
 * @return
 */
status lDeleteElem(LinkList &L, int i, ElemType &e);

/**
 * 头插法创建链表
 * @param L
 * @param n
 * @return
 */
status lCreateLinkListHead(LinkList &L, int n);

/**
 * 尾插法创建链表
 * @param L
 * @param n
 * @return
 */
status lCreateLinkListTail(LinkList &L, int n);

/**
 * 删除整个链表
 * @param L
 * @return
 */
status lClearLinkList(LinkList &L);

/**
 * 初始化静态链表
 * @param L
 * @return
 */
status initStaticLinkList(StaticLinkList &L);

/**
 * 插入元素
 * @param L
 * @return
 */
status staticInsert(StaticLinkList &L, int i, ElemType e);

/**
 * 分配空闲分量下标
 */
 int mallocFreeIndex(StaticLinkList &L);

/**
 * 删除静态链表中的元素
 */
 status staticDelete(StaticLinkList &L, int i);

/**
 * 释放被删除的元素的空闲下标
 */
status freeIndex(StaticLinkList &L, int k);
#endif //DATASTRUCT_CONTANTS_H






