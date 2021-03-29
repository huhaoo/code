/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Thu 22 Oct 2020 02:43:55 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define u64 unsigned long long
#define fr(i,a,b) for(u64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
u64 read()
{
	u64 r=0,t=1,c=getchar();
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
const int N=123,M=1<<16|10;
int n;
u64 a[N],b[N],s;
void print(u64 ans)
{
	fr(i,0,n-1) putchar(((ans>>i)&1)+48);
	putchar(10);
}
void solve(u64 I)
{
	fr(i,0,n-1) a[i]=b[i]*I;
	u64 S=0; int flag=1;
	fr(i,0,n-1)
	{
		if(a[i]<=S) flag=0;
		if(a[i]+S<a[i]) flag=0;
		S+=a[i];
	}
	if(!flag) return ;
	u64 r=s*I;
	fd(i,n-1,0) if(r>=a[i]) r-=a[i];
	if(r) return ;
	u64 ans=0; r=s*I;
	fd(i,n-1,0) if(r>=a[i]){ r-=a[i]; ans|=1ull<<i; }
	print(ans); exit(0);
}
int main()
{
	n=read();
	fr(i,0,n-1) b[i]=read();
	s=read();
	if(!s){ fr(i,0,n-1) putchar('0'); putchar(10); return 0; }
	if(n==1){ printf("1\n"); return 0; }
	if(n<=40)
	{
		int m=n/2;
		std::map<u64,int> t;
		fr(i,0,(1<<m)-1)
		{
			u64 v=0;
			fr(j,0,m-1) if((i>>j)&1) v+=b[j];
			t[v]=i;
		}
		fr(i,0,(1<<(n-m))-1)
		{
			u64 v=0;
			fr(j,0,n-m-1) if((i>>j)&1) v+=b[j+m];
			if(t.count(s-v)){ print(i<<m|t[s-v]); return 0; }
		}
	}
	else
	{
		fr(t,1,1ull<<(65-n))
		{
			u64 x=t,y=b[0],z=64;
			while(!(x&1)&&!(y&1)){ z--; x>>=1; y>>=1; }
			if(!(x&1)||!(y&1)) continue;
			u64 I=1;
			fr(i,2,z) if(((I*y)>>(i-1))&1) I*=1+(1ull<<(i-1));
			if(z==64) solve(I*x);
			else fr(j,0,(1ull<<(64-z))-1) solve(I*(1|j<<z)*x);
		}
	}
	return 0;
}
