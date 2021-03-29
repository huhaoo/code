/***************************************************************
	File name: insider.cpp
	Author: huhao
	Create time: Thu 29 Oct 2020 11:00:49 AM CST
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
#include<set>
#include<vector>
#include<queue>
#define pii std::pair<int,int>
const int N=100010;
int n,m,a[N],b[N],c[N],d[N],p[N],vis[N],P[N];
std::set<pii> s;
std::vector<int> t[N];
int D=2,_D=2;
int operator<<(std::vector<int> &a,int b){ a.push_back(b); return b; }
void modify(int u,int c){ s.erase(pii(d[u],u)); d[u]+=c; s.insert(pii(d[u],u)); }
int main()
{
	freopen("insider.in","r",stdin); freopen("insider.out","w",stdout);
	n=read(); m=read();
	fr(i,1,m){ a[i]=read(); b[i]=read(); c[i]=read(); d[a[i]]--; d[b[i]]+=D; d[c[i]]--; t[a[i]]<<(t[b[i]]<<(t[c[i]]<<i)); }
	fr(i,1,n) s.insert(pii(d[i],i));
	fr(T,1,n)
	{
		int u=s.begin()->second; vis[u]=1; s.erase(s.begin());
		p[T]=u;
		for(auto i:t[u]) if(!P[i])
		{
			int va=vis[a[i]],vb=vis[b[i]],vc=vis[c[i]];
			if(u==a[i])
			{
				if(vc){ if(!vb){ modify(b[i],1); P[i]=1; } }
				else{ modify(c[i],_D+1); modify(b[i],-D-_D); }
			}
			else if(u==b[i])
			{
				if(va){ modify(c[i],-_D-1); }
				else if(vc){ modify(a[i],-_D-1); }
				else{ modify(a[i],1); modify(c[i],1); P[i]=1; }
			}
			else
			{
				if(va){ if(!vb){ modify(b[i],1); P[i]=1; } }
				else{ modify(a[i],_D+1); modify(b[i],-D-_D); }
			}
		}
	}
	fr(i,1,n) printf("%d%c",p[i],i==n?'\n':' ');
/*	int _s=0;
	static int id[N];
	fr(i,1,n) id[p[i]]=i;
	fr(i,1,m) _s+=((id[a[i]]<id[b[i]])==(id[b[i]]<id[c[i]]));
	printf("%d\n",_s);*/
	return 0;
}
