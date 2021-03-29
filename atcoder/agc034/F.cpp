/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Mon 20 Jan 2020 05:02:13 PM CST
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
#define i64 long long
const int N=(1<<18)|10,mod=998244353,i2=(mod+1)/2;
i64 n,a[N],b[N];
void fwt(i64 *a,i64 opt)
{
	opt=(opt==1?1:i2);
	fr(i,0,n-1) for(int j=0;j<(1<<n);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
	{
		i64 x=a[j+k],y=a[j+k+(1<<i)];
		a[j+k]=(x+y)*opt%mod; a[j+k+(1<<i)]=(x-y+mod)*opt%mod;
	}
}
int main()
{
	n=read();
	fr(i,0,(1<<n)-1) a[i]=read();
//	fr(i,0,(1<<n)-1) b[i]=read();
	fwt(a,1); fwt(b,1);
	fr(i,0,(1<<n)-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
//	fr(i,0,(1<<n)-1) printf("%lld%c",b[i],i==end_i?'\n':' ');
//	fr(i,0,(1<<n)-1) a[i]=a[i]*b[i]%mod;
//	fwt(a,-1);
//	fr(i,0,(1<<n)-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
	return 0;
}
