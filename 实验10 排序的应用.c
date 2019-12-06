#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAXNUM 10000
long cn[MAXNUM],mn[MAXNUM];
typedef struct
{
    int key;
}datatype;
void D_InsertSort(datatype R[],long n)
{
    long i,j;
    for(i=2;i<=n;i++)
    {
        cn[0]++;
        if(R[i].key<R[i-1].key)
        {
            R[0]=R[i];
            mn[0]++;
            for(j=i-1;R[0].key<R[j].key;j--)
                R[j+1]=R[j];
            R[j+1]=R[0];
            mn[0]+=2;
        }
    }
}

void Select_Sort(datatype R[], long n)
{
    long i,j,k;
    for(i=1;i<n;i++)
    {
        k=i;
        for(j=i+1;j<=n;j++)
        {
            cn[1]++;
            if(R[j].key<R[k].key)
                k=j;
        }
        if(i==k)
        {
            R[0]=R[k];
            R[k]=R[i];
            R[i]=R[0];
            mn[1]+=3;
        }
    }
}

void Bubble_Sort(datatype R[], long n)
{
    long i,j;
    for(i=1;i<n-1;i++)
    {
        for(j=1;j<=n-i;j++)
        {
            cn[2]++;
            if(R[j].key<R[j+1].key)
            {
                R[0]=R[j];
                R[j]=R[j+1];
                R[j+1]=R[0];
                mn[2]+=3;
            }
        }
    }
}

void HeapAdjust(datatype R[], long s, long t)
{
    datatype rc;
    long i,j;
    rc=R[s];
    i=s;
    for(j=2*i;j<=t;j=2*j)
    {
        cn[3]++;
        if(j<t&&R[j].key<R[j+1].key)
            j=j+1;
        if(rc.key>R[j].key)
            break;
        R[i]=R[j];
        mn[3]++;
        i=j;
    }
    R[i]=rc;
}

void HeapSort(datatype R[], long n)
{
    long i;
    for(i=n/2;i>0;i--)
        HeapAdjust(R,i,n);
    for (i=n; i>1; i--)
    {
        R[0]=R[1];
        R[1]=R[i];
        R[i]=R[0];
        mn[3]+=3;
        HeapAdjust(R, 1, i-1);
    }
}

void Merge(datatype R[],datatype R1[],long s,long m,long t)
{
    long i,j,k;
    i=s;j=m+1;k=s;
    while (i<=m&&j<=t)
    {
        cn[4]++;
        if(R[i].key<R[j].key)
        {
            R1[k++]=R[i++];
            mn[4]++;
        }
        else
        {
            R1[k++]=R[j++];
            mn[4]++;
        }
    }
    while (i<=m)
    {
        R1[k++]=R[i++];
        mn[4]++;
    }
    while (j<=t)
    {
        R1[k++]=R[j++];
        mn[4]++;
    }
}

void MSort(datatype R[],datatype R1[],long s,long t)
{
    long m;
    if(s==t)
    {
        R1[s]=R[s];
        mn[4]++;
    }
    else
    {
        m=(s+t)/2;
        MSort(R, R1, s, m);
        MSort(R, R1, m+1, t);
        Merge(R1, R, s, m, t);
    }
}

void MergeSort(datatype R[],datatype R1[],long n)
{
    MSort(R, R1, 1, n);
}

long Partition(datatype R[],long low,long high)
{
    R[0]=R[low];
    mn[5]++;
    while (low<high)
    {
        while (low<high&&R[high].key>=R[0].key)
        {
            cn[5]++;
            high--;
        }
        if(low<high)
        {
            R[low]=R[high];
            low++;
            mn[5]++;
        }
        while (low<high&&R[low].key<R[0].key)
        {
            cn[5]++;
            low++;
        }
        if(low<high)
        {
            R[high]=R[low];
            high--;
            mn[5]++;
        }
    }
    R[low]=R[0];
    mn[5]++;
    return low;
}

void Quick_Sort(datatype R[],long s,long t)
{
    long i;
    if(s<t)
    {
        i=Partition(R, s, t);
        Quick_Sort(R, s, i-1);
        Quick_Sort(R, i+1, t);
    }
}

void print(datatype R[],long n)
{
    long i;
    printf("排序结果为:\n");
    for(i=1;i<=n;i++)
    {
        printf("%d ",R[i]);
    }
    printf("\n");
}

void init()
{
    int i,n;
    datatype R[MAXNUM]={0};
    printf("请输入你要随机出来的个数:\n");
    scanf("%d",&n);
    if(n>500000)
    {
        printf("超出范围请重新输入!\n");
        scanf("%d ",&n);
    }
    for (i=1; i<=n; i++)
        R[i].key=rand()%1000;
    printf("排序前的元素顺序:\n");
    for (i=1; i<n+1; i++)
    {
        printf("%d ",R[i].key);
    }
    printf("\n");
    D_InsertSort(R, n);
    Select_Sort(R, n);
    Bubble_Sort(R, n);
    HeapSort(R, n);
    datatype R2[MAXNUM]={0};
    MergeSort(R, R2, n);
    Quick_Sort(R, 0, n);
    print(R, n);
}

int main()
{
    init();
    printf("                比较结果                \n");
    printf("    排列方式    比较次数    移动次数\n");
    printf("    直接         %ld          %ld      \n",cn[0],mn[0]);
    printf("    简单选择      %ld          %ld      \n",cn[1],mn[1]);
    printf("    冒泡         %ld          %ld      \n",cn[2],mn[2]);
    printf("    堆排序       %ld          %ld      \n",cn[3],mn[3]);
    printf("    快速排序      %ld          %ld      \n",cn[5],mn[5]);
    return 0;
}
