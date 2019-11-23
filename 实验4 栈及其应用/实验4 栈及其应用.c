#include <stdio.h>
#include <stdlib.h> //一些宏和通用工具函数
#define OK 1;
#define ERROR 0;
//#define OVERFLOW -2;
typedef int Status;

typedef struct
{
    int no;        //学号
    char name[10]; //姓名
    int jyz;       //经验值
} ElemType;

typedef struct LNode
{
    ElemType data;      //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *LinkList;     //LinkList为指向结构体LNode的指针类型

typedef struct
{
    char opr; //操作
    int no;   //姓名
    int jyz;  //经验值
} SElemType;

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

Status InitStack(LinkStack *S) //链栈的初始化
{
    *S = NULL; //构造一个空栈S,将栈顶指针置空
    return OK;
}

Status Push(LinkStack *S, SElemType e) //链栈的入栈
{
    LinkStack p;
    p = (LinkStack)malloc(sizeof(StackNode)); //生成新的结点
    p->data = e;                              //将新结点数据域置位e
    p->next = *S;                             //将新结点插入栈顶
    *S = p;                                   //修改栈顶指针为p
    return OK;
}

Status Pop(LinkStack *S, SElemType *e) //删除S的栈顶元素,用e返回其值
{
    LinkStack p;
    if (S == NULL)
        return ERROR;  //如果栈空返回错误
    (*e) = (*S)->data; //将栈顶元素赋给e
    p = *S;            //用p临时保存栈顶元素空间,以备释放
    (*S) = (*S)->next; //修改栈顶指针
    free(p);           //释放原栈顶元素的空间
    return OK;
}

Status ListInsert_L(LinkList *L, int i, ElemType *e);

Status InitList_L(LinkList *L)              //单链表的初始化
{                                           //构造一个空的单链表L
    (*L) = (LinkList)malloc(sizeof(LNode)); //生成新结点作为头结点,用头指针L指向头结点
    (*L)->next = NULL;                      //头结点的指针域置空
    FILE *myfile;                           //定义文件类型
    myfile = fopen("Student.txt", "r");     //打开一个为Student.txt的文件,只读模式
    if (myfile == NULL)                     //如果文件不存在,则警告文件为空
    {
        printf("文件为空! \n");
        return OK;
    }
    ElemType e;
    int n = 1;
    while (!feof(myfile)) //相当于判断是否输入回车键,EOF
    {
        fscanf(myfile, "%d %s %d", &e.no, e.name, &e.jyz); //文件的写入操作
        ListInsert_L(L, n, &e);
        n++;
    }
    fclose(myfile); //将文件关闭,防止数据丢失
    return OK;
}

Status GetElem_L(LinkList L, int i, ElemType *e) //单链表的取值,按序号查找
{
    //在带头结点的单链表L中查找第i个元素
    int j;
    LNode *p;
    p = L->next;       //初始化,p指向第一个结点
    j = 1;             //j为计数器
    while (j < i && p) //顺链域向后扫描,直到p指向第i个元素或p为空
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i) //如果第i个元素不存在
        return ERROR;
    *e = p->data; //取第i个元素
    return OK;
}

LNode *LocateElem_L(LinkList L, ElemType e) //按值查找
{
    //在带头结点的单链表L中查找值为e的元素
    LNode *p;
    p = L->next;
    //while(p&&p->data!=e)
    while (p && p->data.no != e.no) //按学号查找
        p = p->next;                //寻找满足条件的结点
    return p;                       //返回L中的值为e的数据元素的位置,查找失败返回NULL
} //LocateElem_L;

Status jia(LinkList *L, ElemType e, int jyz) //为学生e增加经验值jyz
{
    LNode *p;
    p = (*L)->next;
    while (p && p->data.no != e.no) //p不为空,并且查找满足条件的序号(p->data.no!=e.no),匹配到如果相等就退出循环
        p = p->next;                //指向下一个数据域,寻找满足条件的结点
    if (!p)
    {
        return ERROR;
    }
    else
    {
        p->data.jyz = p->data.jyz + jyz; //找到后将经验值加进去
        return OK;
    }
}

