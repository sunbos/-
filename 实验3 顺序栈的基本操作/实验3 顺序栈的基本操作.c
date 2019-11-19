#include <stdio.h>
#include <stdlib.h>
//顺序栈的定义
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100         //注意define(宏定义)后面不加";",而const就可以加";",不然30行报错
//const int MAXSIZE=100;    //顺序栈储存空间的初始分配量
typedef int Status;
typedef char SElemType;
typedef struct
{
    SElemType *base;        //栈底指针
    SElemType *top;         //栈顶指针
    int stacksize;          //栈可用的最大容量
}SqStack;


Status InitStack(SqStack *S)    //顺序栈的初始化
{
    //构造一个空栈S
    S->base =(SElemType *)malloc(MAXSIZE*sizeof(SElemType)); //开辟一个MAXSIZE长度的空间
    if (!S->base)
        exit(OVERFLOW);             //栈底为空返回OVERFLOW，并退出
    S->top=S->base;                 //如果没有就让栈顶元素等于栈底元素，使top初始为base
    S->stacksize = MAXSIZE;         //stacksize置为栈的最大容量MAXSIZE
    return OK;                      //返回OK，即1
}

Status Push(SqStack *S,SElemType e)     //顺序栈的入栈
{
    //插入元素e为新的栈顶元素
    if (S->top-S->base==S->stacksize) //先判断栈是否栈满
        return ERROR;                 //如果是就返回错误
    *(S->top++) = e;                  //++在后面，所以后执行，应该是先将元素进栈，再将top指针向后移一位
    return OK;
}

Status Pop(SqStack *S,SElemType *e)     //顺序栈的出栈
{
    //删除S的栈顶元素，用e返回其值
    if(S->base == S->top)       //判断栈是否为空栈
        return ERROR;           //如果是就返回错误
    *e = *(--S->top);           //先将栈顶指针，下移一位，然后再将元素取出
    return OK;
}

SElemType GetTop(SqStack S)     //取顺序栈的栈顶元素
{
    if(S.top != S.base)                 //判断栈是否为空
        return *(S.top-1);              //如果不为空，返回栈顶指针的下一个元素
    else                                //否则返回错误
        return ERROR;
}

int main()
{
    SqStack s;                      //定义一个栈
    int choose,flag=0;              //choose对应下面case的功能，flag起到判断的作用，
    SElemType j,t;
    printf("1.初始化\n");
    printf("2.入栈\n");
    printf("3.读取栈顶元素\n");
    printf("4.出栈\n");
    printf("0.退出\n");

    choose = -1;
    while (choose!=0)
    {
        printf("请选择:");
        scanf("%d",&choose);
        switch (choose)
        {
            case 1:
                if(InitStack(&s))
                {
                    flag = 1;
                    printf("成功对栈进行初始化\n\n");
                }
                else
                    printf("初始化栈失败\n\n");
                break;
            case 2:
            {
                FILE *file;                                     //定义一个叫file的文件
                file = fopen("SqStack.txt", "r"); //定义一个SqStack.txt的文件，只读
                if (file == NULL)                                 //如果没有找到文件
                {
                    printf("错误!未找到文件! \n\n\n");
                    return ERROR;
                }
                if (flag)                               //执行此步骤时必须完成 栈的初始化，如果没有完成，flag就会返回-1
                {
                    flag = 1;
                    printf("进栈元素依次为:\n");
                    j = fgetc(file);                      //从文件里读取字符
                    while (j != EOF)                      //使字符循环输入
                    {
                        //file>>j;
                        Push(&s, j);                     //将字符放到栈里
                        printf("%c ", j);                //并将它输出
                        j = fgetc(file);                 //从文件里取出字符
                    }
                    printf("\n\n");
                } else
                    printf("栈未建立,请重新选择\n\n");
                fclose(file);                           //file.close()关闭文件file;
                break;
            }
            case 3:
                if(flag != -1&&flag != 0)               //等于-1时是出栈完毕，此时栈里没有元素，也就没有相应的栈顶元素。当等于0时，栈没有初始化
                    printf("栈顶元素为:\n%c\n\n",GetTop(s));
                else
                    printf("栈中无元素,请重新选择\n\n");
                break;
            case 4:
                printf("依次弹出的栈顶元素为:\n");
                while (Pop(&s,&t))
                {
                    printf("%c ",t);
                }
                flag = -1;
                printf("\n\n");
                break;
            default:
                if(choose!=0)
                    printf("请输入正确的序号来进行相应的计算\n\n");
        }
    }
    return 0;
}
