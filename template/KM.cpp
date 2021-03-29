/***************************************************************
	File name: KM.cpp
	Author: huhao
	Create time: Sat 15 Aug 2020 01:15:31 PM CST
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
const int N=410,inf=1000000000;
int pl[N],pr[N],n,p,a[N][N],visl[N],visr[N],s[N],vl[N],vr[N],pre[N],q[N];
i64 ans,Ans; int _ans[N];
inline bool Min(int &a,int b){ if(a>b){ a=b; return 1; } return 0; }
void update(int u){ fr(i,1,n) if(Min(s[i],vl[u]+vr[i]-a[u][i])) pre[i]=u; }
int main()
{
	p=read(); n=std::max(p,read());
	fr(i,1,read()){ int u=read(),v=read(); a[u][v]=read(); }
	fr(i,1,n) vl[i]=inf;
	fr(t,1,n)
	{
		fr(i,1,n){ s[i]=inf; visl[i]=visr[i]=pre[i]=0; }
		int flag=0;
		fr(i,1,n) if(!pl[i]){ visl[i]=1; update(i); }
		while(!flag)
		{
			int d=inf;
			fr(i,1,n) if(!visr[i]) Min(d,s[i]);
			fr(i,1,n)
			{
				if(visl[i]) vl[i]-=d;
				if(visr[i]) vr[i]+=d; else s[i]-=d;
			}
			fr(i,1,n) if(!s[i]&&!visr[i])
			{
				if(!pr[i])
				{
					int u=i,v=pre[u];
					while(u&&v){ int k=pl[v]; pl[v]=u; pr[u]=v; u=k; v=pre[u]; }
					flag=1; break;
				}
				visr[i]=1; visl[pr[i]]=1; update(pr[i]);
			}
		}
		Ans=0;
		fr(i,1,n) if(pl[i]) Ans+=a[i][pl[i]];
		if(Ans>ans)
		{
			ans=Ans;
			fr(i,1,n) _ans[i]=pl[i];
		}
		else break;
	}
	printf("%lld\n",ans);
	fr(i,1,p) printf("%lld%c",a[i][_ans[i]]?_ans[i]:0ll,i==p?'\n':' ');
	return 0;
}
