//��һ�⣬ģ��ʵ��ҳʽ����洢����ҳ���û��㷨��OPT�㷨��FIFO�㷨��LRU�㷨��CLOCK�㷨
#include <stdio.h>
#include <queue> //����
using namespace std;

int wulikuai; //�������
int yemianshu; //ҳ����
int queyeshu; //ȱҳ��
int zouxiang[100]; //ҳ����������
int *neicun; //�ڴ��е������
int *xia; //��ǰ�ڴ�����һ�εľ���
int *shang; //��ǰ�ڴ�����һ�εľ���
int *fangwen; //����clock��������λ

void mulu(); //����Ŀ¼����

void shuru() //����
{
    printf("-----ģ��ʵ��ҳʽ����洢����ҳ���û��㷨-----\n");	
	printf("ҳ����:");
	scanf("%d",&yemianshu);
	printf("ҳ������:");
	for (int i=0;i<yemianshu;i++) {
		scanf("%d",&zouxiang[i]);
	}
    printf("�������:");
	scanf("%d",&wulikuai);
    neicun=(int*)malloc(sizeof(int)*wulikuai); //ָ���������ռ�
	xia=(int*)malloc(sizeof(int)*wulikuai);
	shang=(int*)malloc(sizeof(int)*wulikuai);
	fangwen=(int*)malloc(sizeof(int)*wulikuai);
	mulu();
}

void xianshi() //��ʾ�����ڴ��е������
{
	for (int i=0;i<wulikuai;i++) //���������ڴ�
	{
		if (neicun[i]>=0) //������
			printf("%d ",neicun[i]);
	}
}

int zhao(int *a,int x) //��һ�´����ҳ���Ƿ����ڴ���
{
	for (int i=0;i<wulikuai;i++) //���������ڴ�
	{
		if (x==a[i]) //�ҵ�
		{
			return i;
		}	
	}
	return -1; //�ڴ���û�У�����-1
}

int xiajuli(int i,int j,int* a) //ͳ���ڴ��е�ĳ��ҳ�棬����һ�γ��ֵľ���
{ //i��ʾ��ҳ��������ĵڼ���ҳ�濪ʼ������j���ڴ��е�ĳ��ҳ�棬a��ҳ������
	int juli=0; 
	while (i<yemianshu&&j!=a[i]) //��ҳ������������������Ҳ�ƥ��ʱ
	{  
		juli++; //����������
		i++; //��һ��ҳ��
	}
	if (i>=yemianshu) //ҳ�����������꣬˵��û�ҵ�ƥ���
		return juli+1;
	else //û�����꣬�ҵ�ƥ���
		return juli; 
}

int shangjuli(int i,int j,int*a) //ͳ���ڴ��е�ĳ��ҳ�棬����һ�γ��ֵľ���
{ //i��ʾ��ҳ��������ĵڼ���ҳ�濪ʼ������j���ڴ��е�ĳ��ҳ�棬a��ҳ������
	int juli=0;
	while (i>=0&&j!=a[i]) //��ҳ�������������ǰ�������Ҳ�ƥ��ʱ
	{
		juli++; //����������
		i--; //��һ��ҳ��
	}
	if (i<0) //ҳ�����������꣬˵��û�ҵ�ƥ���
		return juli+1;
	else //û�����꣬�ҵ�ƥ���
		return juli;
}

int max(int *a) //������һ������������
{
	int k=0;
	int max=a[0];
	for (int i=1;i<wulikuai;i++) //���������ڴ�
	{
		if (a[i]>max)
		{
			max=a[i];
			k=i;
		}
	}
	return k; //�������ֵ���±�
}

