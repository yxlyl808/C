//第一题，模拟实现页式虚拟存储管理页面置换算法，OPT算法，FIFO算法，LRU算法，CLOCK算法
#include <stdio.h>
#include <queue> //队列
using namespace std;

int wulikuai; //物理块数
int yemianshu; //页面数
int queyeshu; //缺页数
int zouxiang[100]; //页面走向数组
int *neicun; //内存中的物理块
int *xia; //当前内存与下一次的距离
int *shang; //当前内存与上一次的距离
int *fangwen; //用于clock中做访问位

void mulu(); //声明目录函数

void shuru() //输入
{
    printf("-----模拟实现页式虚拟存储管理页面置换算法-----\n");	
	printf("页面数:");
	scanf("%d",&yemianshu);
	printf("页面走向:");
	for (int i=0;i<yemianshu;i++) {
		scanf("%d",&zouxiang[i]);
	}
    printf("物理块数:");
	scanf("%d",&wulikuai);
    neicun=(int*)malloc(sizeof(int)*wulikuai); //指针变量分配空间
	xia=(int*)malloc(sizeof(int)*wulikuai);
	shang=(int*)malloc(sizeof(int)*wulikuai);
	fangwen=(int*)malloc(sizeof(int)*wulikuai);
	mulu();
}

void xianshi() //显示现有内存中的物理块
{
	for (int i=0;i<wulikuai;i++) //遍历现有内存
	{
		if (neicun[i]>=0) //逐个输出
			printf("%d ",neicun[i]);
	}
}

int zhao(int *a,int x) //找一下传入的页面是否在内存中
{
	for (int i=0;i<wulikuai;i++) //遍历现有内存
	{
		if (x==a[i]) //找到
		{
			return i;
		}	
	}
	return -1; //内存中没有，返回-1
}

int xiajuli(int i,int j,int* a) //统计内存中的某个页面，离下一次出现的距离
{ //i表示从页面走向里的第几个页面开始搜索，j是内存中的某个页面，a是页面走向
	int juli=0; 
	while (i<yemianshu&&j!=a[i]) //在页面走向中逐个搜索并且不匹配时
	{  
		juli++; //距离数增加
		i++; //下一个页面
	}
	if (i>=yemianshu) //页面走向搜索完，说明没找到匹配的
		return juli+1;
	else //没搜索完，找到匹配的
		return juli; 
}

int shangjuli(int i,int j,int*a) //统计内存中的某个页面，离上一次出现的距离
{ //i表示从页面走向里的第几个页面开始搜索，j是内存中的某个页面，a是页面走向
	int juli=0;
	while (i>=0&&j!=a[i]) //在页面走向中逐个向前搜索并且不匹配时
	{
		juli++; //距离数增加
		i--; //下一个页面
	}
	if (i<0) //页面走向搜索完，说明没找到匹配的
		return juli+1;
	else //没搜索完，找到匹配的
		return juli;
}

int max(int *a) //用来找一个数组中最大的
{
	int k=0;
	int max=a[0];
	for (int i=1;i<wulikuai;i++) //遍历现有内存
	{
		if (a[i]>max)
		{
			max=a[i];
			k=i;
		}
	}
	return k; //返回最大值的下标
}

