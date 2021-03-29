/**************************************************************
	File name: 4213.cpp(luogu)
	Author: huhao
	Email: 826538400@qq.com
	Create time: 4/2/2019, 4:34:54 PM
**************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const long long _N=(1ll<<31)-1;
const long long k=4500000;
const long long N=k+10;
int sm1[N],sm2[_N/k+100],v[N],p[N],c,mu[N],phi[N],n,T,x;
long long sp1[N],sp2[_N/k+100];
int main()
{
//	printf("%.10lf\n",sizeof(v)/1024./1024.*7);
	fr(i,2,k)
	{
		if(!v[i])
		{
			c++;
			p[c]=i;
			mu[i]=-1;
			phi[i]=i-1;
		}
		fr(j,1,c)
			if(i*p[j]<=k)
			{
				if(i%p[j]==0)
				{
					v[i*p[j]]=1;
					mu[i*p[j]]=0;
					phi[i*p[j]]=p[j]*phi[i];
					break;
				}
				else
				{
					v[i*p[j]]=1;
					mu[i*p[j]]=-mu[i];
					phi[i*p[j]]=(p[j]-1)*phi[i];
				}
			}
			else
				break;
	}
	mu[1]=phi[1]=1;
	fr(i,1,k)
	{
		sm1[i]=sm1[i-1]+mu[i];
		sp1[i]=sp1[i-1]+phi[i];
	}
	T=read();
	while(T--)
	{
		n=read();
		if(n<=k)
		{
			printf("%lld %d\n",sp1[n],sm1[n]);
			continue;
		}
		memset(sp2,0,sizeof(sp2));
		memset(sm2,0,sizeof(sm2));
		x=n/k;
		fd(i,x,1)
		{
			int y=n/i;
			sp2[i]=(long long)y*((long long)y+1)/2;
			sm2[i]=1;
			for(int j=2,o,z;j>=0&&j<=y;j=z)
			{
				o=y/j;
				z=y/o+1;
				sp2[i]-=(z-j)*(o<=k?sp1[o]:sp2[n/o]);
				sm2[i]-=(z-j)*(o<=k?sm1[o]:sm2[n/o]);
			}
		}
		printf("%lld %d\n",sp2[1],sm2[1]);
	}
	return 0;
}