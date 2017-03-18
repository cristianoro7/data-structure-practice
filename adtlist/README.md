## 线性表的定义
* 零个或多个数据元素的有限序列

### 分类
* 顺序储存结构
* 链式储存结构
 * 单链表
 * 静态链表
 * 循环链表
 * 双向链表

### 顺序储存结构
* 宏定义

```c
#define OK 1
#define ERROR 0
#define TRUE 1
#define MAXSIZE 20
//静态链表的最大空间
#define STATIC_MAXSIZE 1000
#define FALSE 0
typedef int status;
typedef int ElemType;
```

* 结构体

```c
/**
 * 顺序储存结构
 */
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;
```

#### 获得元素

```c
status getElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length || L.length == 0) {
        return ERROR;
    }
    e = L.data[i - 1];
    return OK;
}
```

#### 插入元素

##### 算法思路：
* 如果插入位置不合理，抛出异常
* 如果线性表长度大于等于数组长度，则抛出异常或者动态扩容
* 从最后一个元素开始向前遍历到第ｉ的位置，分别将他们向后移动一个位置
*  将要插入的元素填入到位置i处
* 表长 + 1

```c
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
```

#### 删除操作

##### 算法思路
* 如果删除的位置不合理，抛出异常
* 去出删除的元素
* 从删除的元素开始遍历到最后一个元素，分别将他们都向前移动一个位置
*表长 - 1

```c
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
```



#### 时间复杂度
* 最好情况下，如果插入的元素是最后一个，或者删除的元素是最后一个，意味着元素不用移动，那么时间复杂度为O(1)。
* 最坏情况，如果插入的元素在第一个，或者删除的元素在第一个，那么意味着全部元素将要向前或者向后移动，时间复杂度为O(n)。
* 平均情况： 时间复杂度为O(n)

#### 优点
* 快速存取表中的任一元素

#### 缺点
* 插入和删除需要大量移动元素
* 当线性表长度变化较大时，难以确定储存空间

### 链式储存结构
* 结构体

```c
/**
 * 链式储存结构
 */
typedef struct Node {
    ElemType e;
    struct Node *next;
    int length;
} Node, *LinkList;
```

#### 单链表的读取

##### 算法思路
* 声明一个指针ｐ指向链表第一个结点，初始化ｊ从１开始
* 当ｊ<ｉ时，就遍历链表，让ｐ的指针向后移动，不断指向下一个结点，ｊ累加１
* 若到链表末尾ｐ为空，则说明第ｉ个结点不存在
* 否则查找成功，返回结点ｐ的数据

```c
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
```

#### 单链表的插入

##### 算法思路：
* 声明一指针指向链表头结点，初始化ｊ从１开始
* 当ｊ<ｉ时，遍历链表，让ｐ的指针向后移动，不断指向下一个结点，ｊ累加１
* 若到链表末尾为空，则说明第ｉ的结点不存在
* 否则查找成功，在系统中生成一个空的结点ｓ
* 将数据元素ｅ赋值给ｓ－>data
* 进行单链表插入操作

```c
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
```

#### 单链表的删除

##### 算法思路
* 声明一指针指向链表头结点，初始化ｊ从１开始
* 当ｊ<ｉ时，遍历链表，让ｐ的指针向后移动，不断指向下一个结点，ｊ累加１
* 若到链表末尾为空，则说明第ｉ的结点不存在
* 若查找成功，将欲删除的结点p->next赋值给ｑ
* 删除结点
* 将ｑ结点中的数据赋值给ｅ并返回
* 释放ｑ结点
* 返回成功

```c
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
```

#### 创建单链表

##### 算法思路
* 声明一指针ｐ和计数器变量ｉ
* 初始化空链表Ｌ
* 让空链表的头结点指向ＮＵＬＬ，即建立头结点
* 循环创建结点
* 头插法

```c
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
```

* 尾插法

```c
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
```

#### 单链表的整体删除

##### 算法思路
* 声明一个结点ｐ和ｑ
* 将第一个结点赋值给ｐ
* 循环
 * 将下一个结点赋值给ｑ
 * 释放ｑ
 * 将ｑ赋值给ｐ

```c
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
```

### 比较

#### 储存方式
* 顺序储存结构用一端连续的储存单元储存元素
* 单链表用链式储存元素

#### 时间性能

##### 查找
* 顺序结构：O(1)
* 链式储存结构O(n)

##### 插入和删除
* 顺序储存结构需要平均移动毕表长的一半，时间为O(n)
* 单链表在线出某个位置指针后，插入和删除为O(1)

##### 空间性能
* 顺序结构需要预分配储存空间，分大了浪费，分小了溢出
* 单链表可以实时分配空间

### 静态链表
* 用数组描述的链表，是为了解决一个语言中没有指针的问题
* 结构体

```c
/**
 * 用数组实现的静态链表
 */
 typedef struct {
     ElemType data;
     int cur; //游标,为0时表示无指向
     int length;
 } StaticLinkList[STATIC_MAXSIZE];
```

* 通常把未被使用的数组称为备用链表
* 数组的第一个元素的cur存放备用链表的第一个结点下标
* 数组最后一个元素的cur存放第一个元素的下标，相当与头结点
* 初始化：

```c
status initStaticLinkList(StaticLinkList &L) {
    for (int i = 0; i < STATIC_MAXSIZE - 1; ++i) {
        L[i].cur = i + 1;
    }
    L[STATIC_MAXSIZE - 1].cur = 0;
    L->length = 0;
    return OK;
}
```

#### 删除操作

```c
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
```

#### 插入操作

```c
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
```

#### 优点
* 在插入和删除元素时，只需移动修改下标，从而改进顺序储存结构中插入和删除元素需要大量移动元素的缺点

#### 缺点
* 没有解决难以确定表长的缺点
* 失去了顺序储存结构中随机存取元素的特性

> 以上笔记来源《大话数据结构》

