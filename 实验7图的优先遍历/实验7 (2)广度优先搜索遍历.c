#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MVNum 100
#define MAXQSIZE 100
typedef char VerTexType;
typedef int ArcType;
bool visited[MVNum];

typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}Graph;

typedef struct
{
    ArcType *base;
    int front;
    int rear;
}sqQueue;

void InitQueue(sqQueue *Q)
{
    (*Q).base=(ArcType *)malloc(MAXQSIZE*sizeof(ArcType));
    if (!(*Q).base)
        exit(1);
    (*Q).front=(*Q).rear=0;
}

void EnQueue(sqQueue *Q,ArcType e)
{
    if(((*Q).rear+1)%MAXQSIZE==(*Q).front)
        return;
    (*Q).base[(*Q).rear]=e;
    (*Q).rear=((*Q).rear+1)%MAXQSIZE;
}

bool QueueEmpty(sqQueue Q)
{
    if(Q.rear==Q.front)
        return true;
    return false;
}

void DeQueue(sqQueue *Q,ArcType *u)
{
    *u=(*Q).base[(*Q).front];
    (*Q).front=((*Q).front+1)%MAXQSIZE;
}

int LocateVex(Graph G,VerTexType v)
{
    for (int i=0; i<G.vexnum; ++i)
        if(G.vexs[i]==v)
            return i;
    return -1;
}

void CreateUDN(Graph *G)
{
    int i,j,k;
    printf("请输入总顶点数,总边数,以空格隔开:");
    scanf("%d %d",&(*G).vexnum,&(*G).arcnum);
    getchar();
    printf("\n");
    printf("输入点的名称,如a\n");
    for(i=0;i<(*G).vexnum;++i)
    {
        printf("请输入第%d个点的名称:",(i+1));
        scanf("%c",&(*G).vexs[i]);
        getchar();
    }
    printf("\n");
    for(i=0;i<(*G).vexnum;++i)
        for(j=0;j<(*G).vexnum;++j)
            (*G).arcs[i][j]=0;
    printf("输入边依附的顶点,如a b\n");
    for(k=0;k<(*G).arcnum;++k)
    {
        VerTexType v1,v2;
        printf("请输入第%d条边依附的顶点",(k+1));
        scanf("%c %c",&v1,&v2);
        getchar();
        i=LocateVex(*G, v1);
        j=LocateVex(*G, v2);
        (*G).arcs[i][j]=1;
        (*G).arcs[j][i]=(*G).arcs[i][j];
    }
}

int FirstAdjVex(Graph G,int v)
{
    int i;
    for(i=0;i<G.vexnum;++i)
    {
        if(G.arcs[v][i]==1&&visited[i]==false)
            return i;
    }
    return -1;
}

int NextAdjVex(Graph G,int u,int w)
{
    int i;
    for(i=w;i<G.vexnum;++i)
    {
        if(G.arcs[u][i]==1&&visited[i]==false)
            return i;
    }
    return -1;
}

void BFS(Graph G,int v)
{
    sqQueue Q;
    ArcType u;
    ArcType w;
    printf("%c ",G.vexs[v]);
    visited[v]=true;
    InitQueue(&Q);
    EnQueue(&Q, v);
    while (!QueueEmpty(Q))
    {
        DeQueue(&Q, &u);
        for(w=FirstAdjVex(G, u);w >= 0;w=NextAdjVex(G, u, w))
        {
//            NextAdjVex(G, u, w);
            if(!visited[w])
            {
                printf("%c ",G.vexs[w]);
                visited[w]=true;
                EnQueue(&Q, w);
            }
        }
    }
}

int main()
{
    printf("********广度优先搜索遍历连通图********\n\n");
    Graph G;
    CreateUDN(&G);
    printf("\n");
    printf("无向连通图G创建完成!\n\n");
    printf("请输入遍历连通图的起始点:");
    VerTexType c;
    scanf("%c",&c);
    int i;
    for(i=0;i<G.vexnum;++i)
    {
        if(c==G.vexs[i])
            break;
    }
    printf("\n");
    while (i>=G.vexnum)
    {
        printf("该点不存在,请重新输入!\n");
        printf("请输入遍历连通图的起始点:");
        scanf("%c",&c);
        getchar();
        for(i=0;i<G.vexnum;++i)
        {
            if(c==G.vexs[i])
                break;
        }
    }
    printf("广度优先搜索遍历连通图结果:\n");
    BFS(G, i);
    printf("\n");
    return 0;
}
