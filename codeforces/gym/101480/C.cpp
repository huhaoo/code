/***************************************************************
	File name: C.cpp
	Author: huhao
	Create time: Wed 28 Oct 2020 04:42:22 PM CST
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
const int N=1<<20|10,mx=(1<<20)-1;
#include<vector>
#define pii std::pair<int,int>
int _l[N],_r[N],c[N],n,m,q;
std::vector<int> op[N];
std::vector<int> fl[N];
std::vector<pii> co[N];
int t[N<<1];
std::set<int> s;
void update(int k){ t[k]=t[k<<1]+t[k<<1|1]; }
const int D=0;
int query(int k,int l,int r,int L,int R)
{
	if(D&&k==1) printf("Q %d %d\n",L,R);
	if(l>R||L>r) return 0;
	if(L<=l&&r<=R) return t[k];
	int mid=(l+r)>>1;
	return query(k<<1,l,mid,L,R)+query(k<<1|1,mid+1,r,L,R);
}
void clear(int k,int l,int r)
{
	if(!t[k]) return ;
	t[k]=0; int mid=(l+r)>>1;
	if(l==r) return ;
	clear(k<<1,l,mid); clear(k<<1|1,mid+1,r);
}
void clear(int k,int l,int r,int L,int R)
{
	if(D&&k==1) printf("C %d %d\n",L,R);
	if(l>R||L>r) return ;
	if(L<=l&&r<=R){ clear(k,l,r); return ; }
	int mid=(l+r)>>1;
	clear(k<<1,l,mid,L,R); clear(k<<1|1,mid+1,r,L,R);
	update(k);
}
int ans[N];
void modify(int k,int l,int r,int p,int v)
{
	if(D&&k==1) printf("+ %d %d\n",p,v);
	if(l==r){ t[k]+=v; return ; }
	int mid=(l+r)>>1;
	if(p<=mid) modify(k<<1,l,mid,p,v);
	else modify(k<<1|1,mid+1,r,p,v);
	update(k);
}
namespace bf
{
	const int N=110;
	int f[N][N];
	int a[N][N],b[N][N],vis[N][N];
	int dfs(int x,int y)
	{
		if(vis[x][y]||x>n||y>n) return 0;
		vis[x][y]=1; int ans=f[x][y];
		if(a[x][y]) ans+=dfs(x+1,y);
		if(b[x][y]) ans+=dfs(x,y+1);
		return ans;
	}
	int main()
	{
		n=100;
		fr(i,1,n) fr(j,1,n) a[i][j]=b[i][j]=1;
		fr(i,1,read())
		{
			int r1=read(),c1=read(),r2=read(),c2=read();
			fr(i,r1,r2) b[i][c1-1]=b[i][c2]=0;
			fr(i,c1,c2) a[r1-1][i]=a[r2][i]=0;
		}
		fr(i,1,read()){ int x=read(),y=read(); f[x][y]++; }
		fr(i,1,read()){ int x=read(),y=read(); memset(vis,0,sizeof(vis)); printf("%d\n",dfs(x,y)); }
		return 0;
	}
}
int main()
{
	fr(i,1,n=read())
	{
		int r1=read(),c1=read(),r2=read(),c2=read();
		_l[i]=c1; _r[i]=c2; op[r2].push_back(i); op[r1-1].push_back(-i);
	}
	fr(i,1,m=read()){ int r=read(),c=read(); fl[r].push_back(c); }
	fr(i,1,q=read()){ int r=read(),c=read(); co[r].push_back(pii(c,i)); }
	s.insert(0); s.insert(mx);
	fd(t,1000000,1)
	{
		std::sort(op[t].begin(),op[t].end(),[&](int a,int b){ return a>b; });
		for(auto i:op[t])
		{
			if(i>0)
			{
				c[i]=query(1,0,mx,_r[i]+1,*(s.upper_bound(_r[i]))); int C=query(1,0,mx,_l[i],_r[i]);
				clear(1,0,mx,_l[i],_r[i]); modify(1,0,mx,_l[i]-1,C+c[i]);
				s.insert(_l[i]-1); s.insert(_r[i]);
			}
			else
			{
				int I=-i; modify(1,0,mx,_l[I]-1,-c[I]); clear(1,0,mx,_l[I],_r[I]);
				s.erase(_l[I]-1); s.erase(_r[I]);
			}
		}
		for(auto i:fl[t]) modify(1,0,mx,i,1);
		for(auto i:co[t]) ans[i.second]=query(1,0,mx,i.first,*(s.lower_bound(i.first)));
	}
	fr(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
