#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20 //顺序表的最大长度
typedef struct
{
    int key;
    char *otherinfo;
} ElemType;

typedef struct //顺序表的存储结构
{
    ElemType *r; //存储空间的基地址
    int length;  //顺序表的类型
} SqList;

void ShellInsert(SqList *L, int dk)
{ //对顺序表L做一趟增量是dk的希尔插入排序
    int i, j;
    for (i = dk + 1; i <= L->length; i++)
    {
        if (L->r[i].key < L->r[i - dk].key)
        {                      //需将L.r[i]插入有序增量子表
            L->r[0] = L->r[i]; //暂存在L.r[0]
            for (j = i - dk; j > 0 && L->r[0].key < L->r[j].key; j -= dk)
                L->r[j + dk] = L->r[j]; //记录后移,直到找到插入位置
            L->r[j + dk] = L->r[0];     //将r[0]即原r[i],插入到正确的位置
        }
    }
}

void ShellSort(SqList *L, int dt[], int t) //按增量序列dt[0..t-1]对顺序表L作t趟希尔排序
{
    int k;
    for (k = 0; k < t; ++k)
        ShellInsert(L, dt[k]); //一趟增量为dt[t]的希尔插入排序
}

void Create_Sq(SqList *L)
{
    int i, n;
    printf("请输入数据个数,不超过%d个\n", MAXSIZE);
    scanf("%d", &n); //输入个数
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
    int i, t;                                       //增量数组长度
    int *dt = (int *)malloc(MAXSIZE * sizeof(int)); //增量数组
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
