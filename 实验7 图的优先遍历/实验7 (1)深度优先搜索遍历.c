#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MVNum 100
typedef char VerTexType;
typedef struct ArcNode
{
   int adjvex;
   struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode
{
   VerTexType data;
   ArcNode *firstarc;
}VNode,AdjList[MVNum];

typedef struct
{
   AdjList vertices;
   int vexnum,arcnum;
}ALGraph;

//int visited[MVNum];
bool visited[MVNum];

int LocateVex(ALGraph G,VerTexType v)
{
   for(int i=0;i<G.vexnum;++i)
       if(G.vertices[i].data==v)
           return i;
   return -1;
}

void CreateUDG(ALGraph *G)
{
   int i,k;
   printf("请输入总顶点数,总边数,以空格隔开:");
   scanf("%d %d",&(*G).vexnum,&(*G).arcnum);
   getchar();
   printf("\n");
   printf("输入点的名称,如a\n");
   for (i = 0; i < (*G).vexnum; ++i)
   {
       printf("请输入第%d个点的名称:",(i+1));
       scanf("%c",&(*G).vertices[i].data);
       getchar();
       (*G).vertices[i].firstarc=NULL;
   }
   printf("\n");
   printf("输入边依附的顶点,如a b\n");
   for(k=0;k<G->arcnum;++k)
   {
       VerTexType v1,v2;
       int i,j;
       printf("\n请输入第%d条边依附的顶点:",(k+1));
       scanf("%c %c",&v1,&v2);
       getchar();
       i=LocateVex(*G, v1);
       j=LocateVex(*G, v2);

       ArcNode (*p1)=(ArcNode *)malloc(sizeof(ArcNode));
       p1->adjvex=j;
       p1->nextarc=(*G).vertices[i].firstarc;
       (*G).vertices[i].firstarc=p1;

       ArcNode (*p2)=(ArcNode *)malloc(sizeof(ArcNode));
       p2->adjvex=i;
       p2->nextarc=(*G).vertices[j].firstarc;
       (*G).vertices[j].firstarc=p2;
   }
}

void DFS(ALGraph G,int v)
{
   printf("%c ",G.vertices[v].data);
//    visited[v]=1;
   visited[v]=true;
   ArcNode *p=G.vertices[v].firstarc;
   while (p!=NULL) {
       int w=p->adjvex;
       if(!visited[w])
           DFS(G, w);
       p=p->nextarc;
   }
}

int main()
{
   printf("************算法6.6  采用邻接表表示图的深度优先搜索遍历***************\n\n");
   ALGraph G;
   CreateUDG(&G);
   printf("\n");
   printf("无向连通图G创建完成!\n\n");
   printf("请输入遍历连通图的起始点:");
   VerTexType c;
   scanf("%c",&c);
   int i;
   for(i=0;i<G.vexnum;++i)
   {
       if(c==G.vertices[i].data)
           break;
   }
   printf("\n");
   while (i>=G.vexnum)
   {
       printf("该点不存在,请重新输入!\n");
       printf("请输入遍历连通图的起始点:");
       scanf("%c",&c);
       getchar();
       for (i=0; i<G.vexnum; ++i)
       {
           if(c==G.vertices[i].data)
               break;
       }
   }
   printf("深度优先搜索遍历图结果:\n");
   DFS(G, i);
   printf("\n");
   return 0;
}
