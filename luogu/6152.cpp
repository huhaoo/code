/***************************************************************
	File name: 6152.cpp
	Author: huhao
	Create time: Tue 26 May 2020 07:07:10 PM CST
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
#include<map>
#include<set>
#include<vector>
#define pii std::pair<int,int>
const int N=200010,M=20000000,L=20;
int n;
namespace seg
{
	int m,s[M][2];
	int w[M];
	int clone(int k){ m++; w[m]=w[k]; s[m][0]=s[k][0]; s[m][1]=s[k][1]; return m; }
	int modify(int k,int l,int r,int L,int R,int v)
	{
		if(l>R||L>r) return k;
		k=clone(k);
		if(L<=l&&r<=R){ w[k]+=v; return k; }
		int mid=(l+r)>>1;
		s[k][0]=modify(s[k][0],l,mid,L,R,v); s[k][1]=modify(s[k][1],mid+1,r,L,R,v);
		return k;
	}
	int merge(int l,int r)
	{
		if(!l||!r) return l+r;
		l=clone(l); w[l]+=w[r];
		s[l][0]=merge(s[l][0],s[r][0]); s[l][1]=merge(s[l][1],s[r][1]);
		return l;
	}
	int query(int k,int l,int r,int p)
	{
		if(l==r||!k) return w[k];
		int mid=(l+r)>>1;
		return w[k]+(p<=mid?query(s[k][0],l,mid,p):query(s[k][1],mid+1,r,p));
	}
}
int r[N];
namespace sam
{
	int lst,cnt,f[N],l[N];
	std::map<int,int> t[N];
	void init(){ fr(i,1,cnt){ l[i]=f[i]=0; t[i].clear(); } lst=cnt=1; }
	int add(int c)
	{
		int p=lst,np=++cnt,q,nq;
		l[np]=l[p]+1; lst=cnt;
		while(p&&!t[p][c]){ t[p][c]=np; p=f[p]; }
		if(!p){ f[np]=1; return np; }
		q=t[p][c];
		if(l[p]+1==l[q]){ f[np]=q; return np; }
		nq=++cnt; t[nq]=t[q]; l[nq]=l[p]+1; f[nq]=f[q]; f[q]=f[np]=nq;
		while(p&&t[p][c]==q){ t[p][c]=nq; p=f[p]; }
		return np;
	}
}
int a[N],f[N][L+2];
std::vector<pii> A[N];
namespace lct
{
	int f[N],s[N][2],lst[N],dif[N],tag[N];
	int isroot(int u){ return s[f[u]][0]!=u&&s[f[u]][1]!=u; }
	int wson(int u){ return s[f[u]][1]==u; }
	void rotate(int u)
	{
		int F=f[u],o=wson(u);
		if(!isroot(F)) s[f[F]][wson(F)]=u;
		f[u]=f[F]; f[F]=u; f[s[u][o^1]]=F; s[F][o]=s[u][o^1]; s[u][o^1]=F;
	}
	void Tag(int u,int v){ tag[u]=std::min(tag[u],v); lst[u]=std::min(lst[u],v); }
	void pushdown(int u)
	{
		if(tag[u]!=n+1){ Tag(s[u][0],tag[u]); Tag(s[u][1],tag[u]); }
		tag[u]=n+1;
	}
	void splay(int u)
	{
		while(!isroot(u))
		{
			if(!isroot(f[u])) rotate(wson(u)==wson(f[u])?f[u]:u);
			rotate(u);
		}
	}
	void access(int u,int p)
	{
		static int S[N],T; S[T=1]=u; int o=u;
		while(f[o]) S[++T]=(o=f[o]);
		while(T) pushdown(S[T--]);
		int v=0;
		for(;u;u=f[u])
		{
			if(v)
			{
				int L=::sam::l[u];
				if(u!=1&&lst[u]+L<=n)
				{
					r[p]=::seg::modify(r[p],1,n,lst[u]+L-1,dif[u]+L-2,1);
					A[u].push_back(pii(p,lst[u]+L-1));
					dif[u]=lst[u];
				}
			}
			splay(u); s[u][1]=v; v=u;
		}
		Tag(v,p);
	}
}
int q,p[N];
int query(int u,int v,int m)
{
	int o=p[m];
	fd(i,L,0) if(sam::l[f[o][i]]>=v-m+1) o=f[o][i];
	if(sam::l[o]!=v-m+1) return 0;
	return (std::upper_bound(A[o].begin(),A[o].end(),pii(u,0)))->second<=v;
}
#define echo fprintf(stderr,"echo\n")
#define Echo fprintf(stderr,"Echo\n")
void write(int u)
{
	static int s[N],t; t=0;
	while(u){ s[++t]=u%10; u/=10; }
	if(!t) s[t=1]=0;
	while(t) putchar(s[t--]+'0');
	putchar(10);
}
int main()
{
//	freopen("/home/huhao/in","r",stdin); freopen("/dev/null","w",stdout);
	sam::init(); n=read(); q=read();
	fr(i,1,n) a[i]=read();
	fd(i,n,1) p[i]=sam::add(a[i]);
	fr(i,1,sam::cnt){ f[i][0]=lct::f[i]=sam::f[i]; lct::lst[i]=lct::dif[i]=lct::tag[i]=n+1; }
	fr(j,1,L) fr(i,1,sam::cnt) f[i][j]=f[f[i][j-1]][j-1];
	fd(i,n,1) lct::access(p[i],i);
	fr(i,1,sam::cnt){ A[i].push_back(pii(n+1,n+1)); std::sort(A[i].begin(),A[i].end()); }
	fd(i,n-1,1) r[i]=seg::merge(r[i],r[i+1]);
	while(q--)
	{
		int u=read(),v=read(),L=u+1,R=v+1;
		while(L<R)
		{
			int mid=(L+R)>>1;
			if(query(u,v,mid)) R=mid;
			else L=mid+1;
		}
		write(seg::query(r[u],1,n,v)+L-u);
	}
	return 0;
}
