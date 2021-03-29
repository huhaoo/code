/***************************************************************
	File name: mole.cpp
	Author: huhao
	Create time: Wed 06 Jan 2021 03:51:27 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#define pii std::pair<int,int>
const int N=1<<18|10;
int n,m,c[N],t[N],T[N];
pii f[N];
int ans;
pii operator+(pii a,int b){ return pii(a.first+b,a.second); }
void update(int u)
{
	if(!u) return ;
	if(c[u]) f[u]=pii(0,u);
	else f[u]=std::min(f[u<<1]+(t[u<<1]?-1:1),f[u<<1|1]+(t[u<<1|1]?-1:1));
	update(u>>1);
}
int main()
{
	freopen("mole.in","r",stdin); freopen("mole.out","w",stdout);
	n=read(); m=read();
	fr(i,1,n) c[i]=read();
	fr(i,n+1,n+n+1) f[i]=pii(N,0);
	fd(i,n,1)
	{
		if(c[i]) f[i]=pii(0,i);
		else f[i]=std::min(f[i<<1]+1,f[i<<1|1]+1);
	}
	fr(i,1,m)
	{
		int p=read(),u=p,d=0,v=u; pii g=f[u];
		while(u)
		{
			if(g>f[u]+d){ g=f[u]+d; v=u; }
			d+=T[u]?-1:1;
			u>>=1;
		}
		printf("%d%c",ans+=g.first,i==m?'\n':' ');
//		fprintf(stderr,"%d %d %d %d\n",p,v,g.first,g.second);
		c[g.second]--;
		u=p; while(u!=v){ if(T[u]) T[u]--; else t[u]++; u>>=1; }
		u=g.second; while(u!=v){ if(t[u]) t[u]--; else T[u]++; u>>=1; }
		update(p); update(g.second);
	}
	return 0;
}
