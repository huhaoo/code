/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Sun 07 Jun 2020 07:57:11 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const int N=210,L=62;
i64 T,n,a[N],b[N],ans;
char c[N];
void ins(i64 a)
{
	fd(i,L,0)
		if(((a>>i)&1))
		{
			if(b[i]) a^=b[i];
			else{ b[i]=a; return ; }
		}
}
i64 query(i64 a)
{
	fd(i,L,0) if(((a>>i)&1)&&b[i]) a^=b[i];
	return a;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(); memset(b,0,sizeof(b));
		fr(i,1,n) a[i]=read();
		scanf("%s",c+1); ans=0;
		fd(i,n,1)
			if(c[i]=='0') ins(a[i]);
			else if(query(a[i])) ans=1;
		printf("%lld\n",ans);
	}
	return 0;
}
