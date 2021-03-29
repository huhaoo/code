/***************************************************************
	File name: 最小费用最大流_CapacityScaling.cpp
	Author: huhao
	Create time: Fri 23 Oct 2020 02:21:31 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#define i64 long long
#define T i64
const int N=100010;
const T inf=1ll<<60,Inf=1ll<<40;
namespace mcmf
{
	int begin[N],next[N],to[N],e=1; T c[N]; i64 w[N];
	int pre[N],vis[N]; T d[N];
	int n;
	void init(){ memset(begin,0,sizeof(begin)); e=1; }
	void add(int u,int v,int W,T C){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; c[e]=C; }
	void Add(int u,int v,int W,T C){ add(u,v,W,C); add(v,u,0,-C); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void spfa(int S)
	{
		fr(i,1,n){ pre[i]=vis[i]=0; d[i]=inf; }
		d[S]=0; vis[S]=1; if(n==1) return ;
		static int q[N],l,r; l=0; r=1; q[0]=S;
		while(l!=r)
		{
			int u=q[l++]; if(l==n) l=0;
			vis[u]=0;
			fo(i,u) if(w[i]&&d[to[i]]>d[u]+c[i])
			{
				d[to[i]]=d[u]+c[i]; pre[to[i]]=i;
				if(!vis[to[i]]){ vis[to[i]]=1; q[r++]=to[i]; if(r==n) r=0; }
			}
		}
	}
	T solve(int _n,int m,int *u,int *v,i64 *W,T *C)
	{
		T ans=0;
		n=_n; init();
		fr(i,1,m) Add(u[i],v[i],0,C[i]);
		fd(t,50,0)
		{
			ans*=2;
			fr(i,2,e) w[i]<<=1;
			fr(i,1,m) if(((W[i]>>t)&1))
			{
				if(!w[i<<1])
				{
					spfa(v[i]);
					if(d[u[i]]+C[i]<0)
					{
						w[i<<1|1]++; int p=u[i]; ans+=C[i];
						while(p!=v[i])
						{
							ans+=c[pre[p]]; w[pre[p]]--; w[pre[p]^1]++; p=to[pre[p]^1];
						}
					}
					else w[i<<1]++;
				}
				else w[i<<1]++;
			}
		}
		return ans;
	}
#undef fo
}
T c[N];
#undef T
int n,m,u[N],v[N]; i64 w[N];
int main()
{
	n=read(); m=read();
	u[1]=n; v[1]=1; w[1]=Inf; c[1]=-Inf;
	fr(i,2,m+1){ u[i]=read(); v[i]=read(); w[i]=read(); c[i]=read(); }
	T ans=mcmf::solve(n,m+1,u,v,w,c);
	i64 f=mcmf::w[3];
	printf("%lld %lld\n",f,ans+f*Inf);
	return 0;
}
