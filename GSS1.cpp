#include<iostream>
#include<stdio.h>
using namespace std;
int ar[50101],all[250101],lef[250101],righ[250101],ma[250101],l,s,r,m;//cuz i am not iniatialising these so plz check out for any mistakes
void buildtree(int low,int high,int pos)
{
	if(low==high)
	{
		all[pos]=ar[low];
		lef[pos]=ar[low];
		righ[pos]=ar[low];
		ma[pos]=ar[low];
	}
	else
	{
		int mid;
		mid=(low+high)/2;
		buildtree(low,mid,2*pos+1);
		buildtree((mid+1),high,2*pos+2);
		all[pos]=all[2*pos+1]*all[2*pos+2];
		lef[pos]=max(lef[2*pos+1],all[2*pos+1]+lef[2*pos+2]);
		righ[pos]=max(righ[2*pos+2],all[2*pos+2]+righ[2*pos+1]);
		ma[pos]=max(ma[2*pos+1],max(ma[2*pos+2],righ[2*pos+1]+lef[2*pos+2]));
	}
}
void query(int qlow,int qhigh,int low,int high,int pos)
{
	
	if((qlow<=low)&&(qhigh>=high))
	{
		l=lef[pos];
		r=righ[pos];
		s=all[pos];
		m=ma[pos];
		
	}
	else
	{
		int mid;
		mid=(low+high)/2;
		if((qhigh<=mid))//checck out for bugsss
	    {
	    	query(qlow,qhigh,low,mid,2*pos+1);
		}
		else if((qlow>=(mid+1)))//check out for bugsss
		{
			query(qlow,qhigh,mid+1,high,2*pos+2);
		}
		else
		{
				int x1,x2,x3,y1,y2,y3,x4,y4;
			query(qlow,qhigh,low,mid,2*pos+1);
			x1=l;
			x2=r;
			x3=m;
			x4=s;
			query(qlow,qhigh,mid+1,high,2*pos+2);
			y1=l;
			y2=r;
			y3=m;
			y4=s;
			l=max(x1,x4+y1);
			r=max(y2,y4+x2);
			s=x4*y4;
			m=max(x3,max(y3,x2+y1));
			
			
			
		
			
		}
	}
}
int main()
{
	int n,i,q,x,y,mod;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&ar[i]);
		
	}
	cin>>q;
	
	buildtree(0,n-1,0);
	for(i=0;i<q;i++)
	{
		scanf("%d",&x);
		scanf("%d",&y);
		scanf("%d",&mod)
	query(x-1,y-1,0,n-1,0);
	printf("%d\n",s%mod);//do it long long int in case of wrong answer!!!
}
}
