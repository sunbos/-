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

void SelectSort(SqList *L)
{
    int i, j, k;
    ElemType t;
    for (i = 1; i < L->length; ++i)
    {
        k = i;
        for (j = i + 1; j <= L->length; ++j)
            if (L->r[j].key < L->r[k].key)
                k = j;
        if (k != i)
        {
            t = L->r[i];
            L->r[i] = L->r[k];
            L->r[k] = t;
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
    L.r = (ElemType *)malloc((MAXSIZE + 1) * sizeof(ElemType));
    L.length = 0;
    Create_Sq(&L);
    SelectSort(&L);
    printf("排序后的结果为:\n");
    show(&L);
}
