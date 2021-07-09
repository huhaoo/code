#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
namespace GenHelper
{
	unsigned z1,z2,z3,z4,b;
	unsigned read()
	{
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
	void srand(int x)
	{
		z1=x;
		z2=(~x)^0x233333333U;
		z3=x^0x1234598766U;
		z4=(~x)+51;
	}
}
#define u32 unsigned int
const int N=2000010;
int n;
u32 a[N],f[N],ans;
int main()
{
	n=read(); GenHelper::srand(read());
	f[1]=1;
	fr(i,1,n) for(int j=i+i;j<=n;j+=i) f[j]+=f[i];
	fr(i,1,n) a[i]=GenHelper::read();
	fr(i,2,n) a[i]+=a[i-1];
	fr(i,1,n) if(n+1-i<=i) ans+=f[i]*(a[i]-a[n-i]);
	fr(i,1,n)
	{
		int k=n%i; if(!k) continue;
		for(int j=k;j<=n;j+=i) ans+=f[i]*(a[j]-a[j-k]); 
	}
	printf("%u\n",ans);
	return 0;
}