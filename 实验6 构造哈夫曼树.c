#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//哈夫曼树结点结构
/**
 * 构建哈夫曼树时，首先需要确定树中结点的构成。
 * 由于哈夫曼树的构建是从叶子结点开始，不断地构建新的父结点，直至树根，所以结点中应包含指向父结点的指针。(*HuffmanTree)
 * 但是在使用哈夫曼树时是从树根开始，根据需求遍历树中的结点，因此每个结点需要有指向其左孩子和右孩子的指针。(HTNode)
 **/
typedef struct
{
    int weight;                 //结点权重
    int parent, lchild, rchild; //父节点,左孩子,右孩子在数组中的位置下标
} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
/**
 *查找权重值最小的两个结点的思想是:从树组起始位置开始,首先找到两个无父结点的结点(说明还未使用其构建成树),然后和后续无父结点的结点依次做比较,有两种情况需要考虑:
 * 如果比两个结点中较小的那个还小,就保留这个结点,删除原来较大的结点;
 * 如果介于两个结点权重值之间,替换原来较大的结点;
 **/
//HT数组中存放的哈夫曼树,len表示HT数组中存放结点的最终位置,s1和s2传递的是HT数组
void Select(HuffmanTree HT, int len, int *s1, int *s2) //哈夫曼树中的查找算法,s1和s2传入的是实参的地址,所以函数运行完成后,实参中存放的自然就是哈夫曼树中权重值最小的两个结点在数组中的位置.
{
    int i, min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f; //0x3f3f3f3f=1061109567,数据初始化,假设无穷大
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            *s1 = i;
        }
    }
    int temp = HT[*s1].weight;
    HT[*s1].weight = 0x3f3f3f3f;
    for (i = 1; i <= len; i++)
    {
        if (HT[i].weight < min2 && HT[i].parent == 0)
        {
            min2 = HT[i].weight;
            *s2 = i;
        }
    }
    HT[*s1].weight = temp;
}
//HT为地址传递的存储哈夫曼树的数组,n为结点个数
void CreatHuffmanTree(HuffmanTree *HT, int n)
{
    int m, i;
    if (n <= 1)
        return;                                          //如果只有一个编码就相当于0
    m = 2 * n - 1;                                       //哈夫曼树的总结点数m=2n-1,n是叶子结点
    *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode)); //之所以用m+1,是因为0号位置不可用
    for (i = 1; i <= m; ++i)                             //初始化哈夫曼树的所有节点,使其都为0
    {
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }
    printf("请输入叶子结点的权值:\n");
    for (i = 1; i <= n; ++i) //将哈夫曼树的权值输入
        scanf("%d", &(*HT)[i].weight);

    //从树组的下标n+1开始初始化哈夫曼树中除叶子节点外的结点

    for (i = n + 1; i <= m; ++i) //构建哈夫曼树
    {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2); //哈弗曼树中的查找算法
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}
/**
 * 原理:
 * 哈夫曼编码就是在哈夫曼树的基础上构建的，这种编码方式最大的优点就是用最少的字符包含最多的信息内容。
 * 根据发送信息的内容，通过统计文本中相同字符的个数作为每个字符的权值，建立哈夫曼树。
 * 对于树中的每一个子树，统一规定其左孩子标记为 0 ，右孩子标记为 1 。
 * 这样，用到哪个字符时，从哈夫曼树的根结点开始，依次写出经过结点的标记，最终得到的就是该结点的哈夫曼编码。
 * 文本中字符出现的次数越多，在哈夫曼树中的体现就是越接近树根。编码的长度越短。
 * 算法:
 * 从叶子结点一直找到根结点，逆向记录途中经过的标记。最后逆序输出。
 **/
//HT为哈夫曼树,HC为存储结点哈夫曼编码的二维动态数组,n为结点个数
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode *HC, int n)
{
    *HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); //HC为存储结点哈夫曼编码的二维动态数组
    char *cd = (char *)malloc(n * sizeof(char));         //cd为存放结点哈夫曼编码的字符串数组
    // char *cd;
    // cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0'; //字符串结束符
    for (int i = 1; i <= n; ++i)
    {
        int start = n - 1;    //从叶子结点出发,得到的哈弗曼编码是逆序的,需要在字符串数组中进行比较
        int c = i;            //当前结点在数组中的位置
        int f = HT[i].parent; //当前结点的父节点在数组中的位置
        while (f != 0)
        {
            --start;
            if (HT[f].lchild == c) //如果该结点是父结点的左孩子则对应路径编码为0,否则为右孩子编码为1
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f; //把父结点变为孩子结点,继续朝着树根的方向遍历
            f = HT[f].parent;
        }
        (*HC)[i] = (char *)malloc((n - start) * sizeof(char)); //跳出循环后,cd数组中从下标start开始,存放的就是该结点的哈夫曼编码
        strcpy((*HC)[i], &cd[start]);
    }
    free(cd); //使用malloc申请的cd动态数组需要手动释放
}
//打印哈夫曼编码的函数
void show(HuffmanTree HT, HuffmanCode HC, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d编码为%s\n", HT[i].weight, HC[i]);
    }
}

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    printf("请输入叶子结点的个数:\n");
    scanf("%d", &n);
    CreatHuffmanTree(&HT, n);
    CreatHuffmanCode(HT, &HC, n);
    show(HT, HC, n);
}
