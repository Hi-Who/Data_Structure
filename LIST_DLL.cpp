#include<stdlib.h>
#include<stdio.h>

//函数结果代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//compare()函数返回值
typedef enum CompareStatus
{EQUAL,GREATER,LESS}CPS;
//Satus 是函数的返回类型，其值是函数结果状态代码
typedef int Status;

typedef int ElemType;     //假设线性表中存放的数据为int型

//定义双向链表结点DoubleLinkNode
typedef struct LN
{
    struct LN *prior;
    ElemType data;
    struct LN *next;
}LN,*Link,*Position;

//定义双向链表DoubleLinkList
typedef struct
{
    Link head,tail;      //分别指向头结点和最后一个结点
    int length;          //线性链表的长度
}LinkList;

Status PrintList(LinkList L);//输出链表
Status MakeNode(Link &L,ElemType e);//分配由p指向的值为的结点，并返回OK，失败则返回ERROR
Status FreeNode(Link &p);//释放p所指的结点
Status InitList(LinkList &L);//构造一个空的线性表
Status DestoryList(LinkList &L);//销毁线性表L
Status ClearList(LinkList &L);//将链表L置为空表，并释放原链表的结点空间
Status InsFirst(LinkList &L,Link s);//已知h为头结点，将s所指结点插入到第一个结点之前
Status DelFirst(LinkList &L,Link &q);//h为头结点，删除链表的第一个结点并以q返回
Status Append(LinkList &L,Link s);//将s指向的一串结点链接到L的最后一个结点上，并将L的尾指针指向新的尾结点
Status Remove(LinkList &L,Link &q);//删除链表中L的尾结点并以q返回，改变L的尾指针指向新的尾结点
Status InsBefore(LinkList &L,Link &p,Link s);//一直p为链表L中的一个结点，将s指向的结点插入到p所指之前，并修改p指向为新节点
Status InsAfter(LinkList &L,Link &p,Link s);//一直p为链表L中的一个结点，将s指向的结点插入到p所指之后，并修改p指向为新节点
Status SetCurElem(Link &p,ElemType e);//已知p指向链表中一个结点，用e更新p所指结点中数据元素的值
Status ListEmpty(LinkList L);//若链表为空返回TRUE，否则返回FALSE
int ListLength(LinkList L);//返回链表中数据元素的个数
Position GetHead(LinkList L);//返回线性链表L头结点的位置
Position GetLast(LinkList L);//返回线性链表L最后一个结点的位置
Position PriorPos(LinkList L,Link p);//p指向L中某一个结点，返回p所指向结点的直接前驱，无则返回NULL
Position NextPos(LinkList L,Link p);//p指向L中某一个结点，返回p所指向结点的直接后继，无则返回NULL
Status LocatePos(LinkList L,int i,Link &p);//第i个元素的位置用p表示，返回OK，i值不合法返回ERROR
//返回线性链表L中第一个与e满足函数compare()判定关系的元素的位置，若不存在则返回NULL
Position LocateElem(LinkList L,ElemType e,CPS S);
Status compare(ElemType a,ElemType b);
Status ListTraverse(LinkList L,Status (* visit)());//依次对L的每一个元素调用visit(),一旦visit()失败，则操作失败

int main()
{
    LinkList La,Lb,Lc;
    InitList(La);//初始化链表
    InitList(Lb);
    InitList(Lc);
    Link p;
    int a[5] = {1,3,5,7,9};
    int b[5] = {8,6,4,2,0};
    int c[5] = {0,2,4,6,8};
    for (int i=0;i<5;i++)
    {
        MakeNode(p,a[i]);//链表添加元素
        Append(La,p);
        MakeNode(p,b[i]);
        Append(Lb,p);
        MakeNode(p,c[i]);
        Append(Lc,p);
    }
    printf("La:\n");//查看链表内容
    PrintList(La);
    printf("Lb:\n");
    PrintList(Lb);
    printf("Lc:\n");
    PrintList(Lc);
if (0)
{
    //测试InsFirst
    Link s,q;
    MakeNode(s,123);
    InsFirst(Lc,s);
    printf("Lc:\n");
    PrintList(Lc);

    //测试LocatePos(),InsAfter()
    MakeNode(s,1212);
    LocatePos(Lc,3,q);
    printf("q:%x\n",q);
    InsAfter(Lc,q,s);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%x\n",q);

    //测试InsBefore()
    MakeNode(s,2333);
    InsBefore(Lc,q,s);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%x\n",q);

    //测试DelFirst()
    DelFirst(Lc,q);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%d\n",q->data);

    //测试Append
    Append(La,Lb.head->next);
    printf("La:\n");
    PrintList(La);
    //测试Remove
    Link p2,p3;
    Remove(La,p2);
    printf("La:\n");
    PrintList(La);
    printf("Remove:%d\n",p2->data);
    //测试SetCurElem
    LocatePos(La,5,p2);
    SetCurElem(p2,110);
    printf("La:\n");
    PrintList(La);
    //测试PriorPos
    p3 = PriorPos(La,p2);
    printf("La:\n");
    PrintList(La);
    printf("%x\n",p3);
    //测试NextPos()
    p3 = NextPos(La,p2);
    printf("La:\n");
    PrintList(La);
    printf("%x\n",p3);

    p3 = LocateElem(La,2,EQUAL);
    printf("%x\n",p3);
    //DestoryList(Lc);
}//if(0)
    return 0;
}

Status PrintList(LinkList L)
{
    printf("L.head:%x\n",L.head);
    printf("L.head->next:%x\n",L.head->next);
    printf("L.length:%d\n",L.length);
    printf("L.tail:%x\n",L.tail);
    printf("-------------------------------------\n");
    Link p;
    p = L.head->next;
    int i=1;
    while (p!= L.tail)
    {
        printf("%x    %4d    %4d    %x\n",p,i,p->data,p->next);
        i++;
        p = p->next;
    }
    printf("%x    %4d    %4d    %x\n",p,i,p->data,p->next);
    printf("-------------------------------------\n");
    return OK;
}

