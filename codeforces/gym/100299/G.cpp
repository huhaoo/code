/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Tue 05 Jan 2021 02:43:06 PM CST
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
#include<vector>
#include<set>
const int N=1<<18|10;
int n,id[N],m,q,c; pii a[N];
std::vector<int> p[N];
std::multiset<pii> t[N];
std::multiset<int> T;
int mn[N],Mn[N],s[N];
void build(int k,int l,int r)
{
	mn[k]=Mn[k]=N; s[k]=0; t[k].clear(); if(l==r) return ;
	int mid=(l+r)>>1; build(k<<1,l,mid); build(k<<1|1,mid+1,r); 
}
void update(int k){ mn[k]=std::min(mn[k<<1],mn[k<<1|1]); Mn[k]=std::min(Mn[k<<1],Mn[k<<1|1]-s[k<<1]); s[k]=s[k<<1]+s[k<<1|1]; }
void modify(int k,int l,int r,int v,int p)
{
//	if(k==1) printf("+ %d %d %d\n",id[v],::p[v].size(),p);
//	printf("%d %d\n",l,r);
	if(l==r)
	{
		for(auto i: ::p[v]){ t[k].insert(pii(i,v)); T.erase(T.find(i)); }
//		printf("==\n");
		if(t[k].empty()) mn[k]=N;
		else mn[k]=t[k].begin()->first;
		Mn[k]=l-t[k].size(); s[k]=t[k].size();
		return ;
	}
	int mid=(l+r)>>1;
	if(p<=mid) modify(k<<1,l,mid,v,p);
	else modify(k<<1|1,mid+1,r,v,p);
	update(k);
}
void Modify(int k,int l,int r,int p)
{
	if(l==r){ Mn[k]=mn[k]=N; s[k]=0; return ; }
	int mid=(l+r)>>1;
	if(p<=mid) Modify(k<<1,l,mid,p);
	else Modify(k<<1|1,mid+1,r,p);
	update(k);
}
pii query(int k,int l,int r,int p,int Mi)
{
//	printf("%d %d  %d %d\n",l,r,mn[k],Mn[k]);
	if(mn[k]>Mi) return pii(-1,-1);
	if(l==r)
	{
//		printf("- %d\n",l);
		pii u=*t[k].begin(); t[k].erase(t[k].begin());
		if(t[k].empty()) mn[k]=N;
		else mn[k]=t[k].begin()->first;
		Mn[k]=l-t[k].size(); s[k]=t[k].size();
		return u;
	}
	int mid=(l+r)>>1; pii ans;
//	printf("%d %d  %d   %d %d %d\n",l,r,p,Mn[k],Mn[k<<1],Mn[k<<1|1]);
	if(Mn[k]==p)
	{
		if(Mn[k<<1]==p)
		{
			ans=query(k<<1,l,mid,p,Mi);
		}
		else
		{
			ans=query(k<<1|1,mid+1,r,p+s[k<<1],std::min(Mi,mn[k<<1]));
			if(ans==pii(-1,-1)) ans=query(k<<1,l,mid,p,Mi);
		}
	}
	else if(mn[k]==mn[k<<1]) ans=query(k<<1,l,mid,p,Mi);
	else ans=query(k<<1|1,mid+1,r,p+s[k<<1],Mi);
	update(k); return ans;
}
bool check(int k)
{
//	printf("\n%d\n",k);
	build(1,1,n); q=c=0; T.clear();
	fr(i,1,m) for(auto j:p[i]) T.insert(j);
	while(c!=n)
	{
//		printf(" %d %d\n",c,Mn[1]);
		if(Mn[1]-c>0&&!T.empty())
		{
			int mi=*T.begin();
			if(mi<mn[1]) while(q<mi) modify(1,1,n,++q,std::min(n,c+k+1));
		}
//		printf(" %d %d\n",c,Mn[1]);
		if(Mn[1]-c<0) return 0;
		pii u=query(1,1,n,c,N); std::swap(u.first,u.second);
//		printf("%d %d\n",id[u.first],id[u.second]);
		a[++c]=u; Modify(1,1,n,c);
		while(q<u.second) modify(1,1,n,++q,std::min(n,c+k));
	}
	return 1;
}
int main()
{
	fr(T,1,read())
	{
		n=read(); static int x[N],y[N]; m=0;
		fr(i,1,n)
		{
			x[i]=read(); y[i]=read(); id[++m]=x[i]; id[++m]=y[i];
		}
		std::sort(id+1,id+m+1); m=std::unique(id+1,id+m+1)-id-1;
		fr(i,1,m) p[i].clear();
		fr(i,1,n) p[std::lower_bound(id+1,id+m+1,x[i])-id].push_back(std::lower_bound(id+1,id+m+1,y[i])-id);
		int l=0,r=n;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		check(l); printf("%d\n",l);
		fr(i,1,c) printf("%d %d\n",id[a[i].first],id[a[i].second]);
	}
	return 0;
}
