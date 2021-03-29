/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Sat 05 Oct 2019 10:00:23 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=1010,M=(1<<15)|10;
#define i64 long long
const i64 mod=1000000007;
i64 n,f[M],a[N][N],m,p2[N];
i64 calc(i64 k)
{
	if(f[k])
		return f[k];
	for(i64 i=k;i;i=(i-1)&k)
		if((i&3)==0||(i&3)==3)
		{
			if(i&1)
			{
				i64 s=1;
				fr(I,1,n)
					if((1<<(I-1))&(k^i))
					{
						i64 t=1;
						fr(J,1,n)
							if((1<<(J-1))&i)
								if(a[I][J])
									t=t*2%mod;
						t=(t-1+mod)%mod;
						fr(J,1,n)
							if((1<<(J-1))&(k^i))
								if(a[I][J])
									t=t*2%mod;
						s=s*t%mod;
					}
				fr(I,1,n)
					if((1<<(I-1))&i)
						fr(J,1,n)
							if(((1<<(J-1))&(k^i))&&a[I][J])
								s=s*2%mod;
				f[k]=(f[k]+s)%mod;
			}
			else
			{
				i64 s=1;
				fr(I,1,n)
					if((1<<(I-1))&(k^i))
					{
						i64 p=1;
						fr(J,1,n)
							if(((1<<(J-1))&i)&&a[I][J])
								p=p*2%mod;
						p=(p+mod-1)%mod;
						s=s*p%mod;
					}
				fr(I,1,n)
					if((1<<(I-1))&i)
						fr(J,1,n)
							if(((1<<(J-1))&(k^i))&&a[I][J])
								s=s*2%mod;
				i64 C=calc(k^i);
				f[k]=(f[k]+s*C)%mod;
			}
		}
	return f[k];
}
int main()
{
	n=read();
	m=read();
	fr(i,1,m)
	{
		int u=read(),v=read();
		a[u][v]=1;
	}
	p2[0]=1;
	fr(i,1,m)
		p2[i]=p2[i-1]*2%mod;
	printf("%lld\n",(p2[m]-calc((1<<n)-1)+mod)%mod);
	return 0;
}
