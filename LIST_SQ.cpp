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

//线性表的动态分配顺序存储结构
typedef int ElemType;     //假设线性表中存放的数据为int型
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;


int PrintList_Sq(SqList L);                        //输出表内容,第一列表示序号
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
Status InitList_Sq(SqList &L);                    //算法2.3构造一个空的顺序表L
Status DestoryList_Sq(SqList &L);                 //销毁线性表
Status ClearList_Sq(SqList &L);                   //将线性表置为空表
Status ListEmpty_Sq(SqList L);                    //判断线性表是否为空,是则返回TRUE,否则返回FALSE
Status ListLength_Sq(SqList L);                   //返回顺序表长度
Status AppendList_Sq(SqList &L,ElemType e);       //线性表尾部添加数据
Status GetElem_Sq(SqList L,int i,ElemType &e);    //返回线性表指定位置的元素
Status ListInsert_Sq(SqList &L,int i,ElemType e); //算法2.4顺序表插入
Status ListDelete_Sq(SqList &L,int i,ElemType &e);//算法2.5删除顺序表中的第i个元素，并用e返回

//算法2.6判断一个元素是否在线性表中,在则返回第一个与e相匹配的序号，否则返回0
int compare(ElemType a,ElemType b); //算法2.6判断需要用到的compare函数
int LocateElem_Sq(SqList L,ElemType e);

//获取线性表中一个元素的直接前驱
ElemType PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e);

//获取线性表中一个元素的直接后继
ElemType NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e);

int union_Sq(SqList &La,SqList Lb);              //算法2.1两个线性表合并，计算La和Lb的并集
int MergeList_Sq(SqList La,SqList Lb,SqList &Lc);//算法2.2线性表La和Lb中数据非递减排列，归并La和Lb得到Lc仍为非递减排列


int main()
{
    SqList L;                                          //创建空表
    Status S;                                          //状态指示
    //初始化表并判断初始化表是否出错
    S = InitList_Sq(L);
    if(S!= OK)
    {
        printf("InitList_Sq: 初始化失败！！！\n");
        return -1;
    }
    //添加测试数据
    for (int i=1;i<=6;i++)
        AppendList_Sq(L,i);
    //插入数据并检查插入是否出错
    S = ListInsert_Sq(L,1,10);
    if(S!= OK)
    {
        printf("ListInsert_Sq：插入数据失败！！！\n");
        return -1;
    }
    //读取第n位数据
    int n=1;
    ElemType e=0;
    GetElem_Sq(L,n,e);
    printf("获取数据成功，第%d位数据为%d\n",n,e);
    PrintList_Sq(L);

    //数据删除测试
    n=5;
    ListDelete_Sq(L,n,e);
    printf("第%d位数据%d已成功删除\n",n,e);

    //数据定位测试
    e = 60;
    n = LocateElem_Sq(L,e);
    printf("第一个%d的序号为%d\n",e,n);
    PrintList_Sq(L);

    //测试寻找前驱或后继
    ElemType pre_e,next_e;
    e = 6;
    PriorElem_Sq(L,e,pre_e);
    NextElem_Sq(L,e,next_e);
    printf("数据%d的前一个元素是%d，后一个元素是%d\n",e,pre_e,next_e);

    //测试union
    //测试merge
    int a[5] = {1,3,5,7,9},b[5] = {0,3,4,7,8};
    SqList La,Lb,Lc;
    InitList_Sq(La);
    InitList_Sq(Lb);
    InitList_Sq(Lc);
    for (int i=1;i<=5;i++)
    {
        ListInsert_Sq(La,i,a[i-1]);
        ListInsert_Sq(Lb,i,b[i-1]);
    }
    printf("La:--\n");
    PrintList_Sq(La);
    printf("Lb:--\n");
    PrintList_Sq(Lb);

    MergeList_Sq(La,Lb,Lc);
    union_Sq(La,Lb);

    printf("Lc:--\n");
    PrintList_Sq(Lc);
    printf("La:--\n");
    PrintList_Sq(La);

    return 0;
}


//输出表内容,第一列表示序号
int PrintList_Sq(SqList L)
{
    printf("\n-------------------\n");
    int i;
    for (i=1;i<=L.length;i++)
        printf("%4d    %4d\n",i,L.elem[i-1]);
    printf("-------------------\n");
    return 0;
}
//算法2.3构造一个空的顺序表L
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

//销毁线性表
Status DestoryList_Sq(SqList &L)
{
    L.length = 0;
    L.listsize = 0;//
    return OK;
}

//将线性表置为空表
Status ClearList_Sq(SqList &L)
{
    L.length = 0;
    return OK;
}

