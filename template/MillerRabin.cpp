/***************************************************************
	File name: MillerRabin.cpp
	Author: huhao
	Create time: Thu 18 Jun 2020 04:55:00 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
inline i64 Mod(i64 a,i64 p){ return a>=p?a-p:a; }
i64 mul(i64 a,i64 b,i64 p)
{
	i64 r=0;
	for(;b;b>>=1,a=Mod(a+a,p)) if(b&1) r=Mod(r+a,p);
	return r;
}
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=mul(a,a,p)) if(b&1) r=mul(r,a,p);
	return r;
}
i64 check(i64 a,i64 p)
{
	i64 x=p-1,y=0;
	while((x&1)==0){ x>>=1; y++; }
	i64 v=power(a,x,p);
	if(v==1) return 1;
	while(y)
	{
		i64 V=mul(v,v,p);
		if(V==1&&v!=p-1) return 0;
		if(V==1) return 1;
		v=V; y--;
	}
	return 0;
}
#include<stdlib.h>
i64 query(i64 p)
{
	if(p==1) return 0;
	fr(i,1,6) if(!check(rand()%(p-1)+1,p)) return 0;
	return 1;
}
int main()
{
	srand(998244353); i64 n;
	while(scanf("%lld",&n)!=EOF) printf("%c\n",query(n)?'Y':'N');
	return 0;
}