void OPT() //最佳置换
{
	int i=0,j=0;
    int taotai=-1; //要淘汰的页面
	queyeshu=0; //缺页个数
	while (i<yemianshu) //对页面走向逐个访问
	{
        printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{  
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
                j++;
			}
			else //内存满，找页面换出
			{
				for (int k=0;k<wulikuai;k++) //遍历现有内存
				{
					xia[k]=xiajuli(i+1,neicun[k],zouxiang); //统计当前内存与下一次的距离
				}
				int m=max(xia); //找内存中距离最远的页面
				taotai=neicun[m]; //记录要淘汰的页面
				neicun[m]=zouxiang[i]; //把距离最远的页面换出去
			}
			xianshi();
            if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
                printf(" 未命中 ");
                printf("\n");
			}
			else
			{
                printf(" 未命中 ");
                printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，就直接显示
		{
			xianshi();
			if (taotai==-1) //如果此时内存不满
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
			}
		    printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
    mulu();
}

void FIFO() //先进先出
{
	int i=0,j=0;
    int taotai=-1; //要淘汰的页面
	queyeshu=0; //缺页个数
	queue<int>duilie; //队列初始化
	while (i<yemianshu) //对页面走向逐个访问
	{
		printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
                j++;
				duilie.push(zouxiang[i]); //页面入队
			}
			else //内存满，找页面换出
			{
				for (int k=0;k<wulikuai;k++) //遍历现有内存
				{
					if (neicun[k]==duilie.front()) //找到队列第一个被放入的页面，在内存中的位置，淘汰
					{
						taotai=neicun[k]; //记录要淘汰的页面
						neicun[k]=zouxiang[i]; //把第一个放入的页面换出去
						duilie.pop(); //从队列中移除
						duilie.push(zouxiang[i]); //页面入队
						break;
					}
				}
			}
			xianshi();
            if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
                printf(" 未命中 ");
                printf("\n");
			}
			else
			{
                printf(" 未命中 ");
                printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，就直接显示
		{
			xianshi();
			if (taotai==-1) //如果此时内存不满
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
			}
            printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
	memset(neicun,-1,sizeof(int) * wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
    mulu();
}   

void LRU() //最近最久未使用
{
	int i=0,j=0;
	int taotai=-1; //要淘汰的页面
	queyeshu=0; //缺页个数
	while (i<yemianshu) //对页面走向逐个访问
	{
        printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
				j++;
			}
			else //内存满，找页面换出
			{
				for (int k=0;k<wulikuai;k++) //遍历现有内存
				{
					shang[k]=shangjuli(i-1,neicun[k],zouxiang); //统计当前内存与上一次的距离
				}
				int m=max(shang); //找内存中距离最远的页面(最久未访问)
				taotai=neicun[m]; //记录要淘汰的页面
				neicun[m]=zouxiang[i]; //把距离最远的页面换出去
			}
			xianshi();
            if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
                printf(" 未命中 ");
                printf("\n");
			}
			else
			{
                printf(" 未命中 ");
                printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，就直接显示
		{
			xianshi();
            if (taotai==-1) //如果此时内存不满
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
			}
		    printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
    mulu();
} 

void CLOCK() //时钟置换
{
	int i=0,j=0;
	int taotai=-1; //要淘汰的页面
	int f=0; //访问位的下标
	queyeshu=0; //缺页个数
	while (i<yemianshu) //对页面走向逐个访问
	{
        printf("访问%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //页面不在内存中
		{
			if (j<wulikuai) //内存不满
			{
				neicun[j]=zouxiang[i]; //页面直接进入内存
                fangwen[j]=1; //访问位改为1
				f=j;
				j++;
			}
			else //内存满，找页面换出
			{
				while(true) //遍历现有内存的访问位
				{
					if (fangwen[f]==0) //访问位是0，就淘汰
					{
                        taotai=neicun[f];
						break;
					}
					if (fangwen[f]==1) //扫描时发现访问位是1，就改成0
					{
                        fangwen[f]=0;
					}
					if (f==wulikuai) //如果指到访问位末尾，就从头开始
					{
						f=0;
					}
					else
					{
                        f++;
					}
				}
				neicun[f]=zouxiang[i]; //进入内存
				fangwen[f]=1; //进入内存的页面，访问位改为1
			}
			xianshi();
            if (taotai==-1) //内存不满的时候进去的，没有淘汰页面
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
                printf(" 未命中 ");
                printf("\n");
			}
			else
			{
                printf(" 未命中 ");
                printf("淘汰%d\n",taotai);
			}
			queyeshu++; //统计缺页数
		}
		else //页面在内存中，访问位改成1，显示内存
		{
			f=zhao(neicun,zouxiang[i]); //找到这个页面的下标
			fangwen[f]=1; //访问位改成1
			xianshi();
            if (taotai==-1) //如果此时内存不满
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //输出空格，为了使页面美观
				}
			}
		    printf(" 命中\n");
		}
		i++; //一个页面访问完成，进行下一个页面
		f++; //指向下一个访问位
        if (f==wulikuai) //如果指到访问位末尾，就从头开始
		{
			f=0;
		}
	}
	printf("缺页次数:%d\n",queyeshu);
	printf("缺页率:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset是在一段内存块中填充给定的值，对指针初始化
    mulu();
}

void mulu()
{
    int xuan; //菜单选择的功能号
    printf("\n-----功能菜单-----\n");
    printf("1*输入\n");
    printf("2*OPT页面置换算法\n");
    printf("3*FIFO页面置换算法\n");
    printf("4*LRU页面置换算法\n");
    printf("5*CLOCK页面置换算法\n");
    printf("6*退出\n");
    printf("------------------\n");
	printf("选择:");
    scanf("%d",&xuan);
    switch(xuan) {
        case 1:shuru();
               break;
        case 2:printf("\nOPI算法:\n");
			   OPT();
               break;
        case 3:printf("\nFIFO算法:\n");
			   FIFO();
               break;
        case 4:printf("\nLRU算法:\n");
			   LRU();
               break;
        case 5:printf("\nCLOCK算法:\n");
			   CLOCK();
               break;
        default:exit(1); //程序结束
	}
}

void main()
{
	shuru(); //输入
}