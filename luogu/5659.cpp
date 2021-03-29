/***************************************************************
	File name: 5659.cpp
	Author: huhao
	Create time: Mon 25 Nov 2019 03:09:57 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
using namespace std;
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
namespace run
{
	const int N=4010;
	int n,begin[N],next[N],to[N],e,p[N],w[N],f[N],vis[N],pre[N],us[N],in[N],out[N],id[N],od[N];
	int add(int u,int v){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; return e; }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void clear()
	{
#define M(a) memset(a,0,sizeof(a))
		n=0; e=1;
		M(begin); M(next); M(to); M(p); M(w); M(f); M(vis); M(pre); M(us); M(in); M(out); M(id); M(od);
#undef M
	}
	int getf(int x){ return x==f[x]?x:f[x]=getf(f[x]); }
	int cmp(int a,int b,int c,int d)
	{
		return (a==c&&b==d)||(a==d&&b==c);
	}
	void dfs(int u)
	{
		int v;
		vis[u]=1;
		fo(i,u)
		{
			v=to[i];
			if(((od[u]!=1&&in[u]&&out[u]&&cmp(getf(pre[u]),getf(i),getf(in[u]),getf(out[u]))))||w[i]||vis[v]||(pre[u]&&(getf(pre[u]^1)==getf(i^1)))) continue;
			pre[v]=i;
			dfs(v);
		}
	}
	int main()
	{
		clear();
		n=read();
		fr(i,1,n) p[i]=read();
		fr(i,1,n*2) f[i]=i;
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			f[getf(add(u,v))]=getf(add(v,u));
		}
		fr(i,1,n)
		{
			fr(j,1,n)
			{
				vis[j]=pre[j]=0;
				id[j]=od[j]=0;
			}
			fr(j,1,n) fo(k,j) if(!w[k])
			{
				od[j]++; id[to[k]]++;
//				printf("%d %d\n",j,to[k]);
			}
			vis[p[i]]=1;
			fo(j,p[i]) if(!w[j]&&(!in[p[i]]||od[p[i]]==1||getf(in[p[i]])!=getf(j))){ pre[to[j]]=j; dfs(to[j]); }
			int ans=n+1;
			fr(j,1,n) if(vis[j]&&j!=p[i]&&(!out[j]||id[j]==1||getf(out[j])!=getf(pre[j]))&&!us[j]){ ans=j; break; }
//			fr(j,1,n) printf("%d%c",out[j],j==n?'\n':' ');
			printf("%d%c",ans,i==n?'\n':' ');
			assert(ans<=n);
			in[ans]=pre[ans]; w[pre[ans]]=1; us[ans]=1;
			int lst=ans;
			ans=to[pre[ans]^1];
			while(ans!=p[i])
			{
				assert(ans);
//				printf("%d ",ans);
				w[pre[ans]]=1; f[getf(pre[ans])]=getf(pre[lst]);
				lst=ans; ans=to[pre[ans]^1];
			}
//			putchar(10);
			out[p[i]]=pre[lst];
		}
		return 0;
	}
}
int main()
{
	fr(t,1,read()) run::main();
	return 0;
}
