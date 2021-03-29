/***************************************************************
	File name: csa_distinct_neighbours.cpp
	Author: huhao
	Create time: Mon 13 Jan 2020 05:03:20 PM CST
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
#define mii std::map<int,int>
#define i64 long long
const int N=10010,mod=1000000007;
mii a;
i64 n,f[N],F[N],s;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
namespace C
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1;
		fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]);
		fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return a<0||b<0||a-b<0?0:f[a]*F[b]%mod*F[a-b]%mod; }
}
int min(int a,int b){ return a<b?a:b; }
int max(int a,int b){ return a>b?a:b; }
/*
 * 简要题解
 * 记f[i]为当前有i个形如aa的位置，用每一组相等的取转移它
 * 记它们个数为c_1,c_2\dots c_k
 * 那么复杂度就是O(\sum_i(c_i^2\sum_{j<i}c_i))=O(n^3)
 */
int main()
{
	n=read(); C::init(n+1);
	fr(i,1,n) a[read()]++;
	f[0]=1;
	for(mii::iterator it=a.begin();it!=a.end();it++)
	{
		int l=it->second;
		fr(i,0,s){ F[i]=f[i]; f[i]=0; }
		fr(i,0,s) if(F[i]) fr(j,0,min(i,l)) fr(k,max(j,1),min(s+1-(j-i),l))
		{
//			printf(" %d %d %d\n",i,j,k);
			f[i-j+(l-k)]+=F[i]*C::C(i,j)%mod*C::C(s+1-i,k-j)%mod*C::C(l-1,k-1)%mod;
		}
		s+=l;
//		printf("%d\n",l);
//		fr(i,0,s) printf("%lld%c",f[i],i==s?'\n':' ');
		fr(i,0,s) f[i]%=mod;
	}
	printf("%lld\n",f[0]);
	return 0;
}
