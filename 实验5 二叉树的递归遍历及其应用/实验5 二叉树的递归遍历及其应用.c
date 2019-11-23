#include <stdio.h>
#include <stdlib.h>
typedef struct BiNode
{
    char data;                      //定义一个数据
    struct BiNode *lchild, *rchild; //定义左孩子和右孩子
} BiTNode, *BiTree;                 //定义结点和二叉树

void CreateBiTree(BiTree *T) //先序遍历的顺序建立二叉链表
{
    char ch;          //定义一个字符类型变量
    scanf("%c", &ch); //输入字符变量
    if (ch == '#')    //如果输入的字符为"#",就代表空
    {
        (*T) = NULL;
    }
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTNode)); //定义二叉树指针为*T名字为BiTNode类型char*
        (*T)->data = ch;                        //导入根的值
        CreateBiTree(&(*T)->lchild);            //导入左子树的值
        CreateBiTree(&(*T)->rchild);            //导入右子树的值
    }
}

void PreTraverse(BiTree T) //先序遍历二叉树的递归算法
{
    if (T)
    {
        printf("%c", T->data);  //遍历根
        PreTraverse(T->lchild); //遍历左孩子
        PreTraverse(T->rchild); //遍历右孩子
    }
}

void InOrderTraverse(BiTree T) //中序遍历二叉树的递归算法
{
    if (T)
    {
        InOrderTraverse(T->lchild); //遍历左孩子
        printf("%c", T->data);      //遍历根
        InOrderTraverse(T->rchild); //遍历右孩子
    }
}

void PostTraverse(BiTree T) //后序遍历二叉树的递归算法
{
    if (T)
    {
        PostTraverse(T->lchild); //遍历左孩子
        PostTraverse(T->rchild); //遍历右孩子
        printf("%c", T->data);   //遍历根
    }
}

//void PreTree(BiTree T,int j)
//{
//    if(T)
//    {
//        printf("%c",T->data);
//        for(int i=1;i<=j;i++)
//            printf("#");
//        printf("\n");
//        j--;
//        PreTree(T->lchild,j);
//        PreTree(T->rchild,j);
//    }
//}

int Depth(BiTree T) //求深度
{
    int m, n;      //定义m,n
    if (T == NULL) //如果结点为空,返回
        return 0;
    else
    {
        m = Depth(T->lchild); //m代表左孩子的深度
        n = Depth(T->rchild); //n代表右孩子的深度
        if (m > n)            //比较左右孩子深度的大小
            return (m + 1);   //最终结果取得子树的深度加根,就等于总深度
        else
            return (n + 1);
    }
}

int NodeCount(BiTree T) //求树的结点个数(递归)
{
    if (T == NULL) //如果树为空,结束
        return 0;
    else
        return NodeCount(T->lchild) + NodeCount(T->rchild) + 1; //否则,左孩子的总数加右孩子的总数加根
}

void CountLeaf(BiTree T, int *count) //叶子结点个数(度为0)
{
    if (T)
    {
        if ((!T->lchild) && (!T->rchild)) //左子树为空,右子树为空,证明它是叶子
            (*count)++;                   //叶子节点数+1
        CountLeaf(T->lchild, count);      //如果有左孩子或者右孩子就继续递归
        CountLeaf(T->rchild, count);
    }
}

//float PostEval(BiTree T)
//{
//    float lv,rv,value=0;
//    if(T!=NULL)
//    {
//        if((!T->lchild)&&(!T->rchild))
//            return (T->data)-'0';
//        else
//        {
//            lv=PostEval(T->lchild);
//            rv=PostEval(T->rchild);
//            switch (T->data)
//            {
//                case '+':value=lv+rv;break;
//                case '-':value=lv-rv;break;
//                case '*':value=lv*rv;break;
//                case '/':value=lv/rv;break;
//            }
//            return value;
//        }
//    }
//    return 0;
//}

int main()
{
    BiTree tree = NULL;
    int count, j;

    printf("二叉树的遍历及其应用\n");
    printf("1.先序建立二叉链表\n");
    printf("2.打印中序遍历结果\n");
    printf("3.打印先序遍历结果\n");
    printf("4.打印后序遍历结果\n");
    printf("5.求二叉树的深度\n");
    printf("6.求二叉树的结点个数\n");
    printf("7.求二叉树的叶子结点个数\n");
    //    printf("8.求表达式二叉树的值\n");
    //    printf("9.在屏幕打印二叉树\n");
    printf("0.退出\n\n");

    int choose = -1;
    while (choose != 0)
    {
        printf("请选择:");
        scanf("%d", &choose); //因为scanf这里是整型,所以这里只能识别整型,假如这里输入1'\n',代表的是键盘输入1和回车,但是在输入流里scanf只能接收到1,输入流缓冲区里还有\n。
        getchar();            //getchar()在这里使用的是为了将输入流缓冲区里的字符型'\n'取走
        switch (choose)
        {
        case 1:
            printf("请输入建立二叉链表的序列:\n");
            CreateBiTree(&tree);
            printf("\n");
            break;
        case 2:
            printf("先序遍历的结果为:\n");
            PreTraverse(tree);
            printf("\n\n");
            break;
        case 3:
            printf("中序遍历的结果为:\n");
            InOrderTraverse(tree);
            printf("\n\n");
            break;
        case 4:
            printf("后序遍历的结果为:\n");
            PostTraverse(tree);
            printf("\n\n");
            break;
        case 5:
            printf("树的深度为:%d\n\n", Depth(tree));
            break;
        case 6:
            printf("树的结点个数为:%d\n\n", NodeCount(tree));
            break;
        case 7:
            count = 0;
            CountLeaf(tree, &count);
            printf("叶子结点的个数为:%d\n\n", count);
            break;
        // case 8:
        //     printf("表达式二叉树的值是:%f\n\n", PostEval(tree));
        //     break;
        // case 9:
        //     j = 10;
        //     printf("二叉树的示意图为:\n");
        //     PreTree(tree, j);
        //     printf("\n");
        //     break;
        default:
            if (choose != 0)
                printf("请输入正确的操作数字\n\n");
        }
    }
}
