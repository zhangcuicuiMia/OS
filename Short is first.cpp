#include<iostream> 
using namespace std; 
struct job
 { 
	char name[20]; //作业名 
	int subtime; //提交时间 
	int runtime; //运行时间 
	int stime; //开始时间
	int ftime; //完成时间
	int ztime; //周转时间 
	int wtime; //等待时间 
	double dtime; //带权周转时间
	double rratio; //响应比 
}; 
	int flag=0; 
	double sumztime,sumdtime; 
	double avgztime,avgdtime;
	void input(job *p,int n); 	//输入
	void output(job *p,int n);//输出
	void datahandle(job *p,int n); //数据处理
	void sort(job *p,int n); //按提交时间排序
	void fcfs(job *p,int n); //先来先服务 
	void sjf(job *p,int n); //短作业优先 
	void hrf(job *p,int n); //高响应比优先

int main()
 {
	int n; 
	cout<<"/********** 作业调度算法 ***************/"<<endl; 
	cout<<"输入作业数目： ";
	cin>>n; 
	job *a=new job[n];
	input(a,n);
	fcfs(a,n); 
	cout<<"\n";
	sjf(a,n); 
	cout<<"\n";
	hrf(a,n);
	delete a; 
	return 0;
 } 
void input(job *p,int n)
{
	cout<<"请输入作业信息 :"<<endl<<endl;
	for(int i=0;i<n;i++) 
	{
		cout<<"作业名： ";
		cin>>p[i].name ; 
		cout<<"提交时间： "; 
		cin>>p[i].subtime ;
		p[i].subtime=(p[i].subtime)/100*60+p[i].subtime%100;
		cout<<"运行时间： "; 
		cin>>p[i].runtime ;
		p[i].runtime=(p[i].runtime)/100*60+p[i].runtime%100; 
		cout<<"\n"; 
	}
 }
 void output(job *p,int n) 
 {
	 cout<<"作业调度顺序： "; 
	 for(int k=0;k<n;k++) 
	 {
		 cout<<p[k].name <<" ";
	 }
	 cout<<"\n"; 
	 cout<<"名字\t"<<"进入时间\t"<<"运行时间\t"<<"开始时间\t"<<"结束时间\t"<<"周转时间\t"<<"带权周转时间\t"<<endl;
	 for(int i=0;i<n;i++)
	 { 
	
		 cout<<p[i].name<<"\t"<<p[i].subtime/60*100+p[i].subtime-p[i].subtime/60*60<< "\t\t"; 
		 cout<<p[i].runtime/60*100+p[i].runtime-p[i].runtime/60*60<<"\t\t";
		 cout<<p[i].stime/60*100+p[i].stime-p[i].stime/60*60<<"\t\t"; 
		 cout<<p[i].ftime/60*100+p[i].ftime-p[i].ftime/60*60<<"\t\t";
		 cout<<p[i].ztime/60*100+p[i].ztime-p[i].ztime/60*60<<"\t\t"; 
	
		 cout<<(int)p[i].dtime/60*100+p[i].dtime-((int)p[i].dtime)/60*60<<endl; 
	 }
		 cout<<"平均周转时间 ="<<avgztime<<endl;
		 cout<<"平均带权周转时间 ="<<avgdtime<<endl<<endl; 
} 
void sort(job *p,int n) 
{ 
	for(int i=n-1;i>=1;i--) 
		for(int j=0;j<i;j++)
			if(p[j].subtime >p[j+1].subtime )
			{ 
				job temp; temp=p[j]; 
				p[j]=p[j+1]; p[j+1]=temp;
			} 
} 
void datahandle(job *p,int n) 
{
	sumztime=sumdtime=0; 
	p[0].stime=p[0].subtime; 
	p[0].ftime =p[0].subtime +p[0].runtime ;
	for(int i=1;i<n;i++)
	{
		if(p[i-1].ftime>p[i].subtime) 
		{
			p[i].stime=p[i-1].ftime; 
			p[i].ftime=p[i-1].ftime+p[i].runtime; //下一个的开始时间可能大于上一个的结束时间 
		}
		else
		{
			p[i].stime=p[i].subtime; 
			p[i].ftime=p[i].subtime+p[i].runtime;
		}
 }
	for(int j=0;j<n;j++)
	{
		p[j].ztime =p[j].ftime -p[j].subtime ;
		p[j].dtime =p[j].ztime*1.0 /p[j].runtime*1.0 ;
		sumztime+=p[j].ztime; sumdtime+=p[j].dtime; 
	}
	avgztime=sumztime/n; avgdtime=sumdtime/n; } 
void fcfs(job *p,int n)
 { 
	sort(p,n); datahandle(p,n);
	cout<<"先来先服务算法 "<<endl; 
	output(p,n); 
} 
void sjf(job *p,int n) 
{
	sort(p,n);
	for(int i=0;i<n-1;i++) 
	{
		int k=0;
		if(i==0) 
			p[i].ftime =p[i].subtime +p[i].runtime ; 
		else 
			p[i].ftime =p[i].runtime +p[i-1].ftime ;
		for(int j=i+1;j<n;j++)
		{
			if(p[j].subtime<=p[i].ftime )
				k++;
		} 
		double minstime=p[i+1].runtime;
		int ps=i+1;
		for(int m=i+1;m<i+k;m++)
		{
			if(p[m+1].runtime <minstime) 
			{
				minstime=p[m+1].runtime ; 
				ps=m+1;
			}
		} 
		job temp; 
		temp=p[i+1]; 
		p[i+1]=p[ps]; 
		p[ps]=temp; 
} 
	datahandle(p,n);
	cout<<"短作业优先算法： "<<endl; 
	output(p,n); } 
void hrf(job *p,int n)
 {
	sort(p,n); 
	for(int i=0;i<n-1;i++) 
	{
		int k=0;
		if(i==0) 
			p[i].ftime =p[i].subtime +p[i].runtime ; 
		else 
			p[i].ftime =(p[i].runtime +p[i-1].ftime) ;
		for(int j=i+1;j<n;j++)
		{
			if(p[j].subtime <=p[i].ftime ) k++; 
		}
		double maxrratio=(p[i].ftime -p[i+1].subtime )/(1.0*p[i+1].runtime); 
		
		int ps=i+1; 
		for(int m=i+1;m<i+k;m++)
		{
			if((p[i].ftime -p[m+1].subtime)/p[m+1].runtime >=maxrratio) 
			{
				maxrratio=(p[i].ftime -p[m+1].subtime)/(1.0*p[m+1].runtime); ps=m+1; 
			}
		} 
		job temp; 
		temp=p[i+1]; 
		p[i+1]=p[ps];
		p[ps]=temp; 
	}
	datahandle(p,n); 
	cout<<"高响应比优先算法： "<<endl; 
	output(p,n);
 } 
