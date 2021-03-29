/***************************************************************
	File name: fygon20.cpp
	Author: huhao
	Create time: Wed 28 Oct 2020 08:04:37 PM CST
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
const int N=256;
int id[N],n,m,_n;
int A[N][N];
int dfn[N],low[N],Dfn,s[N],t,is[N],Id[N],a[N][N];
void tarjan(int u)
{
	dfn[u]=low[u]=++Dfn; s[++t]=u; is[u]=1;
	fr(v,1,n) if(A[u][v])
	{
		if(!dfn[v]){ tarjan(v); low[u]=std::min(low[u],low[v]); }
		else if(is[v]) low[u]=std::min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		_n++;
		while(s[t]!=u){ is[s[t]]=0; Id[s[t--]]=_n; }
		is[s[t]]=0; Id[s[t--]]=_n;
	}
}
int l[N],r[N];
char x[N],y[N],z[N];
#include<vector>
std::vector<int> e[N];
int w[N];
#define i64 long long
i64 f[1<<20|10];
int main()
{
	freopen("fygon20.in","r",stdin); freopen("fygon20.out","w",stdout);
	m=read(); id['1']=++n; id['n']=++n;
	fr(i,1,m-1)
	{
		scanf("for %c in range(%c, %c):\n",&x[i],&y[i],&z[i]);
		id[x[i]]=++n; A[id[z[i]]][id[x[i]]]=A[id[x[i]]][id[y[i]]]=1;
//		printf("%d %d\n%d %d\n",id[z[i]],id[x[i]],id[x[i]],id[y[i]]);
	}
	fr(i,1,m-1){ x[i]=id[x[i]]; y[i]=id[y[i]]; z[i]=id[z[i]]; }
//	fr(i,1,m-1) printf("%d %d %d\n",x[i],y[i],z[i]);
	fr(i,1,n) if(!dfn[i]) tarjan(i);
//	fr(i,1,n) printf("%d  %d %d\n",Id[i],dfn[i],low[i]);
	fr(i,1,n) fr(j,1,n) if(A[i][j]) a[Id[i]][Id[j]]=1;
	if(_n<=2){ printf("0 1/1\n"); return 0; }
	n=0; memset(A,0,sizeof(A));
	fr(i,1,_n)
	{
		if(i==Id[1]||i==Id[2]) id[i]=N-10;
		else id[i]=n++;
	}
	fr(i,1,_n) fr(j,1,_n) A[id[i]][id[j]]=a[i][j];
	f[0]=1;
	fr(i,0,(1<<n)-1)
	{
		fr(j,0,n-1) if(!((i>>j)&1))
		{
			int flag=1;
			fr(k,0,n-1) if(((i>>k)&1)&&A[j][k]) flag=0;
			if(!flag) continue;
			f[i|(1<<j)]+=f[i];
		}
	}
	i64 a1=f[(1<<n)-1],a2=1;
	fr(i,1,n) a2=a2*i;
	i64 g=std::__gcd(a1,a2);
	printf("%d %lld/%lld\n",n,a1/g,a2/g);
	return 0;
}