//判断线性表是否为空
//是则返回TRUE,否则返回FALSE
Status ListEmpty_Sq(SqList L)
{
    return (L.length==0)?TRUE:FALSE;
}

//返回顺序表长度
int  ListLength_Sq(SqList L)
{
    return L.length;
}

//线性表尾部添加数据
Status AppendList_Sq(SqList &L,ElemType e)
{
    //首先判断表空间够不够，不够就增加
    ElemType *newbase;
    if (L.length >= L.listsize)
    {
        newbase = (ElemType *) realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(ERROR);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    //开始添加数据
    L.elem[L.length] = e;
    L.length++;
    return OK;
}

//返回线性表指定位置的元素
Status GetElem_Sq(SqList L,int i,ElemType &e)
{
    //判断i是否在表范围内
    if (i<0 || i>L.length)
    {
        printf("获取元素失败，指定位置不在范围内\n");
        return ERROR;
    }
    //获取元素并返回
    e = L.elem[i-1];
    return OK;
}

//算法2.4顺序表插入
Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
    if (i<1||i>L.length+1)
        return ERROR;
    //如果存储空间已满，则增加分配
    ElemType *newbase,*p,*q;
    if (L.length >= L.listsize)
    {
        newbase = (ElemType *) realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(ERROR);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }

    q = &(L.elem[i-1]);
    for (p=&L.elem[L.length-1];q<=p;p--)
        *(p+1)=*p;
    *q = e;
    L.length++;
//    printf("%d\n",L.length);
    return OK;
}

//算法2.5删除顺序表中的第i个元素，并用e返回
Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
    if (i<1||i>L.length)
        return ERROR;
    ElemType *p,*q;
    q = &L.elem[i-1];
    e = *q;
    for (p = &L.elem[L.length-1];q<p;q++)
        *q=*(q+1);
    L.length--;
    return OK;
}

//算法2.6判断一个元素是否在线性表中,在则返回第一个与e相匹配的序号，否则返回0
//判断需要用到的compare函数
int compare(ElemType a,ElemType b)
{
    if (a!=b)
        return 0;
    return 1;
}
int LocateElem_Sq(SqList L,ElemType e)
{
    int i=1;
    ElemType *p;
    p = L.elem;
    while (i<=L.length && !compare(e,*p++))
        i++;
    return (i<=L.length)?i:0;
}

//获取线性表中一个元素的直接前驱
Status PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e)
{
    int i;
    i = LocateElem_Sq(L,cur_e);
    if (i==0)
        return ERROR;
    else
        if (i>1)
            pre_e = L.elem[i-2];
    return OK;
}

//获取线性表中一个元素的直接后继
Status NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e)
{
    int i;
    i = LocateElem_Sq(L,cur_e);
    if (i==0)
        return ERROR;
    else
        if (i<L.length)
            next_e = L.elem[i];
    return OK;
}

//算法2.1两个线性表合并，计算La和Lb的并集
int union_Sq(SqList &La,SqList Lb)
{
    //判断Lb中元素是否在La内，不再则插入
    int i,La_len,Lb_len;
    La_len = ListLength_Sq(La);
    Lb_len = ListLength_Sq(Lb);
    ElemType e;

    for (i=1;i<=Lb_len;i++)
    {
        GetElem_Sq(Lb,i,e);
        if (!LocateElem_Sq(La,e))//locate返回0则说明不在La内
            ListInsert_Sq(La,++La_len,e);
    }
    return OK;
}

//算法2.2线性表La和Lb中数据非递减排列，归并La和Lb得到Lc仍为非递减排列
int MergeList_Sq(SqList La,SqList Lb,SqList &Lc)
{
    int i,j,k,La_len,Lb_len;
    i = 1;
    j = 1;
    k = 0;
    ElemType ai,bj;
    La_len = ListLength_Sq(La);
    Lb_len = ListLength_Sq(Lb);
    while (i<=La_len && j<=Lb_len)
    {
        GetElem_Sq(La,i,ai);
        GetElem_Sq(Lb,j,bj);
        if (ai<bj)
        {
            ListInsert_Sq(Lc,++k,ai);
            i++;
        }
        else
        {
            ListInsert_Sq(Lc,++k,bj);
            j++;
        }
    }
    while (i<=La_len)
    {
        GetElem_Sq(La,i,ai);
        ListInsert_Sq(Lc,++k,ai);
        i++;
    }
    while (j<=Lb_len)
    {
        GetElem_Sq(Lb,j,bj);
        ListInsert_Sq(Lc,++k,bj);
        j++;
    }
    return OK;
}
