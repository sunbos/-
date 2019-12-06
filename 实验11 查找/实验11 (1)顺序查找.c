#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OK 1
typedef struct
{
    int key;
}ElemType;
typedef struct
{
    ElemType *R;
    int length;
}SSTable;

int InitList_SSTable(SSTable *L)
{
    L->R=(ElemType*)malloc(MAXSIZE*sizeof(ElemType));
    if(!L->R)
    {
        printf("初始化错误");
        return 0;
    }
    L->length=0;
    return OK;
}

int Insert_SSTable(SSTable *L)
{
    int j=0;
    for(int i=0;i<MAXSIZE;i++)
    {
        L->R[i].key=j;
        L->length++;
        j++;
    }
    return 1;
}

int Search_Seq(SSTable ST,int key)
{
    for(int i=ST.length;i>=1;--i)
        if(ST.R[i].key==key)
            return i;
    return 0;
}

void Show_End(int result,int testkey)
{
    if(result==0)
        printf("未找到%d\n",testkey);
    else
        printf("找到%d位置为%d\n",testkey,result);
    return;
}

int main()
{
    SSTable ST;
    InitList_SSTable(&ST);
    Insert_SSTable(&ST);
    int testkey1 = 7,testkey2 = 200;
    int result;
    result = Search_Seq(ST, testkey1);
    Show_End(result, testkey1);
    result = Search_Seq(ST, testkey2);
    Show_End(result, testkey2);
    return 0;
}
