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

void BubbleSort(SqList *L)
{
    int m, j, flag;
    ElemType t;
    m = L->length - 1;
    flag = 1;
    while (m > 0 && flag == 1)
    {
        flag = 0;
        for (j = 1; j <= m; j++)
        {
            if (L->r[j].key > L->r[j + 1].key)
            {
                flag = 1;
                t = L->r[j];
                L->r[j] = L->r[j + 1];
                L->r[j + 1] = t;
            }
        }
        --m;
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
    BubbleSort(&L);
    printf("排序后的结果为:\n");
    show(&L);
}