Status jian(LinkList *L, ElemType e, int jyz) //为学生e减少经验值jyz
{
    LNode *p;
    p = (*L)->next;
    while (p && p->data.no != e.no) //p不为空,并且查找满足条件的序号(p->data.no!=e.no),匹配到如果相等就退出循环
        p = p->next;                //指向下一个数据域,寻找满足条件的结点
    if (!p)
    {
        return ERROR;
    }
    else
    {
        p->data.jyz = p->data.jyz - jyz; //找到后将经验值减进去
        return OK;
    }
}

Status ListInsert_L(LinkList *L, int i, ElemType *e) //单链表的插入
{
    //在带头结点的单链表L中第i个位置之前插入元素e
    int j;
    LNode *p, *s;
    p = *L;
    j = 0;
    while (p && j < i - 1) //寻找第i-1个节点
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) //i大于表长+1,或者小于1
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode)); //生成新节点s
    s->data = *e;                        //将结点s的数据域置为e
    s->next = p->next;                   //将结点s插入L中
    p->next = s;
    return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e) //单链表的删除
{
    //在带头结点的单链表L中,删除第i个位置,并由e返回值
    LNode *p, *q;
    int j;
    p = *L;
    j = 0;
    while (p->next && j < i - 1) //寻找第i-1个结点
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1) //i大于表长+1或者小于1
        return ERROR;
    q = p->next;       //临时保存被删结点的地址,以备释放
    p->next = q->next; //改变删除结点前驱结点的指针域
    *e = q->data;      //保存删除结点的数据域
    free(q);           //释放删除节点的空间
    return OK;
}

//void CreateList_F(LinkList *L, int n)     //前插法创建单链表
//{
//    //逆位序输入n个元素的值,建立到头结点的单链表L
//    LNode *p;
//    (*L)=(LinkList)malloc(sizeof(LNode));
//    (*L)->next=NULL;                  //先建立一个带表头结点的空链表
//    cout<<"请输入"<<n<<"个数:\n";
//    for (int i = n;i > 0;--i)
//    {
//        p=(LinkList)malloc(sizeof(LNode));    //生成新的结点
//        scanf("%d",&p->data.no);              //输入学生学号、姓名、当前经验值信息
//        scanf("%s",&p->data.name);
//        scanf("%d",&p->data.jyz);
//        p->next=(*L)->next;                   //插入到表头
//        (*L)->next;
//    }
//}           //CreateList_F

void CreateList_L(LinkList *L, int n) //后插法创建单链表
{
    //正位序输入n个元素的值,建立到头结点的单链表L
    LNode *r, *p;
    (*L) = (LinkList)malloc(sizeof(LNode));
    (*L)->next = NULL; //先建立一个带头结点的单链表
    r = *L;            //尾指针r指向头结点
    //cout<<"请输入"<<n<<"个数:\n";
    printf("请输入%d个学生的学号、姓名、当前经验值:\n", n);
    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(LNode)); //生成新结点
        //cin>>p->data;
        scanf("%d", &p->data.no); //输入学生学号、姓名、当前经验值信息
        scanf("%s", p->data.name);
        scanf("%d", &p->data.jyz);
        p->next = NULL; //插入到表尾
        r->next = p;
        r = p; //r指向新的尾结点
    }
} //CreateList_L

Status DestroyList_L(LinkList *L) //存盘与销毁
{
    LinkList p;
    FILE *myfile;
    myfile = fopen("Student.txt", "w");
    while (*L)
    {
        p = (*L);
        (*L) = (*L)->next;
        if (*L && (!(*L)->next))
            fprintf(myfile, "%d %s %d", (*L)->data.no, (*L)->data.name, (*L)->data.jyz);
        else if (*L)
            fprintf(myfile, "%d %s %d\n", (*L)->data.no, (*L)->data.name, (*L)->data.jyz);
        free(p);
    }
    fclose(myfile);
    return OK;
}

Status ClearList_L(LinkList *L)
{
    //将L重置为空表
    LinkList p, q;
    p = (*L)->next; //p指向第一个结点
    while (p)       //没到表尾
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL; //头结点指针域为空
    return OK;
}

