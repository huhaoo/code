/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Fri 13 Nov 2020 07:11:22 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=1<<18|10;
namespace seg
{
	int t[N],m[N];
	void build(int k,int l,int r)
	{
		t[k]=N; if(l==r) return ;
		int mid=(l+r)>>1;
		build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	}
	void Tag(int k,int v){ t[k]+=v; m[k]+=v; }
	void pushdown(int k){ Tag(k<<1,m[k]); Tag(k<<1|1,m[k]); m[k]=0; }
	void reset(int k,int l,int r,int p)
	{
		if(l==r){ t[k]=0; return ; }
		int mid=(l+r)>>1;
		pushdown(k);
		if(p<=mid) reset(k<<1,l,mid,p);
		else reset(k<<1|1,mid+1,r,p);
		t[k]=std::min(t[k<<1],t[k<<1|1]);
	}
	void modify(int k,int l,int r,int L,int R,int v)
	{
		if(l>R||L>r) return ;
		if(L<=l&&r<=R){ Tag(k,v); return ; }
		int mid=(l+r)>>1; pushdown(k);
		modify(k<<1,l,mid,L,R,v); modify(k<<1|1,mid+1,r,L,R,v);
		t[k]=std::min(t[k<<1],t[k<<1|1]);
	}
	int query(int k,int l,int r,int p)
	{
		if(l>p||t[k]) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1; pushdown(k);
		int w=query(k<<1|1,mid+1,r,p);
		if(w) return w;
		else return query(k<<1,l,mid,p);
	}
}
const int L=18;
int n,p[N];
int f[N],m,op[N];
int F[N][L+2],d[N];
int l[N],r[N];
void build()
{
	m=n;
	static int s1[N],s2[N],t1,t2,s[N],t;
	seg::build(1,1,n); seg::reset(1,1,n,1); s1[t1=1]=s2[t2=1]=s[t=1]=1;
	fr(i,1,n) l[i]=r[i]=i;
	fr(i,2,n)
	{
		seg::modify(1,1,n,1,i-1,-1); seg::reset(1,1,n,i);
		while(t1&&p[s1[t1]]>p[i])
		{
			seg::modify(1,1,n,s1[t1-1]+1,s1[t1],p[s1[t1]]-p[i]); t1--;
		}
		while(t2&&p[s2[t2]]<p[i])
		{
			seg::modify(1,1,n,s2[t2-1]+1,s2[t2],p[i]-p[s2[t2]]); t2--;
		}
		s1[++t1]=s2[++t2]=s[++t]=i;
		int p;
		while((p=seg::query(1,1,n,l[s[t]]-1)))
		{
			if(op[s[t-1]]&&l[s[t-1]]<p)
			{
				f[s[t]]=s[t-1]; r[s[t-1]]=r[s[t]]; t--;
			}
			else
			{
				m++; r[m]=r[s[t]];
				while(1)
				{
					f[s[t]]=m; l[m]=l[s[t]]; op[m]++;
					if(l[s[t]]<=p){ t--; break; }
					t--;
				}
				s[++t]=m; if(op[m]==2) op[m]=1; else op[m]=0;
			}
		}
	}
	fr(i,1,m) if(!d[i])
	{
		int u=i;
		while(u&&!d[u]){ u=f[u]; d[i]++; }
		if(u) d[i]+=d[u];
		while(u&&!d[f[u]]){ d[f[u]]=d[u]-1; u=f[u];  }
	}
	fr(i,1,m) F[i][0]=f[i];
	fr(j,1,L) fr(i,1,m) F[i][j]=F[F[i][j-1]][j-1];
}
int lca(int &u,int &v)
{
	if(d[u]>d[v]){ fd(i,L,0) if(d[F[u][i]]>=d[v]) u=F[u][i]; }
	else{ fd(i,L,0) if(d[F[v][i]]>=d[u]) v=F[v][i]; }
	if(u==v) return u;
	fd(i,L,0) if(F[u][i]!=F[v][i]){ u=F[u][i]; v=F[v][i]; }
	return F[u][0];
}
int main()
{
	n=read();
	fr(i,1,n) p[i]=read();
	build();
	fr(q,1,read())
	{
		int u=read(),v=read();
		int w=lca(u,v);
		if(op[w]) printf("%d %d\n",l[u],r[v]);
		else printf("%d %d\n",l[w],r[w]);
	}
	return 0;
}
