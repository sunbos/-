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

void ShellInsert(SqList *L, int dk)
{
    int i, j;
    for (i = dk + 1; i <= L->length; i++)
    {
        if (L->r[i].key < L->r[i - dk].key)
        {
            L->r[0] = L->r[i];
            for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk)
                L->r[j + dk] = L->r[j];
            L->r[j + dk] = L->r[0];
        }
    }
}

void ShellSort(SqList *L, int dt[], int t)
{
    int k;
    for (k = 0; k < t; ++k)
        ShellInsert(L, dt[k]);
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
    int i, t;
    int *dt = (int *)malloc(MAXSIZE * sizeof(int));
    printf("请输入增量个数:\n");
    scanf("%d", &t);
    for (i = 0; i < t; i++)
    {
        printf("第%d个增量:\n", i + 1);
        scanf("%d", &dt[i]);
    }
    ShellSort(&L, dt, t);
    printf("排序后的结果为:\n");
    show(&L);
}
