/**************************************************************
	File name: 3822.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 6/30/2018, 8:19:03 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef unsigned long long ul;
typedef unsigned int ui;
#define fr(i,a,b) for(ui i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(ui i=(a),_end_=(b);i>=_end_;i--)
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
#define N 30000010
#include<set>
set<int>s;
ui n,a1[N],a2[N],l;
int main()
{
	s.insert(1);
	n=read();read();read();read();
	l=30*n/32;
	fr(i,1,n)
		if(read()&1)
		{
			int k=read(),b=read();
			if(k>0)
			{
				ul kk=k;
				kk<<=(ul)b%32;
				b/=32;
				while(kk&&b<=l)
				{
					kk+=a1[b];
					if(a1[b]==a2[b])s.insert(-b);
					a1[b]=kk&((1ul<<32ul)-1);
					if(a1[b]==a2[b])s.erase(-b);
					kk>>=32ll;
					b++;
				}
			}
			else
			{
				k=-k;
				ul kk=k;
				kk<<=(ul)b%32;
				b/=32;
				while(kk&&b<=l)
				{
					kk+=a2[b];
					if(a1[b]==a2[b])s.insert(-b);
					a2[b]=kk&((1ul<<32ul)-1);
					if(a1[b]==a2[b])s.erase(-b);
					kk>>=32ll;
					b++;
				}
			}
//			printf("%u %u\n",a1[0],a2[0]);
		}
		else
		{
			ui k=read();
//			printf(" %u %u\n",i,k);
			ui a=k/32,b=k%32;
			ui ans=2+!!(a1[a]&(1ul<<b))-!!(a2[a]&(1ul<<b));
			if((a1[a]&((1ul<<b)-1))!=(a2[a]&((1ul<<b)-1)))
			{
				if((a1[a]&((1ul<<b)-1))<(a2[a]&((1ul<<b)-1)))
					ans--;
			}
			else
			{
				ui aa=-*s.upper_bound(-a);
				if((aa!=-1u)&&a1[aa]<a2[aa])ans--;
//				putchar('*');
			}
			printf("%u\n",ans&1);
		}
	return 0;
}