int main()
{
    LinkStack s;
    SElemType t;
    InitStack(&s);
    int choose, n, jyz;
    ElemType res, b;
    LNode *L = NULL, *p;
    printf("课堂经验值管理系统\n");
    printf("1.导入文件建立学生信息表\n");
    printf("2.正序输入学生数据\n");
    printf("3.按位置查找\n");
    printf("4.按学号查找学生经验值\n");
    printf("5.插入新学生信息\n");
    printf("6.删除离班同学信息\n");
    printf("7.输入全部同学信息\n");
    printf("8.为某学号同学加指定经验值\n");
    printf("9.为某学号同学减指定经验值\n");
    printf("10.撤销上一次增减经验值操作\n");
    printf("0.存盘并退出\n\n");
    choose = -1;
    while (choose != 0)
    {
        printf("请选择:");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1: //建立一个单链表
            if (InitList_L(&L))
                printf("成功建立学生信息表\n\n");
            else
                printf("学生信息表建立失败\n\n");
            break;
        case 2: //使用后插法创建单链表
            printf("请输入学生人数:");
            scanf("%d", &n);
            ClearList_L(&L);
            printf("请输入%d个学生信息:\n", n);
            CreateList_L(&L, n);
            printf("成功输入%d个学生信息\n\n", n);
            break;
        case 3: //单链表的按序号查找
            printf("请输入一个位置用来查找:");
            scanf("%d", &n);
            if (GetElem_L(L, n, &res))
            {
                printf("查找成功!第%d个学生是:%s\n\n", n, res.name);
            }
            else
            {
                printf("查找失败\n\n");
            }
            break;
        case 4: //单链表的按值查找
            printf("请输入所要查找的学生学号:");
            scanf("%d", &b.no);
            if (LocateElem_L(L, b) != NULL)
                printf("查找成功\n%d学生的经验值是 %d.\n\n", LocateElem_L(L, b)->data.no, LocateElem_L(L, b)->data.jyz);
            else
                printf("查找失败!%d没有找到\n\n", b.no);
            break;
        case 5: //单链表的插入
            printf("请输入要插入的新同学信息:\n");
            printf("插入的位置   学号  姓名  经验值:\n");
            scanf("%d%d%s%d", &n, &b.no, b.name, &b.jyz);
            if (ListInsert_L(&L, n, &b))
            {
                printf("成功将%d插在学生信息表第%d个位置\n\n", b.no, n);
            }
            else
            {
                printf("插入失败!");
            }
            break;
        case 6: //单链表的删除
            printf("请输入所要删除的离班学生在信息表中的位置:");
            scanf("%d", &n);
            if (ListDelete_L(&L, n, &res))
                printf("删除成功.\n被删除离班学生是:%d\n\n", res.no);
            else
                printf("删除失败!\n\n");
            break;
        case 7: //单链表的输出
            printf("当前学生信息表为:\n");
            printf("学号  姓名  经验值\n");
            p = L->next;
            while (p)
            {
                printf("%d  %s  %d \n", p->data.no, p->data.name, p->data.jyz);
                p = p->next;
            }
            printf("\n");
            break;
        case 8: //加经验值
            printf("请输入所要加经验值的学生序号:");
            scanf("%d", &b.no); //输入e,代表所要查找的数值
            printf("请输入所要加的经验值:");
            scanf("%d", &jyz);
            if (jia(&L, b, jyz))
            {
                printf("%d学生的经验值已加%d.\n\n", b.no, jyz);
                t.opr = '+';
                t.no = b.no;
                t.jyz = jyz;
                Push(&s, t);
            }
            else
                printf("查找失败!没有这样的学生信息\n");
            break;
        case 9: //减经验值
            printf("请输入所要减检验值的学生学号:");
            scanf("%d", &b.no);
            printf("请输入所要减得经验值:");
            scanf("%d", &jyz);
            if (jian(&L, b, jyz))
            {
                printf("%d学生的经验值已减%d.\n\n", b.no, jyz);
                t.opr = '-';
                t.no = b.no;
                t.jyz = jyz;
                Push(&s, t);
            }
            else
            {
                printf("查找失败!没有这样的学生信息\n\n");
            }
            break;
        case 10: //撤销
            if (Pop(&s, &t))
            {
                if (t.opr == '+')
                {
                    b.no = t.no;
                    jian(&L, b, t.jyz);
                }
                if (t.opr == '-')
                {
                    b.no = t.no;
                    jia(&L, b, t.jyz);
                }
                printf("撤销成功!\n\n");
            }
            else
                printf("无步骤可撤销!\n\n");
            break;
        }
    }
    DestroyList_L(&L);
    return 0;
}
