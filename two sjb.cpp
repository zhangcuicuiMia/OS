#include<stdio.h>

struct Date
{
	int hour;
	int minute;
};
struct Jcb
{
	int no;
	Date enter;
	int operation;
	Date start;
	Date over;
	int turnover;
	double weighted;
	int state;
};

void display(Jcb J[],int n);
void mulfc(Jcb J[],int n);


int main()

{

	int n=4;

	int n0,n1,n2,n3;

	Jcb job[20],job1[20],job2[20],job3[20];


	scanf("%d", &n0);
	job[0].no=1;
	scanf("%d%d%d",&job[0].enter.hour, &job[0].enter.minute, &job[0].operation);
		

	scanf("%d", &n1);
	job1[0]=job[0];
	job1[1].no=2;
	scanf("%d%d%d",&job1[1].enter.hour, &job1[1].enter.minute, &job1[1].operation);

	scanf("%d", &n2);
	job2[0]=job[0];
	job2[1]=job1[1];
	job2[2].no=3;
	scanf("%d%d%d",&job2[2].enter.hour, &job2[2].enter.minute, &job2[2].operation);

	scanf("%d", &n3);
	job3[0]=job[0];
	job3[1]=job1[1];
	job3[2]=job2[2];
	job3[3].no=4;
	scanf("%d%d%d",&job3[3].enter.hour, &job3[3].enter.minute, &job3[3].operation);

	mulfc(job3,n3);
	return 0;
}


void display(Jcb J[],int n)
{
	
	double T=0,W=0;
	
	printf("作业   作业进入时间 估计运行时间(分钟) 开始时间 结束时间 周转时间(分钟)带权周转时间\n");
	
	for(int i=0;i<n;i++)
		
	{
		
		J[i].turnover=(J[i].over.hour*60 +J[i].over.minute)-(J[i].enter.hour*60+J[i].enter.minute);
		
		T+=J[i].turnover;
		
		J[i].weighted=J[i].turnover/(double)J[i].operation;
		
		W+=J[i].weighted;
		
		printf("JOB%d\t  %2d:%02d\t      %-14d\t%2d:%02d\t %2d:%02d\t   %-6d\t%-5.2f\t\n",J[i].no,J[i].enter.hour, J[i].enter.minute,J[i].operation, J[i].start.hour,J[i].start.minute,J[i].over.hour, J[i].over.minute, J[i].turnover,J[i].weighted);
		
	}
	
	T/=n;
	
	W/=n;
	
	printf("作业平均周转时间 T=%.2lf 分钟\n", T);
	
	printf("作业带权平均周转时间W=%.3lf\n\n\n",W);
	
}




void mulfc(Jcb J[],int n)

{

	printf("两道批处理系统中最短作业优先作业调度算法\n");

	int op[20];

	int i,work1=-1,work2=-1;

	for(i=0;i<n;i++)

	{

		op[i]=J[i].operation;

		J[i].state=0;
	}

	work1=0;

	J[0].state=1;

	J[0].start.hour=J[0].enter.hour;

	J[0].start.minute=J[0].enter.minute;

	work2=1;
	
	int h=J[0].enter.hour;

	int m=J[0].enter.minute;

	int work=work1;
	
	int time;

	int t=2;

	while(t<=n)

	{


		if(J[work1].operation>J[work2].operation)

		{
			op[work1]+=J[work2].operation;

			if(t==2)

				{

					J[work2].start.hour=J[work2].enter.hour;

					J[work2].start.minute=J[work2].enter.minute;

				}

			else

				{

					J[work2].start.hour=h;

					J[work2].start.minute=m;

				}

			J[work2].over.hour=J[work2].start.hour+(J[work2].start.minute+op[work2])/60;

			J[work2].over.minute=(J[work2].start.minute+op[work2])%60;

			h=J[work2].over.hour;

			m=J[work2].over.minute;

			time=h*60+m;

			work2=-1;
		}

		else

			{

				J[work1].over.hour=J[work1].start.hour+(J[work1].start.minute+op[work1])/60;

				J[work1].over.minute=(J[work1].start.minute+op[work1])%60;

				h=J[work2].over.hour;

				m=J[work2].over.minute;

				time=h*60+m;

				J[work2].start.hour=h;

				J[work2].start.minute=m;

				work1=work2;

				work2=-1;

			 }

		int w;

		int i=1;

		while(J[i].state==1)

		{

			i++;

		}
		
		w=i;
		
		for(int j=w; j<n;j++)
			
		{
			
			if((J[j].enter.hour*60+J[j].enter.minute)>time)
				
				break;

			if(J[j].state==0 &&(J[w].operation > J[j].operation))
				
				w=j;
			
		}
		
		
		work2=w;
		
		t++;
		
		J[work2].state=1;
		
} 

J[work1].over.hour=J[work1].start.hour+(J[work1].start.minute+op[work1])/60;

J[work1].over.minute=(J[work1].start.minute+op[work1])%60;

display(J,n);

}
