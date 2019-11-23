#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int Status;   //将Status定义成int类型
typedef int ElemType; //将ElemType定义成int类型

typedef struct LNode //将Lode定义成struct类型
{
    ElemType data;      //定义结点的数据域
    struct LNode *next; //定义结点的指针域
} LNode, *LinkList;     //LinkList为指向结构体LNode的指针类型

Status InitList_L(LinkList *L) //单链表的初始化
{
    (*L) = (LinkList)malloc(sizeof(LNode)); //生成新结点作为头结点,用头指针L指向头结点,数据域会默认为0
    (*L)->next = NULL;                      //头结点的指针域置空
    return OK;
}

// LinkList InitList_L() //单链表的初始化
// {
//     LinkList L; //单链表的头指针
//     L = (LinkList)malloc(sizeof(LNode));
//     if (L == NULL)
//         return NULL;
//     L->next = NULL;
//     return L;
// }

Status GetElem_L(LinkList L, int i, ElemType *e) //按序号查找
{
    int j;
    LNode *p;
    if (L == NULL)
    {
        printf("未初始化，请先初始化\n");
        return ERROR;
    }
    p = L->next;       //p指向第一个结点
    j = 1;             //j为计数器
    while (j < i && p) //i为查找序号的位置,顺链域向后扫描,直到p指向第i个元素或p为空
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR; //第i个元素不存在
    *e = p->data;     //取第i个元素,并将值给e
    return OK;
}

LNode *LocateElem_L(LinkList L, ElemType e) //按值查找
{
    LNode *p;
    if (L == NULL) //判断链表是否为空
    {
        printf("未初始化，请先初始化\n");
        return NULL;
    }
    p = L->next;              //现将链表L的数据导进去,因为L有头结点(data=0),所以用L->next
    while (p && p->data != e) //当p不等于e且p不为空时(相当于p!=NULL)
        p = p->next;          //让p的next指针域等于p
    return p;
}

Status ListInsert_L(LinkList L, int i, ElemType e) //单链表的插入
{
    int j;
    LNode *p, *s; //定义两个链表
    if (L == NULL)
    { //当链表为空时,初始化
        printf("未初始化，请先初始化\n");
        return ERROR;
    }
    p = L;                 //把L的链表赋值给p
    j = 0;                 //j的作用是计数,把j初始化
    while (p && j < i - 1) //p不为空(相当于p!=NULL),且j小于i-1(因为有头结点所以要i-1)
    {
        p = p->next; //p指向p的下一个结点
        ++j;
    }
    if (!p || j > i - 1) //如果(表长小于1)或者(大于(表长+1))
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode)); //为s定义新的空间
    s->data = e;                         //将e的数据放到s链表的数据域
    s->next = p->next;                   //使新插入的数据与p结合,形成新的s链表
    p->next = s;                         //最后将新建的s链表插入原链表p中
    return OK;
}

Status ListDelete_L(LinkList L, int i, ElemType *e) //单链表的删除,将要删除的数据域的前一个结点与其断开并插入新的链表
{
    //带头结点的单链表L中,删除第i个位置,并由e返回值
    LNode *p, *q;
    int j;
    if (L == NULL)
    {
        printf("未初始化，请先初始化\n");
        return ERROR;
    }
    p = L;
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

LinkList CreateList_L(LinkList L, int n) //后插法创建链表
{
    //正位序输入n个元素的值,建立到头结点的单链表L上
    LNode *r, *p;
    int i;
    if (L == NULL) //判断链表L是否为空
    {
        printf("未初始化，请先初始化\n");
        return NULL;
    }
    r = L; //尾指针r指向头结点
    printf("请输入%d个数\n", n);
    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(LNode)); //生成新的结点
        scanf("%d", &p->data);               //输入元素值 (1)
        p->next = NULL;                      //插入到表尾 (2)
        r->next = p;                         //(1),(2)为建立数据域的过程,并将它插入链表r中
        r = p;                               //r指向新的尾结点
    }
    return L;
}

int main()
{
    int res, a, b, choose;
    LNode *L = NULL, *p;
    printf("1.初始化链表\n");
    printf("2.输入数据\n");
    printf("3.按位置查找\n");
    printf("4.按值查找\n");
    printf("5.链表的插入\n");
    printf("6.链表的删除\n");
    printf("7.输出数据\n");
    printf("0.退出\n \n");
    choose = -1;
    while (choose != 0)
    {
        printf("请选择:");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1: //初始化链表
            InitList_L(&L);
            //L =InitList_L();
            if (L != NULL)
                printf("初始化链表成功!\n\n");
            else
                printf("初始化链表失败!\n\n");
            break;
        case 2:
            L = CreateList_L(L, 10);
            if (L != NULL)
                printf("输入数据成功!\n\n");
            else
                printf("输入数据失败!\n\n");
            break;
        case 3:
            printf("请输入一个位置用来查找:");
            scanf("%d", &a);
            if (GetElem_L(L, a, &res))
                printf("查找成功！第%d个数是%d\n\n", a, res);
            else
                printf("查找失败!\n\n");
            break;
        case 4:
            printf("请输入一个数值用来查找:");
            scanf("%d", &b);
            if (LocateElem_L(L, b) != NULL)
                printf("查找成功\n\n");
            else
                printf("查找失败!%d没有找到\n\n", b);
            break;
        case 5:
            printf("请输入两个数分别代表插入的位置和数值:");
            scanf("%d%d", &a, &b);
            if (ListInsert_L(L, a, b))
                printf("成功将%d插在%d个位置\n\n", b, a);
            else
                printf("插入失败!\n\n");
            break;
        case 6:
            printf("请输入一个位置来删除:");
            scanf("%d", &a);
            if (ListDelete_L(L, a, &res))
                printf("删除成功!被删除的数是:%d\n\n", res);
            else
                printf("删除失败!\n\n");
            break;
        case 7:
            printf("现在链表里的数分别是:\n");
            p = L;
            if (p == NULL)
                printf("未初始化！\n");
            else
            {
                p = L->next;
                while (p)
                {
                    printf("%d ", p->data);
                    p = p->next;
                }
                printf("\n\n");
            }
            break;
        default:
            if (choose != 0)
                printf("请输入正确数字\n");
        }
    }
    return 0;
}