void OPT() //����û�
{
	int i=0,j=0;
    int taotai=-1; //Ҫ��̭��ҳ��
	queyeshu=0; //ȱҳ����
	while (i<yemianshu) //��ҳ�������������
	{
        printf("����%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //ҳ�治���ڴ���
		{  
			if (j<wulikuai) //�ڴ治��
			{
				neicun[j]=zouxiang[i]; //ҳ��ֱ�ӽ����ڴ�
                j++;
			}
			else //�ڴ�������ҳ�滻��
			{
				for (int k=0;k<wulikuai;k++) //���������ڴ�
				{
					xia[k]=xiajuli(i+1,neicun[k],zouxiang); //ͳ�Ƶ�ǰ�ڴ�����һ�εľ���
				}
				int m=max(xia); //���ڴ��о�����Զ��ҳ��
				taotai=neicun[m]; //��¼Ҫ��̭��ҳ��
				neicun[m]=zouxiang[i]; //�Ѿ�����Զ��ҳ�滻��ȥ
			}
			xianshi();
            if (taotai==-1) //�ڴ治����ʱ���ȥ�ģ�û����̭ҳ��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
                printf(" δ���� ");
                printf("\n");
			}
			else
			{
                printf(" δ���� ");
                printf("��̭%d\n",taotai);
			}
			queyeshu++; //ͳ��ȱҳ��
		}
		else //ҳ�����ڴ��У���ֱ����ʾ
		{
			xianshi();
			if (taotai==-1) //�����ʱ�ڴ治��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
			}
		    printf(" ����\n");
		}
		i++; //һ��ҳ�������ɣ�������һ��ҳ��
	}
	printf("ȱҳ����:%d\n",queyeshu);
	printf("ȱҳ��:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset����һ���ڴ������������ֵ����ָ���ʼ��
    mulu();
}

void FIFO() //�Ƚ��ȳ�
{
	int i=0,j=0;
    int taotai=-1; //Ҫ��̭��ҳ��
	queyeshu=0; //ȱҳ����
	queue<int>duilie; //���г�ʼ��
	while (i<yemianshu) //��ҳ�������������
	{
		printf("����%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //ҳ�治���ڴ���
		{
			if (j<wulikuai) //�ڴ治��
			{
				neicun[j]=zouxiang[i]; //ҳ��ֱ�ӽ����ڴ�
                j++;
				duilie.push(zouxiang[i]); //ҳ�����
			}
			else //�ڴ�������ҳ�滻��
			{
				for (int k=0;k<wulikuai;k++) //���������ڴ�
				{
					if (neicun[k]==duilie.front()) //�ҵ����е�һ���������ҳ�棬���ڴ��е�λ�ã���̭
					{
						taotai=neicun[k]; //��¼Ҫ��̭��ҳ��
						neicun[k]=zouxiang[i]; //�ѵ�һ�������ҳ�滻��ȥ
						duilie.pop(); //�Ӷ������Ƴ�
						duilie.push(zouxiang[i]); //ҳ�����
						break;
					}
				}
			}
			xianshi();
            if (taotai==-1) //�ڴ治����ʱ���ȥ�ģ�û����̭ҳ��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
                printf(" δ���� ");
                printf("\n");
			}
			else
			{
                printf(" δ���� ");
                printf("��̭%d\n",taotai);
			}
			queyeshu++; //ͳ��ȱҳ��
		}
		else //ҳ�����ڴ��У���ֱ����ʾ
		{
			xianshi();
			if (taotai==-1) //�����ʱ�ڴ治��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
			}
            printf(" ����\n");
		}
		i++; //һ��ҳ�������ɣ�������һ��ҳ��
	}
	printf("ȱҳ����:%d\n",queyeshu);
	printf("ȱҳ��:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
	memset(neicun,-1,sizeof(int) * wulikuai); //memset����һ���ڴ������������ֵ����ָ���ʼ��
    mulu();
}   

void LRU() //������δʹ��
{
	int i=0,j=0;
	int taotai=-1; //Ҫ��̭��ҳ��
	queyeshu=0; //ȱҳ����
	while (i<yemianshu) //��ҳ�������������
	{
        printf("����%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //ҳ�治���ڴ���
		{
			if (j<wulikuai) //�ڴ治��
			{
				neicun[j]=zouxiang[i]; //ҳ��ֱ�ӽ����ڴ�
				j++;
			}
			else //�ڴ�������ҳ�滻��
			{
				for (int k=0;k<wulikuai;k++) //���������ڴ�
				{
					shang[k]=shangjuli(i-1,neicun[k],zouxiang); //ͳ�Ƶ�ǰ�ڴ�����һ�εľ���
				}
				int m=max(shang); //���ڴ��о�����Զ��ҳ��(���δ����)
				taotai=neicun[m]; //��¼Ҫ��̭��ҳ��
				neicun[m]=zouxiang[i]; //�Ѿ�����Զ��ҳ�滻��ȥ
			}
			xianshi();
            if (taotai==-1) //�ڴ治����ʱ���ȥ�ģ�û����̭ҳ��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
                printf(" δ���� ");
                printf("\n");
			}
			else
			{
                printf(" δ���� ");
                printf("��̭%d\n",taotai);
			}
			queyeshu++; //ͳ��ȱҳ��
		}
		else //ҳ�����ڴ��У���ֱ����ʾ
		{
			xianshi();
            if (taotai==-1) //�����ʱ�ڴ治��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
			}
		    printf(" ����\n");
		}
		i++; //һ��ҳ�������ɣ�������һ��ҳ��
	}
	printf("ȱҳ����:%d\n",queyeshu);
	printf("ȱҳ��:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset����һ���ڴ������������ֵ����ָ���ʼ��
    mulu();
} 

void CLOCK() //ʱ���û�
{
	int i=0,j=0;
	int taotai=-1; //Ҫ��̭��ҳ��
	int f=0; //����λ���±�
	queyeshu=0; //ȱҳ����
	while (i<yemianshu) //��ҳ�������������
	{
        printf("����%d  ",zouxiang[i]);
		if (zhao(neicun,zouxiang[i])==-1) //ҳ�治���ڴ���
		{
			if (j<wulikuai) //�ڴ治��
			{
				neicun[j]=zouxiang[i]; //ҳ��ֱ�ӽ����ڴ�
                fangwen[j]=1; //����λ��Ϊ1
				f=j;
				j++;
			}
			else //�ڴ�������ҳ�滻��
			{
				while(true) //���������ڴ�ķ���λ
				{
					if (fangwen[f]==0) //����λ��0������̭
					{
                        taotai=neicun[f];
						break;
					}
					if (fangwen[f]==1) //ɨ��ʱ���ַ���λ��1���͸ĳ�0
					{
                        fangwen[f]=0;
					}
					if (f==wulikuai) //���ָ������λĩβ���ʹ�ͷ��ʼ
					{
						f=0;
					}
					else
					{
                        f++;
					}
				}
				neicun[f]=zouxiang[i]; //�����ڴ�
				fangwen[f]=1; //�����ڴ��ҳ�棬����λ��Ϊ1
			}
			xianshi();
            if (taotai==-1) //�ڴ治����ʱ���ȥ�ģ�û����̭ҳ��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
                printf(" δ���� ");
                printf("\n");
			}
			else
			{
                printf(" δ���� ");
                printf("��̭%d\n",taotai);
			}
			queyeshu++; //ͳ��ȱҳ��
		}
		else //ҳ�����ڴ��У�����λ�ĳ�1����ʾ�ڴ�
		{
			f=zhao(neicun,zouxiang[i]); //�ҵ����ҳ����±�
			fangwen[f]=1; //����λ�ĳ�1
			xianshi();
            if (taotai==-1) //�����ʱ�ڴ治��
			{
                for (int k=j;k<wulikuai;k++)
				{
				    printf("  "); //����ո�Ϊ��ʹҳ������
				}
			}
		    printf(" ����\n");
		}
		i++; //һ��ҳ�������ɣ�������һ��ҳ��
		f++; //ָ����һ������λ
        if (f==wulikuai) //���ָ������λĩβ���ʹ�ͷ��ʼ
		{
			f=0;
		}
	}
	printf("ȱҳ����:%d\n",queyeshu);
	printf("ȱҳ��:%.2f%%\n",(1.0*queyeshu/yemianshu)*100);
    memset(neicun,-1,sizeof(int)*wulikuai); //memset����һ���ڴ������������ֵ����ָ���ʼ��
    mulu();
}

void mulu()
{
    int xuan; //�˵�ѡ��Ĺ��ܺ�
    printf("\n-----���ܲ˵�-----\n");
    printf("1*����\n");
    printf("2*OPTҳ���û��㷨\n");
    printf("3*FIFOҳ���û��㷨\n");
    printf("4*LRUҳ���û��㷨\n");
    printf("5*CLOCKҳ���û��㷨\n");
    printf("6*�˳�\n");
    printf("------------------\n");
	printf("ѡ��:");
    scanf("%d",&xuan);
    switch(xuan) {
        case 1:shuru();
               break;
        case 2:printf("\nOPI�㷨:\n");
			   OPT();
               break;
        case 3:printf("\nFIFO�㷨:\n");
			   FIFO();
               break;
        case 4:printf("\nLRU�㷨:\n");
			   LRU();
               break;
        case 5:printf("\nCLOCK�㷨:\n");
			   CLOCK();
               break;
        default:exit(1); //�������
	}
}

void main()
{
	shuru(); //����
}