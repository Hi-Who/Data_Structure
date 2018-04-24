#include<stdlib.h>
#include<stdio.h>

//�����������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//compare()��������ֵ
typedef enum CompareStatus
{EQUAL,GREATER,LESS}CPS;
//Satus �Ǻ����ķ������ͣ���ֵ�Ǻ������״̬����
typedef int Status;

typedef int ElemType;     //�������Ա��д�ŵ�����Ϊint��

//����˫��������DoubleLinkNode
typedef struct LN
{
    struct LN *prior;
    ElemType data;
    struct LN *next;
}LN,*Link,*Position;

//����˫������DoubleLinkList
typedef struct
{
    Link head,tail;      //�ֱ�ָ��ͷ�������һ�����
    int length;          //��������ĳ���
}LinkList;

Status PrintList(LinkList L);//�������
Status MakeNode(Link &L,ElemType e);//������pָ���ֵΪ�Ľ�㣬������OK��ʧ���򷵻�ERROR
Status FreeNode(Link &p);//�ͷ�p��ָ�Ľ��
Status InitList(LinkList &L);//����һ���յ����Ա�
Status DestoryList(LinkList &L);//�������Ա�L
Status ClearList(LinkList &L);//������L��Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
Status InsFirst(LinkList &L,Link s);//��֪hΪͷ��㣬��s��ָ�����뵽��һ�����֮ǰ
Status DelFirst(LinkList &L,Link &q);//hΪͷ��㣬ɾ������ĵ�һ����㲢��q����
Status Append(LinkList &L,Link s);//��sָ���һ��������ӵ�L�����һ������ϣ�����L��βָ��ָ���µ�β���
Status Remove(LinkList &L,Link &q);//ɾ��������L��β��㲢��q���أ��ı�L��βָ��ָ���µ�β���
Status InsBefore(LinkList &L,Link &p,Link s);//һֱpΪ����L�е�һ����㣬��sָ��Ľ����뵽p��ָ֮ǰ�����޸�pָ��Ϊ�½ڵ�
Status InsAfter(LinkList &L,Link &p,Link s);//һֱpΪ����L�е�һ����㣬��sָ��Ľ����뵽p��ָ֮�󣬲��޸�pָ��Ϊ�½ڵ�
Status SetCurElem(Link &p,ElemType e);//��֪pָ��������һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
Status ListEmpty(LinkList L);//������Ϊ�շ���TRUE�����򷵻�FALSE
int ListLength(LinkList L);//��������������Ԫ�صĸ���
Position GetHead(LinkList L);//������������Lͷ����λ��
Position GetLast(LinkList L);//������������L���һ������λ��
Position PriorPos(LinkList L,Link p);//pָ��L��ĳһ����㣬����p��ָ�����ֱ��ǰ�������򷵻�NULL
Position NextPos(LinkList L,Link p);//pָ��L��ĳһ����㣬����p��ָ�����ֱ�Ӻ�̣����򷵻�NULL
Status LocatePos(LinkList L,int i,Link &p);//��i��Ԫ�ص�λ����p��ʾ������OK��iֵ���Ϸ�����ERROR
//������������L�е�һ����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã����������򷵻�NULL
Position LocateElem(LinkList L,ElemType e,CPS S);
Status compare(ElemType a,ElemType b);
Status ListTraverse(LinkList L,Status (* visit)());//���ζ�L��ÿһ��Ԫ�ص���visit(),һ��visit()ʧ�ܣ������ʧ��

