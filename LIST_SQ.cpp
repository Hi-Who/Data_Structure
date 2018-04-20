#include<stdlib.h>
#include<stdio.h>

//�����������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Satus �Ǻ����ķ������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

//���Ա�Ķ�̬����˳��洢�ṹ
typedef int ElemType;     //�������Ա��д�ŵ�����Ϊint��
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;


int PrintList_Sq(SqList L);                        //���������,��һ�б�ʾ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
Status InitList_Sq(SqList &L);                    //�㷨2.3����һ���յ�˳���L
Status DestoryList_Sq(SqList &L);                 //�������Ա�
Status ClearList_Sq(SqList &L);                   //�����Ա���Ϊ�ձ�
Status ListEmpty_Sq(SqList L);                    //�ж����Ա��Ƿ�Ϊ��,���򷵻�TRUE,���򷵻�FALSE
Status ListLength_Sq(SqList L);                   //����˳�����
Status AppendList_Sq(SqList &L,ElemType e);       //���Ա�β���������
Status GetElem_Sq(SqList L,int i,ElemType &e);    //�������Ա�ָ��λ�õ�Ԫ��
Status ListInsert_Sq(SqList &L,int i,ElemType e); //�㷨2.4˳������
Status ListDelete_Sq(SqList &L,int i,ElemType &e);//�㷨2.5ɾ��˳����еĵ�i��Ԫ�أ�����e����

//�㷨2.6�ж�һ��Ԫ���Ƿ������Ա���,���򷵻ص�һ����e��ƥ�����ţ����򷵻�0
int compare(ElemType a,ElemType b); //�㷨2.6�ж���Ҫ�õ���compare����
int LocateElem_Sq(SqList L,ElemType e);

//��ȡ���Ա���һ��Ԫ�ص�ֱ��ǰ��
ElemType PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e);

//��ȡ���Ա���һ��Ԫ�ص�ֱ�Ӻ��
ElemType NextElem_Sq(SqList L,ElemType cur_e,ElemType &next_e);

int union_Sq(SqList &La,SqList Lb);              //�㷨2.1�������Ա�ϲ�������La��Lb�Ĳ���
int MergeList_Sq(SqList La,SqList Lb,SqList &Lc);//�㷨2.2���Ա�La��Lb�����ݷǵݼ����У��鲢La��Lb�õ�Lc��Ϊ�ǵݼ�����


int main()
{
    SqList L;                                          //�����ձ�
    Status S;                                          //״ָ̬ʾ
    //��ʼ�����жϳ�ʼ�����Ƿ����
    S = InitList_Sq(L);
    if(S!= OK)
    {
        printf("InitList_Sq: ��ʼ��ʧ�ܣ�����\n");
        return -1;
    }
    //��Ӳ�������
    for (int i=1;i<=6;i++)
        AppendList_Sq(L,i);
    //�������ݲ��������Ƿ����
    S = ListInsert_Sq(L,1,10);
    if(S!= OK)
    {
        printf("ListInsert_Sq����������ʧ�ܣ�����\n");
        return -1;
    }
    //��ȡ��nλ����
    int n=1;
    ElemType e=0;
    GetElem_Sq(L,n,e);
    printf("��ȡ���ݳɹ�����%dλ����Ϊ%d\n",n,e);
    PrintList_Sq(L);

    //����ɾ������
    n=5;
    ListDelete_Sq(L,n,e);
    printf("��%dλ����%d�ѳɹ�ɾ��\n",n,e);

    //���ݶ�λ����
    e = 60;
    n = LocateElem_Sq(L,e);
    printf("��һ��%d�����Ϊ%d\n",e,n);
    PrintList_Sq(L);

    //����Ѱ��ǰ������
    ElemType pre_e,next_e;
    e = 6;
    PriorElem_Sq(L,e,pre_e);
    NextElem_Sq(L,e,next_e);
    printf("����%d��ǰһ��Ԫ����%d����һ��Ԫ����%d\n",e,pre_e,next_e);

    //����union
    //����merge
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


//���������,��һ�б�ʾ���
int PrintList_Sq(SqList L)
{
    printf("\n-------------------\n");
    int i;
    for (i=1;i<=L.length;i++)
        printf("%4d    %4d\n",i,L.elem[i-1]);
    printf("-------------------\n");
    return 0;
}
//�㷨2.3����һ���յ�˳���L
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

//�������Ա�
Status DestoryList_Sq(SqList &L)
{
    L.length = 0;
    L.listsize = 0;//
    return OK;
}

//�����Ա���Ϊ�ձ�
Status ClearList_Sq(SqList &L)
{
    L.length = 0;
    return OK;
}

//�ж����Ա��Ƿ�Ϊ��
//���򷵻�TRUE,���򷵻�FALSE
Status ListEmpty_Sq(SqList L)
{
    return (L.length==0)?TRUE:FALSE;
}

//����˳�����
int  ListLength_Sq(SqList L)
{
    return L.length;
}

//���Ա�β���������
Status AppendList_Sq(SqList &L,ElemType e)
{
    //�����жϱ�ռ乻����������������
    ElemType *newbase;
    if (L.length >= L.listsize)
    {
        newbase = (ElemType *) realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(ERROR);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    //��ʼ�������
    L.elem[L.length] = e;
    L.length++;
    return OK;
}

//�������Ա�ָ��λ�õ�Ԫ��
Status GetElem_Sq(SqList L,int i,ElemType &e)
{
    //�ж�i�Ƿ��ڱ�Χ��
    if (i<0 || i>L.length)
    {
        printf("��ȡԪ��ʧ�ܣ�ָ��λ�ò��ڷ�Χ��\n");
        return ERROR;
    }
    //��ȡԪ�ز�����
    e = L.elem[i-1];
    return OK;
}

//�㷨2.4˳������
Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
    if (i<1||i>L.length+1)
        return ERROR;
    //����洢�ռ������������ӷ���
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

//�㷨2.5ɾ��˳����еĵ�i��Ԫ�أ�����e����
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

//�㷨2.6�ж�һ��Ԫ���Ƿ������Ա���,���򷵻ص�һ����e��ƥ�����ţ����򷵻�0
//�ж���Ҫ�õ���compare����
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

//��ȡ���Ա���һ��Ԫ�ص�ֱ��ǰ��
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

//��ȡ���Ա���һ��Ԫ�ص�ֱ�Ӻ��
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

//�㷨2.1�������Ա�ϲ�������La��Lb�Ĳ���
int union_Sq(SqList &La,SqList Lb)
{
    //�ж�Lb��Ԫ���Ƿ���La�ڣ����������
    int i,La_len,Lb_len;
    La_len = ListLength_Sq(La);
    Lb_len = ListLength_Sq(Lb);
    ElemType e;

    for (i=1;i<=Lb_len;i++)
    {
        GetElem_Sq(Lb,i,e);
        if (!LocateElem_Sq(La,e))//locate����0��˵������La��
            ListInsert_Sq(La,++La_len,e);
    }
    return OK;
}

//�㷨2.2���Ա�La��Lb�����ݷǵݼ����У��鲢La��Lb�õ�Lc��Ϊ�ǵݼ�����
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
