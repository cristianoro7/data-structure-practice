### 栈

#### 顺序栈

* 结构体

```c
/*顺序储存结构*/
typedef struct {
    ElemType data[MAXSIZE];
    int top;
}SqStack;
```

* 入栈操作

```c
status push(SqStack &S, ElemType elemType) {
    if (S.top == MAXSIZE - 1) {
        return ERROR;
    }
    S.data[++S.top] = elemType;
    return OK;
}
```

* 出栈

```c
status pop(SqStack &S, ElemType &e) {
    if (S.top == -1) {
        return ERROR;
    }
    e = S.data[S.top - 1];
    S.top--;
    return e;
}
```

* 出栈和入栈都没有涉及到循环语句,因此时间复杂度为0(1)

#### 两栈共享空间

* 适合一个栈同增加的同时另一个栈在减少
* 结构体

```c
/**
 * 共享栈结构体
 */
typedef struct {
    ElemType data[MAXSIZE];
    int top1;
    int top2;
}SqShareStack;
```

* 当top1 + 1 == top2时视为栈满

* 入栈

```c
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
```

* 出栈

```c
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
```

#### 链栈

* 结构体

```c
//链式储存结构
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack {
    LinkStackPtr top;
    int count;
}LinkStack;
```

* 入栈

```c
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
```

* 出栈

```c
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
```

#### 对比
* 顺序栈与链栈的时间复杂度都是O(1)
* 空间上链栈没有空间限制,但是链栈要求每个元素都要有指针域,者也一定程度上增加了内存的开销.顺序栈需要事先规定一个固定长度，可能会造成内存浪费,但是它对于存取时定位很方便

> 参考资料:《大话数据结构》


