#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OK 1
typedef struct
{
    int key; //关键字域
} ElemType;
typedef struct
{
    ElemType *R;
    int length;
} SSTable;

int InitList_SSTable(SSTable *L)
{
    L->R = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if (!L->R)
    {
        printf("初始化错误");
        return 0;
    }
    L->length = 0;
    return OK;
}

int Insert_SSTable(SSTable *L)
{
    int j = 0;
    for (int i = 0; i < MAXSIZE; i++)
    {
        L->R[i].key = j;
        L->length++;
        j++;
    }
    return 1;
}

int Search_Seq(SSTable ST, int key)
{
    //顺序查找
    //在顺序表ST中顺序查找其关键字等于key的数据元素。若找到,则函数值为i
    //该元素在表中的位置,否则为0
    for (int i = ST.length; i >= 1; --i)
        if (ST.R[i].key == key) //从后往前查找
            return i;
    return 0;
}

void Show_End(int result, int testkey)
{
    if (result == 0)
        printf("未找到%d\n", testkey);
    else
        printf("找到%d位置为%d\n", testkey, result);
    return;
}

int main()
{
    SSTable ST;
    InitList_SSTable(&ST);
    Insert_SSTable(&ST);
    int testkey1 = 7, testkey2 = 200;
    int result;
    result = Search_Seq(ST, testkey1);
    Show_End(result, testkey1);
    result = Search_Seq(ST, testkey2);
    Show_End(result, testkey2);
    return 0;
}