Status MakeNode(Link &p,ElemType e)//分配由p指向的值为的结点，并返回OK，失败则返回ERROR
{
    p = (Link)malloc(sizeof(LN));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->prior = NULL;
    p->next = NULL;
    return OK;
}

Status FreeNode(Link &p)//释放p所指的结点
{
    free(p);
    return OK;
}

Status InitList(LinkList &L)//构造一个空的线性表
{
    Link p;//申请一个结点大小的空间作为头结点
    p = (Link)malloc(sizeof(LN));
    if(!p) exit(OVERFLOW);
    p->prior = NULL;
    p->next = NULL;
    L.head = p;
    L.tail = NULL;
    L.length = 0;
    return OK;
}

Status DestoryList(LinkList &L)//销毁线性表L
{
    ClearList(L);
    free(&L);
    return OK;
}
Status ClearList(LinkList &L)//将链表L置为空表，并释放原链表的结点空间
{
    Link q;
    q = L.tail;
    while(L.length)//删除最后一个元素，直至元素个数为0
    {
        //Remove(L,q)也可以，但是没有释放删除的结点
        q->prior->next = q->next;//兼容双向循环链表
        q = q->prior;
        free(q->next);
        L.length--;
    }
    L.tail = q;
    return OK;
}

Status InsFirst(LinkList &L,Link s)//将s所指结点插入到第一个结点之前,此处与书上不同
{
    Link h;
    h = L.head;
    s->next = h->next;
    s->prior = h;
    h->next->prior = s;
    h->next = s;
    L.length++;
    return OK;
}
Status DelFirst(LinkList &L,Link &q)//删除链表的第一个结点并以q返回
{
    Link h;
    h = L.head;
    q = h->next;
    h->next = h->next->next;
    L.length--;
    return OK;
}

Status Append(LinkList &L,Link s)//将s指向的一串结点链接到L的最后一个结点上，并将L的尾指针指向新的尾结点
{
    //将s接到L尾部
    Link p,q;
    p = GetLast(L);
    p->next = s;
    s->prior = p;

    //尾指针移动,表长增加
    q = p;
    while (q->next)
    {
        q = q->next;
        L.length++;
    }
    L.tail = q;
    return OK;
}
Status Remove(LinkList &L,Link &q)//删除链表中L的尾结点并以q返回，改变L的尾指针指向新的尾结点
{
    if(L.length==0) return ERROR;
    Link t;
    t = L.tail;
    q = t;
    t->prior->next = t->next;//倒数第二个元素的next指针改为最后一个元素的next，兼容双向循环链表
    L.tail = t->prior;
    L.length--;
    return  OK;
}
Status InsBefore(LinkList &L,Link &p,Link s)//一直p为链表L中的一个结点，将s指向的结点插入到p所指之前，并修改p指向为新节点
{
    s->next = p->prior->next;
    s->prior = p->prior;
    p->prior->next = s;
    p->prior = s;
    p = s;
    L.length++;
    return OK;
}

Status InsAfter(LinkList &L,Link &p,Link s)//一直p为链表L中的一个结点，将s指向的结点插入到p所指之后，并修改p指向为新节点
{
    s->next = p->next;
    s->prior = p;
    p->next->prior = s;
    p->next = s;
    p = s;
    L.length++;
    if(p->prior == L.tail)//新插入结点为最后一个结点
        L.tail = p;
    return OK;
}

Status SetCurElem(Link &p,ElemType e)//已知p指向链表中一个结点，用e更新p所指结点中数据元素的值
{
    p->data = e;
    return OK;
}

Status ListEmpty(LinkList L)//若链表为空返回TRUE，否则返回FALSE
{
    return (L.length)?FALSE:TRUE;
}

int ListLength(LinkList L)//返回链表中数据元素的个数
{
    return L.length;
}

Position GetHead(LinkList L)//返回线性链表L头结点的位置
{
    return L.head;
}

Position GetLast(LinkList L)//返回线性链表L最后一个结点的位置
{
    if(L.length==0) return L.head;//线性表为空表
    return L.tail;
}

Position PriorPos(LinkList L,Link p)//p指向L中某一个结点，返回p所指向结点的直接前驱，无则返回NULL
{
    if(p!= L.head->next)
    {
        p = p->prior;
    }

    else
        p = NULL;
    return p;
}
Position NextPos(LinkList L,Link p)//p指向L中某一个结点，返回p所指向结点的直接后继，无则返回NULL
{
    if (p!= L.tail)
        p = p->next;
    else
        p = NULL;
    return p;
}

Status LocatePos(LinkList L,int i,Link &p)//第i个元素的位置用p表示，返回OK，i值不合法返回ERROR
{
    if(i<1 || i>L.length) return ERROR;
    int j;
    p = L.head;
    for(j=0;j<i;j++)
        p = p->next;
    return OK;
}
//返回线性链表L中第一个与e满足函数compare()判定关系的元素的位置，若不存在则返回NULL
Position LocateElem(LinkList L,ElemType e,CPS S)
{
    Link p;
    p = L.head->next;
    while (p!=NULL)
    {
        if (compare(p->data,e)==S)
            return p;
        p = p->next;
    }
    return NULL;
}
Status compare(ElemType a,ElemType b)
{
    if (a>b)
        return GREATER;
    else
        return (a<b)?LESS:EQUAL;
}

Status ListTraverse(LinkList L,Status (* visit)());//依次对L的每一个元素调用visit(),一旦visit()失败，则操作失败
