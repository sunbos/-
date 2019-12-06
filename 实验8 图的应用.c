#include <stdio.h>
#include <string.h>

#define MaxInt 32767
#define MVNum 100
typedef char VerTexType[20];
typedef int ArcType;
int Path[MVNum][MVNum];
int D[MVNum][MVNum];
//---------图的邻接矩阵---------
typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} AMGraph;

int LocateVex(AMGraph G, VerTexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (!strcmp(G.vexs[i], v))
            return i;
    }
    return -1;
}

void CreateUDN(AMGraph *G)
{
    int i, j, k;
    printf("请输入总标志点数,总可通道路数,以空格隔开:");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    getchar();
    printf("\n");
    printf("输入标志点的名称,如“南1”\n");
    for (i = 0; i < G->vexnum; ++i)
    {
        printf("请输入第%d个标志点的名称:", (i + 1));
        scanf("%s", G->vexs[i]);
        getchar();
    }
    printf("\n");
    for (i = 0; i < G->vexnum; ++i)
    {
        for (j = 0; j < G->vexnum; ++j)
        {
            if (j != i)
                G->arcs[i][j] = MaxInt;
            else
                G->arcs[i][j] = 0;
        }
    }
    printf("输入道路依附的标志点及权值,如南1行政楼3\n");
    for (k = 0; k < G->arcnum; ++k)
    {
        VerTexType v1, v2;
        ArcType w;
        printf("请输入%d条道路依附的标志点及路长:", (k + 1));
        scanf("%s %s %d", v1, v2, &w);
        i = LocateVex(*G, v1);
        j = LocateVex(*G, v2);
        G->arcs[i][j] = w;
        G->arcs[j][i] = w;
    }
}

void ShortestPath_Floyed(AMGraph G)
{
    int i, j, k;
    for (i = 0; i < G.vexnum; ++i)
    {
        for (j = 0; j < G.vexnum; ++j)
        {
            D[i][j] = G.arcs[i][j];
            if (D[i][j] < MaxInt && i != j)
                Path[i][j] = i;
            else
                Path[i][j] = -1;
        }
    }
    for (k = 0; k < G.vexnum; ++k)
    {
        for (i = 0; i < G.vexnum; ++i)
        {
            for (j = 0; j < G.vexnum; ++j)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
}

void DisplayPath(AMGraph G, int begin, int temp)
{
    if (Path[begin][temp] != -1)
    {
        DisplayPath(G, begin, Path[begin][temp]);
        printf("%s-->", G.vexs[Path[begin][temp]]);
    }
}

int main()
{
    printf("***********图及其应用(校园导航)***********\n\n");
    AMGraph G;
    char start[20], destination[20];
    int num_start, num_destination, choose = 1;
    CreateUDN(&G);
    printf("\n");
    printf("校园地图创建完成!\n");
    ShortestPath_Floyed(G);
    while (choose == 1)
    {
        printf("请依次输入路径的起点与终点的名称(以空格隔开)");
        scanf("%s %s", start, destination);
        num_start = LocateVex(G, start);
        num_destination = LocateVex(G, destination);
        DisplayPath(G, num_start, num_destination);
        printf("%s\n", G.vexs[num_destination]);
        printf("最短路径长度为:%d\n", D[num_start][num_destination]);
        printf("\n");
        printf("输入1继续,输入其他数结束:");
        scanf("%d", &choose);
    }
    return 0;
}
