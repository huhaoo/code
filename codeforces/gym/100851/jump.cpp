/***************************************************************
	File name: jump.cpp
	Author: huhao
	Create time: Sun 08 Nov 2020 10:22:16 PM CST
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
#include<random>
#include<vector>
std::mt19937 Rand;
int query(std::vector<int> s){ for(auto i:s) putchar(i+48); putchar(10); fflush(stdout); return read(); }
void solve(int n)
{
	std::vector<int> s(n); int lst,flag=0;
	while(!flag)
	{
		fr(i,0,n-1) s[i]=Rand()&1;
		fr(i,0,0)
		{
			if((lst=query(s))){ flag=1; break; } s[i]^=1;
		}
	}
	if(lst==n) return ;
	std::vector<int> p(n);
	fr(i,1,n-1)
	{
		s[0]^=1; s[i]^=1; lst=query(s);
		if(lst==n) return ;
		if(lst) p[i]=1;
		s[0]^=1; s[i]^=1;
	}
	fr(i,0,n-1) s[i]^=p[i];
	if(!query(s))
	{
		fr(i,0,n-1) s[i]^=1;
		query(s);
	}
}
int main()
{
	solve(read()); return 0;
/*	int n=read(),t=0;
	fr(T,1,1000000000)
	{
		int a=0;
		std::vector<int> s(n);
		fr(i,0,n-1) a+=(s[i]=Rand()&1);
		int Ans=-1;
		fr(i,0,n-1)
		{
			if(a==n/2||a==n){ Ans=i+1; break; }
			a-=s[i]; s[i]^=1; a+=s[i];
		}
		if(Ans<=1) t++;
		if(T%100000==0) printf("%.10lf\n",t*1./T);
	}*/
	return 0;
}
