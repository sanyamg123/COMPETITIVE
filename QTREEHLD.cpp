/*NAME: SANYAM GARG
INSTITUTION:DELHI TECHNOLOGICAL UNIVERSITY*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<bits/stdc++.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>

#define mod 1000000007
#define lli  int
#define ll int
#define readi(x) scanf("%d",&x)
#define  reads(x)  scanf("%s",&x)
#define readl(x) scanf("%d",&x)
#define rep(i,n) for(i=0;i<n;i++)
#define revp(i,n) for(i=(n-1);i>=0;i--)
#define myrep1(i,a,b) for(i=a;i<=b;i++)
#define myrep2(i,a,b) for(i=b;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define sec second

using namespace std;
vector<list<pair<lli,lli> > > adjlist(10009);
lli siz[10009],special[10009],visited[10009],chno[10009],head[10009],pos[10009],L[10009],ar[10009],seg[40009];
lli P[10009][200];
map<pair<lli,lli> ,lli > my_map;
//dfs 1 is the function that calculate the size of the subtree.NOTE:size of the subtree of an element invcludes the element itself..//siz array
void dfs1(lli i)//just give it dfs1(1) as 1 is the root//visited[1]=1 mark krke bhejna h!//aur baaki visited array 0 hona chahiye pura
{
	ll val=1;
	for(list<pair<lli,lli> > ::iterator it=adjlist[i].begin();it!=adjlist[i].end();it++)
	{
		if(!visited[it->fi])
		{
			L[it->fi]=L[i]+1;//level of 1 is 0!!!	
		visited[it->fi]=1;
		dfs1(it->fi);
		val+=siz[it->fi];
	    }
	}
	siz[i]=val;
}
//dfs2 is the function that computes the special child of each node..//for leaf nodes this value will be -1//special array!
//visited array ko phir se 0 karke bhejna padega idhar!!visited[1]=1;
void dfs2(lli i)
{
	lli val=-1;//val is the measure of subtree size
	lli index=-1;//index is the node number (special)
	for(list<pair<lli,lli> >::iterator it=adjlist[i].begin();it!=adjlist[i].end();it++)
	{
		
		if(!visited[it->fi])
		{
			visited[it->fi]=1;
			dfs2(it->fi);
		if(siz[it->fi]>val)
		{
		
			val=siz[it->fi];
			index=it->fi;
		}
	    }
	    
	}
	special[i]=index;
}
//this function edge will compute three arrays edge_ind ,edge_val and T that is the parent array!!
lli T[10009],edge_ind[10009],edge_val[10009];

//visited array phir se waise hi bhejna hai!!

void edge(lli i)//visited[1]=1;
{
//	cout<<"edge";
	
	for(list<pair<lli,lli> > ::iterator it=adjlist[i].begin();it!=adjlist[i].end();it++)
    {
    //	cout<<(it->fi)<<" ";
    	if(!visited[it->fi])
    	{
    		
    		visited[it->fi]=1;
    		edge(it->fi);
    		//here there may be bugss waise lagta nahi ki positioning ki wajah se problem hogi!!
    		T[it->fi]=i;
    		edge_val[it->fi]=it->sec;//isse ye pata chal jayega ki konse node par kitni value ka edge terminate hoga jisse main agle function mein use karunga
    		edge_ind[my_map[mp(it->fi,i)]]=it->fi;//iske andar hume ye pata chal jayega ki iss number waali edge kis node par terminate karegi aur phir uss node ki main uss array mei position nikal lunga! 
		
		}
	//	cout<<endl;
	}
}





lli ch=1,p=0;//ch stores the position of the node in the array and ch stores the chain number!!
//for each node we will store the chain number of each node in chno array..//we will stoe the address of that node or the position
//of that node in pos array// head of a chain stores the head of the node in the array!!!//phirse visited array bhi bana padega
//ar is the array that stores the complete array on which segtree operations will be applied!!
//head[1]=1;//head of first chain is 1 supposedly!!
void chain(lli i)//visited[1]=1;
{
	chno[i]=ch;
	ar[p]=edge_val[i];//jo edge is par terminate hogi!
	pos[i]=p++;
	if(special[i]!=-1)//leaf node ke liye hum aage nahi jaa payenge!!!
	{
	visited[special[i]]=1;
	chain(special[i]);
     }
	for(list<pair<lli,lli> > ::iterator it=adjlist[i].begin();it!=adjlist[i].end();it++)
	{
		if((!visited[it->fi])&&((it->fi)!=special[i]))
		{
			visited[it->fi]=1;
			ch++;
			head[ch]=it->fi;
			chain(it->fi);
		}
	}
	
}
//now lets build the segtree!!//seg is the segtree array that stores the maximum no. in the array!
void buildtree(lli low,lli high,lli pos)
{
	if(low==high)
	{
	
	seg[pos]=ar[low];
	}
	else
	{
		int mid;
		mid=(low+high)/2;
		buildtree(low,mid,2*pos+1);
		buildtree((mid+1),high,2*pos+2);
		seg[pos]=max(seg[2*pos+1],seg[2*pos+2]);
	}
}
lli query(int start,int end,int low,int high,int pos)
{
	//cout<<"query"<<endl;
	int mid,ans1,ans2;
     if(start>end)
     {
     	return 0;
	 }
	 if((start<=low)&&(end>=high))//complete overlap....
	{
	//	cout<<"quey:"<<seg[pos]<<endl;
		return seg[pos];
	}
	else if((end<low)||(start>high))
	{
		return 0;
	}
	else//partial overlap
	{
		
		mid=(low+high)/2;
		ans1=query(start,end,low,mid,2*pos+1);
		ans2=query(start,end,mid+1,high,2*pos+2);
	//	cout<<"query:"<<max(ans1,ans2)<<endl;;
		return max(ans1,ans2);
	}
}
void update(int low,int high,int pos,int val,int search)
{
	if(low==high)
	{
		
		seg[pos]=val;
	}
	else
	{
		int mid=(low+high)/2;
		if(search>=(mid+1))
		{
			update(mid+1,high,2*pos+2,val,search);
		
		seg[pos]=max(seg[2*pos+1],seg[2*pos+2]);
		}
		else//check for bugsssss
		{
			update(low,mid,2*pos+1,val,search);
		
	    seg[pos]=max(seg[2*pos+1],seg[2*pos+2]);
			
		}
	}
}
//now we are done with the build query and update in segtree of ar!!!!!
///now i have to write a function of query in hld and 2 sparse table functions!!
void buildsparse()
{
	
	ll i,j;
		rep(i,10009)
			{
				rep(j,200)
				{
					P[i][j]=-1;//dekh lio ye waali initialisation!!!//ye basically root node ke liye hai!!
				}
			}
	//n and h both are available over here!!!
	for(i=1;i<10009;i++)
	{
		//cout<<T[i]<<endl;
		//cout<<"hi";
		P[i][0]=T[i];
	//	cout<<P[i][0]<<" ";
	}
//	cout<<"yo";
	//cout<<endl;
	for(j=1 ;1 << j < 10009;j++)
	{
		
    for(i=1;i<10009;i++)
     {
     	if(P[i][j-1]!=-1)
     	{
		 P[i][j]=P[P[i][j-1]][j-1];
	   	
        // cout<<P[i][j]<<" ";
        }
	 }
	 //cout<<endl;
	 
    }
}
ll rmq(ll a,ll b)
{
	ll temp;
	if(L[b]>L[a])
	{
		temp=a;
		a=b;
		b=temp;
	}
	ll log,i;
	//always a will be the bottom element in comparison to b!!!
	for(log=1;(1<<log) <=L[a];log++);
	log--;
//	ye actual height nikal gyi a ki!!
   // cout<<L[a]<<" "<<L[b]<<endl;
    for(i=log;i>=0;i--)
    if(L[a]- (1<<i) >=L[b])
    a=P[a][i];
    //cout<<a<<endl<<endl;
    if(a==b)
    
    return a;
    //cout<<P[5][0]<<endl;
    for(i=log;i>=0;i--)
    	{
    		if(P[a][i]!=P[b][i]&&P[a][i]!=-1&&P[b][i]!=-1)
    		{
    		//	cout<<"yahi hai"<<P[a][i]<<endl;
    			a=P[a][i];
    			b=P[b][i];
			}
		}
	return T[a];    
}
//ab inse lca nikal jayega ab bas query ka answer nikalna hai!!!
lli hld_query(lli a,lli b)
{
	lli lca;
	lca=rmq(a,b);
//	cout<<"lca"<<lca<<endl;
	//now first lets go from a to lca!!!!
	lli temp=a,ans=0;
	
	while(chno[temp]!=chno[lca])//kyunki chno ke andar indexes stored hain!!!
	{
	//	cout<<pos[head[chno[temp]]]<<endl;
		ans=max(ans,query(pos[head[chno[temp]]],pos[temp],0,10008,0));
		temp=T[head[chno[temp]]];
	}
	
	
//	cout<<pos[lca]+1<<" "<<pos[temp]<<endl;
	ans=max(ans,query(pos[lca]+1,pos[temp],0,10008,0));
	temp=b;
	while(chno[temp]!=chno[lca])//kyunki chno ke andar indexes stored hain!!!
	{
		ans=max(ans,query(pos[head[chno[temp]]],pos[temp],0,10008,0));
		temp=T[head[chno[temp]]];
	}
//	cout<<pos[lca]+1<<" "<<pos[temp]<<endl;
	ans=max(ans,query(pos[lca]+1,pos[temp],0,10008,0));
	return ans;
	//then we will go from b to lca!!!!
	
}
int main()
{
//	freopen("input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
	lli t,i,n,a,b,w,ans;
	
	char c[20];
    readl(t);
    while(t--)
    {
    	//cout<<"my_map[mp(1,2)]="<<my_map[mp(1,2)]<<endl;
    	rep(i,10009)
    	{
    		T[i]=-1;
    		ar[i]=0;
    		siz[i]=0;special[i]=0;visited[i]=0;chno[i]=0;head[i]=0;pos[i]=0;L[i]=0;edge_ind[i]=0;edge_val[i]=0;
		}
		rep(i,40009)
		{
			seg[i]=0;
		}
    //	siz[20000],special[20000],visited[20000],chno[20000],head[20000],pos[20000],L[20000]
        ch=1;
        p=0;
    	T[1]=-1;
    	head[1]=1;
    	readl(n);
    	for(i=1;i<=(n-1);i++)
    	{
    		
    		readl(a);
    		readl(b);
    		readl(w);
    		adjlist[a].pb(mp(b,w));
    		adjlist[b].pb(mp(a,w));
    		my_map[mp(a,b)]=i;
    		my_map[mp(b,a)]=i;
		    
		}
	
	//	cout<<"hi";
		rep(i,10009)
		visited[i]=0;
		visited[1]=1;
		dfs1(1);
	//	cout<<"hi";
		rep(i,10009)
		visited[i]=0;
		visited[1]=1;
		dfs2(1);
	//	cout<<"hi";
		rep(i,10009)
		visited[i]=0;
		visited[1]=1;
		edge(1);
//		cout<<"hi";
		rep(i,10009)
		visited[i]=0;
		visited[1]=1;
		chain(1);

//		cout<<"hi";
		buildtree(0,10008,0);//check for bugss in this call
	//	cout<<"hello";
		buildsparse();
//		   for(i=1;i<=11;i++)
//            {
//            	cout<<i<<":"<<ar[i]<<endl;
//			}
			
//		cout<<"hello";
		scanf("%s",&c);
		while(strcmp(c,"DONE")!=0)
		{
			if(strcmp(c,"QUERY")==0)
			{
				readl(a);
				readl(b);
				ans=hld_query(a,b);
				printf("%d\n",ans);
			}
			else
			{
				readl(a);
				readl(b);
//				cout<<"updatepos"<<pos[edge_ind[a]]<<endl;
				update(0,10008,0,b,pos[edge_ind[a]]);
				
			}
//			for(i=0;i<=3;i++)
//			{
//				cout<<"seg"<<i<<":  "<<seg[i];
//			}
//			cout<<endl;
         
			
			scanf("%s",&c);
			
		}
		for(i=0;i<10009;i++)
		{
			adjlist[i].clear();
		}
		//ek baar koi aisa test case bana jo iske bina galat answer de agar abhi bhi wrong answer aaye toh!!
	  my_map.clear();

		
	}
}
	
 
