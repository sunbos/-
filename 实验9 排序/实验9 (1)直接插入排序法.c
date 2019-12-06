#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct
{
    int key;
    char *otherinfo;
} ElemType;

typedef struct
{
    ElemType *r;
    int length;
} SqList;

void InserSort(SqList *L)
{
    int i, j;
    for (i = 1; i <= L->length; i++)
    {
        if (L->r[i].key < L->r[i - 1].key)
        {
            L->r[0] = L->r[i];
            L->r[i] = L->r[i - 1];
            for (j = i - 2; L->r[0].key < L->r[j].key; --j)
                L->r[j + 1] = L->r[j];
            L->r[j + 1] = L->r[0];
        }
    }
}

void Create_Sq(SqList *L)
{
    int i, n;
    printf("请输入数据个数,不超过%d个\n", MAXSIZE);
    scanf("%d", &n);
    while (n > MAXSIZE)
    {
        printf("个数超过上限,不能超过%d,请重新输入\n", MAXSIZE);
        scanf("%d", &n);
    }
    printf("请输入待排序的数据:\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &L->r[i].key);
        L->length++;
    }
}

void show(SqList *L)
{
    int i;
    for (i = 1; i <= L->length; i++)
        printf("%d ", L->r[i].key);
}

int main()
{
    SqList L;
    L.r=(ElemType *)malloc((MAXSIZE+1)*sizeof(ElemType));
    L.length=0;
    Create_Sq(&L);
    InserSort(&L);
    printf("排序后的结果为:\n");
    show(&L);
}
