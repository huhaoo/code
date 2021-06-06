#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
i64 t,n,ans;
int main()
{
	t=read(); n=read();
	while(n>t*2)
	{
		ans+=100; n-=t;
	}
	fr(i,1,1000000) if((i64)i*(100+t)/100-i==n)
	{
//		printf("%d %d\n",i,i*(100+t)/100);
		ans+=i; break;
	}
	printf("%lld\n",ans*(100+t)/100-1);
	return 0;
}