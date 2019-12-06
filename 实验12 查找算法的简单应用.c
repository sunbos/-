#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int key;
    char *p;
}name;
name a[35];
int main()
{
    a[0].p="wangjunzhe";    a[1].p="mahaiping";
    a[2].p="luozijian";     a[3].p="luoxiangzhou";
    a[4].p="zhangkai";      a[5].p="fengyuyang";
    a[6].p="wuzhenzhen";    a[7].p="haokaiqi";
    a[8].p="caopu";         a[9].p="liuying";
    a[10].p="cuijuan";      a[11].p="hanqianqian";
    a[12].p="lixiaoyu";     a[13].p="caoyingnan";
    a[14].p="jinbaoyu";     a[15].p="zhaduo";
    a[16].p="wenbo";        a[17].p="cuichangwei";
    a[18].p="zhangqiu";     a[19].p="luopeng";
    a[20].p="hudie";        a[21].p="xieshanshan";
    a[22].p="liming";       a[23].p="zhangshuai";
    a[24].p="qiuyajun";     a[25].p="yanruibin";
    a[26].p="jiangwei";     a[27].p="fangzhaohua";
    a[28].p="yujia";        a[29].p="liuzhenzhen";
    
    int i,s,r;
    for(i=0;i<30;i++)
    {
        s=0;
        for (r=0; *(a[i].p+r)!='\0'; r++)
        {
            s+=*(a[i].p+r);
            a[i].key=s;
        }
    }
    
    typedef struct
    {
        int key;
        int hash;
        int reha;
        char *p;
        int l;
    }HASH;
    HASH h[40];
    for(i=0;i<40;i++)
    {
        h[i].key=0;
        h[i].hash=0;
        h[i].reha=0;
        h[i].p="";
        h[i].l=0;
    }
    for(i=0;i<30;i++)
    {
        int sum=0;
        int hi=(a[i].key)%37;
        int hj=(7*a[i].key)%10+1;
        if(h[hi].l==0)
        {
            h[hi].key=a[i].key;
            h[hi].hash=(a[i].key)%37;
            h[hi].reha=(7*a[i].key)%10+1;
            h[hi].p=a[i].p;
            h[hi].l=1;
        }
        else
        {
            int finh;
            do
            {
                finh=(hi+hj)%40;
                hi=finh;
                sum=sum+1;
            }while(h[hi].l!=0);
            h[hi].key=a[i].key;
            h[hi].hash=(a[i].key)%37;
            h[hi].reha=(7*a[i].key)%10+1;
            h[hi].p=a[i].p;
            h[hi].l=sum+1;
        }
    }
    float average=0;
    printf("关键码 初散列 再散列 哈希地址 查找次数 姓名\n");
    for (i=0; i<40; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%s\n",h[i].key,h[i].hash,h[i].reha,i,h[i].l,h[i].p);
    }
    for (i=0; i<40; i++)
        average+=h[i].l;
    average/=30;
    printf("平均查找长度:ASL%f\n",average);
    int m;
    do
    {
        char *f=(char *)malloc(20*sizeof(char *));
        int key=0,n=0,g,l=1,adr;
        printf("请输入姓名的拼音:\n");
        scanf("%s",f);
        for (g=0; *(f+g)!='\0'; g++)
        {
            n+=*(f+g);
            key=n;
        }
        adr=key%37;
        if(h[adr].key==key)
        {
            printf("关键字:%d\n",key);
            printf("初散列值为:%d\n",h[adr].hash);
            printf("再散列值为:%d\n",h[adr].reha);
            printf("表中位置为:%d\n",adr);
            printf("查找长度为:%d\n",l);
        }
        else if(h[adr].key==0)
            printf("无此记录!\n");
        else
        {
            int finh;
            int sign=0;
            do
            {
                finh =(adr+7*key%10+1)%40;
                adr=finh;
                l=l+1;
                if(h[adr].key==0)
                {
                    sign=1;
                    printf("无此记录!\n");
                }
                if(h[adr].key==key)
                {
                    sign=1;
                    printf("关键字:%d\n",key);
                    printf("初散列值为:%d\n",h[adr].hash);
                    printf("表中位置为:%d\n",adr);
                    printf("查找长度为:%d\n",l);
                }
            }while(sign==0);
        }
        printf("继续查询请输入,退出请输入:\n");
        scanf("%d",&m);
    }while(m==1);
    return 0;
}
