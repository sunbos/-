#include <stdio.h>
#include <stdlib.h> //一些宏和通用工具函数
#define OK 1;
#define ERROR 0;
//#define OVERFLOW -2;
typedef int Status;
//typedef int ElemType;

typedef struct
{
    int no;    //学号
    char name; //姓名
    int jyz;   //经验值
} ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

Status InitList_L(LinkList *L) //线性表的初始化
{
    //构造一个空的单链表
    (*L) = (LinkList)malloc(sizeof(LNode)); //函数功能: 分配 size 字节的存储区,函数返回: 所分配的内存区地址,如果内存不够,返回0
    (*L)->next = NULL;
    return OK;
}

LNode *LocateElem_L(LinkList L, ElemType e) //按元素值查找
{
    //在带头结点的单链表L中查找值为e的元素
    LNode *p;
    p = L->next;
    while (p && p->data.no != e.no)
        p = p->next; //寻找满足条件的结点
    return p;        //返回L中的值为e的数据元素的位置，查找失败返回NULL
}

Status ListInsert_L(LinkList *L, int i, ElemType *e) //单链表的插入
{
    //在带头结点的单链表L中第i个位置之前插入元素e
    int j;
    LNode *p, *s;
    p = (*L);
    j = 0;
    while (p && j < i - 1) //寻找第i-1个节点
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) //i大于表长+1或者小于1
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode)); //生成新节点s
    s->data = (*e);                      //将结点的数据域置为e
    s->next = p->next;                   //将结点s插入L中
    p->next = s;
    return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e) //单链表的删除,将要删除的数据域的前一个结点与其断开并插入新的链表
{
    //在带头结点的单链表L中，删除第i个位置，并由e返回值
    LNode *p, *q;
    int j;
    p = (*L);
    j = 0;
    while (p->next && j < i - 1) //寻找i-1个结点
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1) //i大于表长+1或者小于1
        return ERROR;
    q = p->next;       //临时保存被删结点的地址以备释放
    p->next = q->next; //改变删除结点前驱结点的指针域
    *e = q->data;      //保存删除结点的数据域
    free(q);           //释放删除结点的空间
    return OK;
}

void CreateList_L(LinkList *L, int n) //后插法创建链表
{
    //正位序输入n个元素的值，建立到头结点的单链表L
    LNode *r, *p;
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL; //先建立一个带头结点的空链表
    r = (*L);
    scanf("请输入%d个数:\n", &n);
    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(LNode)); //生成新的结点
        scanf("%d", &p->data.no);            //输入元素值 (1)
        p->next = NULL;                      //插入到表尾 (2)
        r->next = p;                         //(1),(2)为建立数据域的过程,并将它插入链表r中
        r = p;                               //r指向新的尾结点
    }
}

int jia(LinkList *L, ElemType e, int jyz) //为学生e增加经验值jyz
{
    LNode *p;
    p = (*L)->next;
    while (p && p->data.no != e.no) //p不为空,并且查找满足条件的序号(p->data.no!=e.no),匹配到如果相等就退出循环
    {
        p = p->next; //指向下一个数据域,寻找满足条件的结点
    }
    if (!p)
        return 0;
    else
    {
        p->data.jyz = p->data.jyz + jyz; //找到后将经验值加进去
        return 1;
    }
}

int jian(LinkList *L, ElemType e, int jyz) //为学生e减少经验值jyz
{
    LNode *p;
    p = (*L)->next;
    while (p && p->data.no != e.no) //p不为空,并且查找满足条件的序号(p->data.no!=e.no),匹配到如果相等就退出循环
    {
        p = p->next; //指向下一个数据域,寻找满足条件的结点
    }
    if (!p)
        return 0;
    else
    {
        p->data.jyz = p->data.jyz - jyz; //找到后将经验值减进去
        return 1;
    }
}

int main()
{
    LinkList L = NULL;
    ElemType res, b;
    LNode *p;
    int i = 0, temp = 0, a, c, choose, n, jyz;
    printf("课堂经验值管理系统\n");
    printf("1.建立学生信息表\n");
    printf("2.输入学生数据\n");
    printf("3.按学号查找学生经验值\n");
    printf("4.插入新同学信息\n");
    printf("5.删除离班同学信息\n");
    printf("6.输出全部同学信息\n");
    printf("7.为某学号同学加指定经验值\n");
    printf("8.为某学号同学减指定经验值\n");
    printf("0.退出\n\n");

    choose = -1;
    while (choose != 0)
    {
        printf("\n请选择:");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            if (InitList_L(&L))
            {
                printf("成功建立学生信息表\n");
            }
            else
            {
                printf("学生信息表建立失败\n");
            }
            break;
        case 2:
            printf("请输入学生人数");
            scanf("%d", &n);
            printf("请输入%d个学生信息:\n", n);
            printf("学号  姓名  经验值\n");
            for (i = 1; i <= n; i++)
            {
                scanf("%d", &b.no);
                scanf("%s", &b.name);
                scanf("%d", &b.jyz);
                ListInsert_L(&L, i, &b);
            }
            break;
        case 3:
            printf("请输入所要查找的学生学号");
            scanf("%d", &b.no);
            if (LocateElem_L(L, b) != NULL) //元素查找
            {
                printf("查找成功\n%d学生的经验值是%d.\n", b.no, LocateElem_L(L, b)->data.jyz);
            }
            else
                printf("查找失败!%d没有找到\n\n", b.no);
            break;
        case 4:
            printf("请输入要插入的新同学的信息:\n");
            printf("插入的位置   学号  姓名  经验值:\n");
            scanf("%d%d%s%d", &a, &b.no, &b.name, &b.jyz);
            if (ListInsert_L(&L, a, &b)) //元素插入
            {
                printf("插入成功.\n");
            }
            else
            {
                printf("插入失败.\n");
            }
            break;
        case 5:
            printf("请输入所要删除的离班学生的位置:");
            scanf("%d", &c);
            if (ListDelete_L(&L, c, &res))
            {
                printf("删除成功.\n被删除离班学生是:%d %s\n", res.no, &res.name);
            }
            else
                printf("删除失败.\n");
            break;
        case 6:
            printf("当前学生信息表为:\n");
            printf("学号  姓名  经验值\n");
            p = L->next;
            while (p) //判断是否为空链表
            {
                printf("%d %s %d\n", p->data.no, &p->data.name, p->data.jyz);
                p = p->next;
            }
            break;
        case 7:
            printf("请输入所要加经验值的学生学号:");
            scanf("%d", &b.no);
            printf("请输入所要加的经验值:");
            scanf("%d", &jyz);
            temp = jia(&L, b, jyz);
            if (temp != 0)
            {
                printf("%d学生的经验值已加%d.\n", b.no, jyz);
            }
            else
            {
                printf("查找失败!没有这样的学生信息\n");
            }
            break;
        case 8:
            printf("请输入所要减检验值的学生学号:");
            scanf("%d", &b.no);
            printf("请输入所要减的经验值:");
            scanf("%d", &jyz);
            temp = jian(&L, b, jyz);
            if (temp != 0)
            {
                printf("%d学生的经验值已减%d.\n", b.no, jyz);
            }
            else
                printf("查找失败!没有这样的学生信息\n");
            break;
        }
    }
    return 0;
}
