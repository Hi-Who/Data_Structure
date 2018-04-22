#include<stdlib.h>
#include<stdio.h>

//函数结果代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Satus 是函数的返回类型，其值是函数结果状态代码
typedef int Status;

typedef int ElemType;
//定义单向链表
typedef struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
}LinkNode,*LinkList;

Status InitList_LN(LinkList &L)//创建空链表并初始化
{
    LinkList p;
    p = (LinkNode *)malloc(sizeof(LinkNode));
    p->next = NULL;
    L = p;
    return OK;
}

Status AddElem_LN(LinkList L,ElemType e)//链表后面添加结点
{
    LinkList p,s;
    s = (LinkNode *)malloc(sizeof(LinkNode));
    p = L;
    while (p->next)
        p = p->next;
    p->next = s;
    s->data = e;
    s->next = NULL;
    return OK;
}
Status PrintList_LN(LinkList L)//输出链表结果，第一列为序号，第二列为数值
{
    LinkList p;
    p=L;
    printf("--------------\n");
    int i=0;
    while (p->next)
    {
        p=p->next;
        i++;
        printf("%4d    %4d\n",i,p->data);
    }
    printf("--------------\n");
    return OK;
}

ElemType GetElem_LN(LinkList L,int i)//算法2.8获取第i个元素并返回
{
    LinkList p;
    ElemType e;
    p = L->next;
    int j=1;
    while (p&&j<i)
    {
        p = p->next;
        j++;
    }
    if (!p || j>i)
        return 0;
    e = p->data;
    return e;
}

Status ListInsert_LN(LinkList L,int i,ElemType e)//算法2.9插入数据
{
    LinkList p;
    p = L;
    int j=0;
    while (p&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if (!p||j>i-1)
        return ERROR;
    LinkNode *s;
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s->next = p->next;
    p->next = s;
    s->data = e;
    return OK;
}

ElemType ListDelete_LN(LinkList &L,int i)//算法2.10删除第i个元素并返回
{
    LinkList p,q;
    ElemType e;
    p = L;
    int j=0;
    while (p->next&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if (!p||j>i-1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return e;
}

int CreateList_LN(LinkList &L,int n)//算法2.11从表尾到表头逆向建立单链表
{
    L = (LinkList)malloc(sizeof(LinkNode));
    L->next = NULL;
    LinkList p;
    for (int i=n;i>0;i--)
    {
        p = (LinkList)malloc(sizeof(LinkNode));
        scanf ("%d",&p->data);
        p->next = L->next;
        L->next = p;
    }
    return 0;
}


Status MergeList_LN(LinkList &La,LinkList &Lb,LinkList &Lc)//算法2.12Merge两个有序表合并为一个有序表
{
    LinkList pa,pb,pc;
    pa = La->next;
    pb = Lb->next;
    pc = Lc;
    while (pa&&pb)
    {
        if (pa->data<=pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;
    return OK;
}

//定义双向链表
typedef struct DLinkNode
{
    struct DLinkNode *pre;
    ElemType data;
    struct DLinkNode *next;
}DLinkNode;



int main()
{
/*
    LinkList L;
    InitList_LN(L);
    int a[5]={3,5,7,11,13};
    ElemType e;
    for(int i=0;i<5;i++)
    {
        e = a[i];
        AddElem_LN(L,e);//测试添加数据
    }
    PrintList_LN(L);
    int i = 1;
    printf("GetElem:序号%d，数值%d\n",i,GetElem_LN(L,i));//测试按序号数据

    //测试插入数据
    i=4,e=17;
    ListInsert_LN(L,4,17);
    PrintList_LN(L);
    printf("ListInsert_LN:序号%d，数值%d\n",i,e);

    //测试删除数据
    i=3;
    e = ListDelete_LN(L,i);
    PrintList_LN(L);
    printf("ListDelete_LN:序号%d，数值%d\n",i,e);

    //测试逆向建立单链表
    LinkList L2;
    CreateList_LN(L2,5);
    PrintList_LN(L2);
*/
    //测试Merge
    LinkList La,Lb,Lc;
    InitList_LN(La);
    InitList_LN(Lb);
    InitList_LN(Lc);

    int a[7]={1,2,11,13,29,43,47};
    int b[7]={3,5,17,19,31,37,41};
    for (int i=0;i<7;i++)
    {
        AddElem_LN(La,a[i]);
        AddElem_LN(Lb,b[i]);
    }
    printf("La:\n");
    PrintList_LN(La);
    printf("Lb:\n");
    PrintList_LN(Lb);

    MergeList_LN(La,Lb,Lc);
    printf("Lc:\n");
    PrintList_LN(Lc);

    return 0;
}

