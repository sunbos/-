#include <stdio.h>
#include <string.h>

#define MaxInt 32767         //表示极大值,即∞
#define MVNum 100            //最大顶点数
typedef char VerTexType[20]; //假设顶点的数据类型为字符型
typedef int ArcType;         //假设边的权值类型为整型
int Path[MVNum][MVNum];      //最短路径上顶点vj的前一顶点的序号
int D[MVNum][MVNum];         //记录顶点vi和vj之间的最短路径长度
//---------图的邻接矩阵---------
typedef struct
{
    VerTexType vexs[MVNum];     //顶点表
    ArcType arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum, arcnum;         //图的当前点数和边数
} AMGraph;

int LocateVex(AMGraph G, VerTexType v) //确定点v在G中的位置
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (!strcmp(G.vexs[i], v))
            return i;
    }
    return -1;
}

void CreateUDN(AMGraph *G) //采用邻接矩阵表示法,创建无向网G
{
    int i, j, k;
    printf("请输入总标志点数,总可通道路数,以空格隔开:");
    scanf("%d %d", &G->vexnum, &G->arcnum); //输入总顶点数,总边数
    getchar();
    printf("\n");
    printf("输入标志点的名称,如“南1”\n");
    for (i = 0; i < G->vexnum; ++i)
    {
        printf("请输入第%d个标志点的名称:", (i + 1));
        scanf("%s", G->vexs[i]); //依次输入点的信息
        getchar();
    }
    printf("\n");
    for (i = 0; i < G->vexnum; ++i) //初始化邻接矩阵,边的权值均置为极大值MaxInt
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
    for (k = 0; k < G->arcnum; ++k) //构造邻接矩阵
    {
        VerTexType v1, v2;
        ArcType w;
        printf("请输入%d条道路依附的标志点及路长:", (k + 1));
        scanf("%s %s %d", v1, v2, &w); //输入一条边依附的顶点及权值
        i = LocateVex(*G, v1);
        j = LocateVex(*G, v2); //确定v1和v2在G中的位置,即顶点数组的下标
        G->arcs[i][j] = w;     //边<v1,v2>的权值为w
        G->arcs[j][i] = w;     //如果是有向网只需删除本条语句
    }
}

void ShortestPath_Floyed(AMGraph G)
{
    //用Floyd算法求有向网G中各对顶点i和j之间的最短路径
    int i, j, k;
    for (i = 0; i < G.vexnum; ++i) //各对结点之间初始已知路径及距离
    {
        for (j = 0; j < G.vexnum; ++j)
        {
            D[i][j] = G.arcs[i][j];
            if (D[i][j] < MaxInt && i != j) //如果i和j之间有弧,则将j的前驱置为i
                Path[i][j] = i;
            else //如果i和j之间无弧,则将j的前驱置为-1
                Path[i][j] = -1;
        }
    }
    for (k = 0; k < G.vexnum; ++k)
    {
        for (i = 0; i < G.vexnum; ++i)
        {
            for (j = 0; j < G.vexnum; ++j)
            {
                if (D[i][k] + D[k][j] < D[i][j]) //从i经k到j的一条路径更短
                {
                    D[i][j] = D[i][k] + D[k][j]; //更新D[i][j]
                    Path[i][j] = Path[k][j];     //更改j的前驱为k
                }
            }
        }
    }
}

void DisplayPath(AMGraph G, int begin, int temp) //显示更短路径
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
