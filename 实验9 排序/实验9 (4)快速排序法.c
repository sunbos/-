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

int Partition(SqList *L, int low, int high)
{
    int pivotkey;
    L->r[0] = L->r[low];
    pivotkey = L->r[low].key;
    while (low < high)
    {
        while (low < high && L->r[high].key >= pivotkey)
            --high;
        L->r[low] = L->r[high];
        while (low < high && L->r[low].key <= pivotkey)
            ++low;
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;
}

void QSort(SqList *L, int low, int high)
{
    int pivotloc;
    if (low < high)
    {
        pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc);
        QSort(L, pivotloc + 1, high);
    }
}

void QuickSort(SqList *L)
{
    QSort(L, 1, L->length);
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
    QuickSort(&L);
    printf("排序后的结果为:\n");
    show(&L);
}
