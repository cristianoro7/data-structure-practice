## 队列

### 顺序循环队列
* 由于队列的顺序储存本身会由于删除等操作而发生假溢出.因此使用循环队列可以解决这个问题
#### 定义：
把队列的头尾相接的顺序储存结构称为循环队列

#### 问题：
* 在使用循环队列时,会出现front == rear 对应队列为空或者队列满的情况

#### 解决：
* 设置一个标志位： 当队列为空时，flag = 0，当队列满时，flag = 1;
* 当队列为空时，front == rear，当队列满时，修改其条件，空出一个元素空间

#### 实现：
* 结构体

```c
/**
 * 循环队列的顺序结构
 */
typedef struct {
    ElemType data[MAXSIZE];
    int front;
    int rear;
}SqQueue;
```

* 初始化：

```c
status init(SqQueue &Q) {
    Q.front = 0;
    Q.rear = 0;
    return OK;
}
```

* 队列长度

```c
status length(SqQueue Q) {
    return ((Q.rear - Q.front + MAXSIZE) % MAXSIZE);
}
```

* 入队操作

```c
status enQueue(SqQueue &Q, ElemType e) {
    if((Q.rear + 1) % MAXSIZE == Q.front) {
        return ERROR;
    }
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return OK;
}
```

* 出队操作

```c
status deQueue(SqQueue &Q, ElemType &e) {
    if(Q.front == Q.rear) {
        return ERROR;
    }
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return OK;
}
```

### 链式队列

* 结构体：

```c
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
```

* 入队操作

```c
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
```

* 出队操作

```c
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
```

### 对比：

#### 时间上：
* 两者的基本操作的时间复度都是O(1)
* 对于循环队列来说，事先申请好空间，试用期间不释放
* 对于链队列来说，每次申请和释放结点也会存在一些时间开销
* 如果入队频繁的话，两者还是有细微差别

#### 空间上
* 循环队列需要事先确定一个长度，所以就有了储存个数和空间浪费的问题
* 链队列则不存在上述问题，但是它需要指针域，也会在空间上产生一定的开销
* 总体来说，链队列在空间上更加灵活

#### 总结
* 在确定队列长度的最大值的情况下，使用循环队列较为适宜，否则使用链队列比较适合

>参考资料：《大话数据结构》