int main()
{
    LinkList La,Lb,Lc;
    InitList(La);//��ʼ������
    InitList(Lb);
    InitList(Lc);
    Link p;
    int a[5] = {1,3,5,7,9};
    int b[5] = {8,6,4,2,0};
    int c[5] = {0,2,4,6,8};
    for (int i=0;i<5;i++)
    {
        MakeNode(p,a[i]);//�������Ԫ��
        Append(La,p);
        MakeNode(p,b[i]);
        Append(Lb,p);
        MakeNode(p,c[i]);
        Append(Lc,p);
    }
    printf("La:\n");//�鿴��������
    PrintList(La);
    printf("Lb:\n");
    PrintList(Lb);
    printf("Lc:\n");
    PrintList(Lc);
if (0)
{
    //����InsFirst
    Link s,q;
    MakeNode(s,123);
    InsFirst(Lc,s);
    printf("Lc:\n");
    PrintList(Lc);

    //����LocatePos(),InsAfter()
    MakeNode(s,1212);
    LocatePos(Lc,3,q);
    printf("q:%x\n",q);
    InsAfter(Lc,q,s);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%x\n",q);

    //����InsBefore()
    MakeNode(s,2333);
    InsBefore(Lc,q,s);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%x\n",q);

    //����DelFirst()
    DelFirst(Lc,q);
    printf("Lc:\n");
    PrintList(Lc);
    printf("q:%d\n",q->data);

    //����Append
    Append(La,Lb.head->next);
    printf("La:\n");
    PrintList(La);
    //����Remove
    Link p2,p3;
    Remove(La,p2);
    printf("La:\n");
    PrintList(La);
    printf("Remove:%d\n",p2->data);
    //����SetCurElem
    LocatePos(La,5,p2);
    SetCurElem(p2,110);
    printf("La:\n");
    PrintList(La);
    //����PriorPos
    p3 = PriorPos(La,p2);
    printf("La:\n");
    PrintList(La);
    printf("%x\n",p3);
    //����NextPos()
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

Status MakeNode(Link &p,ElemType e)//������pָ���ֵΪ�Ľ�㣬������OK��ʧ���򷵻�ERROR
{
    p = (Link)malloc(sizeof(LN));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->prior = NULL;
    p->next = NULL;
    return OK;
}

Status FreeNode(Link &p)//�ͷ�p��ָ�Ľ��
{
    free(p);
    return OK;
}

Status InitList(LinkList &L)//����һ���յ����Ա�
{
    Link p;//����һ������С�Ŀռ���Ϊͷ���
    p = (Link)malloc(sizeof(LN));
    if(!p) exit(OVERFLOW);
    p->prior = NULL;
    p->next = NULL;
    L.head = p;
    L.tail = NULL;
    L.length = 0;
    return OK;
}

Status DestoryList(LinkList &L)//�������Ա�L
{
    ClearList(L);
    free(&L);
    return OK;
}
Status ClearList(LinkList &L)//������L��Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
{
    Link q;
    q = L.tail;
    while(L.length)//ɾ�����һ��Ԫ�أ�ֱ��Ԫ�ظ���Ϊ0
    {
        //Remove(L,q)Ҳ���ԣ�����û���ͷ�ɾ���Ľ��
        q->prior->next = q->next;//����˫��ѭ������
        q = q->prior;
        free(q->next);
        L.length--;
    }
    L.tail = q;
    return OK;
}

Status InsFirst(LinkList &L,Link s)//��s��ָ�����뵽��һ�����֮ǰ,�˴������ϲ�ͬ
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
Status DelFirst(LinkList &L,Link &q)//ɾ������ĵ�һ����㲢��q����
{
    Link h;
    h = L.head;
    q = h->next;
    h->next = h->next->next;
    L.length--;
    return OK;
}

Status Append(LinkList &L,Link s)//��sָ���һ��������ӵ�L�����һ������ϣ�����L��βָ��ָ���µ�β���
{
    //��s�ӵ�Lβ��
    Link p,q;
    p = GetLast(L);
    p->next = s;
    s->prior = p;

    //βָ���ƶ�,������
    q = p;
    while (q->next)
    {
        q = q->next;
        L.length++;
    }
    L.tail = q;
    return OK;
}
Status Remove(LinkList &L,Link &q)//ɾ��������L��β��㲢��q���أ��ı�L��βָ��ָ���µ�β���
{
    if(L.length==0) return ERROR;
    Link t;
    t = L.tail;
    q = t;
    t->prior->next = t->next;//�����ڶ���Ԫ�ص�nextָ���Ϊ���һ��Ԫ�ص�next������˫��ѭ������
    L.tail = t->prior;
    L.length--;
    return  OK;
}
Status InsBefore(LinkList &L,Link &p,Link s)//һֱpΪ����L�е�һ����㣬��sָ��Ľ����뵽p��ָ֮ǰ�����޸�pָ��Ϊ�½ڵ�
{
    s->next = p->prior->next;
    s->prior = p->prior;
    p->prior->next = s;
    p->prior = s;
    p = s;
    L.length++;
    return OK;
}

Status InsAfter(LinkList &L,Link &p,Link s)//һֱpΪ����L�е�һ����㣬��sָ��Ľ����뵽p��ָ֮�󣬲��޸�pָ��Ϊ�½ڵ�
{
    s->next = p->next;
    s->prior = p;
    p->next->prior = s;
    p->next = s;
    p = s;
    L.length++;
    if(p->prior == L.tail)//�²�����Ϊ���һ�����
        L.tail = p;
    return OK;
}

Status SetCurElem(Link &p,ElemType e)//��֪pָ��������һ����㣬��e����p��ָ���������Ԫ�ص�ֵ
{
    p->data = e;
    return OK;
}

Status ListEmpty(LinkList L)//������Ϊ�շ���TRUE�����򷵻�FALSE
{
    return (L.length)?FALSE:TRUE;
}

int ListLength(LinkList L)//��������������Ԫ�صĸ���
{
    return L.length;
}

Position GetHead(LinkList L)//������������Lͷ����λ��
{
    return L.head;
}

Position GetLast(LinkList L)//������������L���һ������λ��
{
    if(L.length==0) return L.head;//���Ա�Ϊ�ձ�
    return L.tail;
}

Position PriorPos(LinkList L,Link p)//pָ��L��ĳһ����㣬����p��ָ�����ֱ��ǰ�������򷵻�NULL
{
    if(p!= L.head->next)
    {
        p = p->prior;
    }

    else
        p = NULL;
    return p;
}
Position NextPos(LinkList L,Link p)//pָ��L��ĳһ����㣬����p��ָ�����ֱ�Ӻ�̣����򷵻�NULL
{
    if (p!= L.tail)
        p = p->next;
    else
        p = NULL;
    return p;
}

Status LocatePos(LinkList L,int i,Link &p)//��i��Ԫ�ص�λ����p��ʾ������OK��iֵ���Ϸ�����ERROR
{
    if(i<1 || i>L.length) return ERROR;
    int j;
    p = L.head;
    for(j=0;j<i;j++)
        p = p->next;
    return OK;
}
//������������L�е�һ����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã����������򷵻�NULL
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

Status ListTraverse(LinkList L,Status (* visit)());//���ζ�L��ÿһ��Ԫ�ص���visit(),һ��visit()ʧ�ܣ������ʧ��
