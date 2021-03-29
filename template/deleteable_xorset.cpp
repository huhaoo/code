/***************************************************************
	File name: deleteable_xorset.cpp
	Author: huhao
	Create time: Tue 22 Dec 2020 10:25:28 AM CST
	Source: https://uoj.ac/problem/91
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
#include<bitset>
const int N=2048;
std::bitset<N> Read()
{
	static char s[N]; scanf("%s",s); int n=strlen(s); std::bitset<N> a;
	fr(i,0,n-1) a[n-i]=s[i]=='1';
	return a;
}
int n,m,id[N],b[N],q;
std::bitset<N> a[N],p[N],A[N];
void ins(int u)
{
	fd(i,m,1) if(a[u][i])
	{
		if(!b[i]){ b[i]=u; id[u]=i; return ; }
		a[u]^=a[b[i]]; p[u]^=p[b[i]];
	}
	id[u]=0;
}
void Xor(int u,std::bitset<N> X)
{
	int v=0;
	fr(i,1,n) if(p[i][u]&&id[i]<id[v]) v=i;
	fr(i,1,n) if(i!=v&&p[i][u]){ p[i]^=p[v]; a[i]^=a[v]; }
	if(id[v]){ b[id[v]]=0; id[v]=0; }
	a[v]^=X; ins(v);
/*	printf(" %d\n ",u);
	fd(i,m,1) putchar(int(X[i])+48);; putchar(10);
	fr(i,1,n){ fd(j,m,1) putchar(int(a[i][j])+48);; putchar(10); }
	fr(i,1,m) printf("%d%c",b[i],i==m?'\n':' ');*/
}
std::bitset<N> query()
{
	std::bitset<N> ans;
	fd(i,m,1) if(!ans[i]&&b[i]) ans^=a[b[i]];
	return ans;
}
int main()
{
	n=read(); m=read(); q=read(); id[0]=m+1;
	fr(i,1,n) A[i]=Read();
	fr(i,1,n){ a[i]=A[i]^A[i-1]; p[i].reset(); p[i][i]=1; ins(i); }
//	fr(i,1,n){ fd(j,m,1) putchar(int(a[i][j])+48);; putchar(10); }
//	fr(i,1,n) printf("%d%c",id[i],i==n?'\n':' ');
//	fr(i,1,m) printf("%d%c",b[i],i==m?'\n':' ');; putchar(10);
	while(q--)
	{
		int op=read();
		if(op==1)
		{
			int l=read(),r=read(); std::bitset<N> X=Read();
			Xor(l,X); if(r+1<=n) Xor(r+1,X);
			fr(i,l,r) A[i]^=X;
		}
		else if(op==2)
		{
			int l=read(),r=read(); std::bitset<N> X=Read();
			fr(i,l+1,r) if(A[i]!=A[i-1]) Xor(i,A[i]^A[i-1]);
			Xor(l,A[l]^X); if(r+1<=n) Xor(r+1,A[r]^X);
			fr(i,l,r) A[i]=X;
		}
		else
		{
			std::bitset<N> ans=query();
			fd(i,m,1) putchar(int(ans[i])+48);; putchar(10);
		}
	}
	return 0;
}
