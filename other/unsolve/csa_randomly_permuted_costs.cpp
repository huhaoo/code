/***************************************************************
	File name: csa_randomly_permuted_costs.cpp
	Author: huhao
	Create time: Mon 13 Jan 2020 06:57:32 PM CST
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
/*
 * 拓扑排序，然后每个点考虑一下怎么DP
 * 我们可以假设没有自环，相当于两个数组a,b，其中b随机排列，求max(a_i+b_i)的期望
 * 我们可以算最小值不小于k的概率，然后容斥一下，这有c^2个（其中c为出边个数）
 * 考虑对于一个实数p怎么算：
 * 对于每个a_i，求出有几个b_j使得a_i+b_j>p，记为c_i
 * 如果记s_i为c_j\le i的个数，答案是\prod_i(s_i-i+1)（最后/c!）
 * 然后一共有c^2次修改，发现修改只有关s_i，树状数组维护即可，于是单次O(c^2\log c)
 * 有自环的话我们可以考虑二分这个节点的dp值$g$，如果比真实$f$小的话我们会算出来$h>g$否则$h<g$，这样二分一下（注意一下精度卡卡常就好了）
 * ~~如果卡不过就安心想一个log吧~~
 * 相当于每次插入一次数，然后只有O(n)次操作，我们扫一遍就好了，预计代码不会小于5K，不打算写了
 */
/*
#include<queue>
namespace run
{
	const double eps=1e-9;
	const int N=2010;
	int n,m,e,begin[N],next[N],to[N],S,T,rk[N],_l,_r,c[N],d[N],s[N];
	double a[N],b[N];
	double f[N],w[N];
	double p[N],v[N];
	void add(int u,int v,double W){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
#define pii std::pair<int,int>
#include<vector>
	struct cmp{ int operator()(pii x,pii y){ return a[x.first]+b[x.second]<a[y.first]+b[y.second]; } };
	std::priority_queue<pii,std::vector<pii>,cmp> q;
	double calc(int n)
	{
		int m=0;
		std::sort(a+1,a+n+1); std::sort(b+1,b+n+1);
		fr(i,1,n) q.push(pii(i,n));
		fr(i,1,n*n){ ... }
	}
	int main()
	{
		n=read(); m=read(); S=read(); T=read(); _l=1;
		fr(i,1,m){ int u=read(),v=read(); double w; scanf("%lf",&w); add(u,v,w); if(u!=v) d[v]++; }
		fr(i,1,n) if(!d[i]) rk[++_r]=i;
		while(_l<=_r)
		{
			int u=rk[_l++];
			fo(i,u){ d[to[i]]--; if(!d[to[i]]) rk[++_r]=to[i]; }
		}
		c[T]=1;
		fd(i,n,1) fo(j,rk[i]) c[rk[i]]|=c[to[j]];
		if(!c[S]){ printf("-1\n"); return 0; }
		fr(i,1,n) f[i]=1e9;
		f[T]=0;
		fd(I,n,1)
		{
			int i=rk[I]; double l=0,r=1e8;
			while(r-l>eps)
			{
				double mid=(l+r)/2; int m=0; f[i]=mid;
				fo(j,i){ m++; a[m]=f[to[j]]; b[m]=w[j]; }
				double f=calc(m);
				if(f>=mid) l=f;
				else r=f;
			}
			f[i]=(l+r)/2;
		}
		printf("%.10lf\n",f[S]);
		return 0;
	}
}
int main(){ return run::main(); }*/
int main(){ return 0; }
