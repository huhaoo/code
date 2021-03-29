/***************************************************************
	File name: 1912.cpp
	Author: huhao
	Create time: Fri 04 Oct 2019 07:04:53 PM CST
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
#define i64 long long
#define f80 long double
const int N=100010,L=40;
const i64 inf=1e18;
i64 n,A,p,a[N],T,q[N],_l,_r,l[N],r[N],pre[N],S[N],t;
char s[N][L];
f80 f[N];
i64 power(i64 a,i64 b)
{
	i64 r=1;
	while(1)
	{
		if(b&1)
		{
			if((f80)r*a>1e18)
				return inf+1;
			r=r*a;
		}
		if(b<2)
			break;
		if((f80)a*a>1e18)
			return inf+1;
		a=a*a;
		b>>=1;
	}
	return r;
}
f80 fpower(f80 a,i64 b)
{
	f80 r=1;
	while(b--)
		r=r*a;
	return r;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		A=read();
		p=read();
		fr(i,1,n)
		{
			scanf("%s",s[i]);
			a[i]=strlen(s[i])+a[i-1]+1;
		}
		_l=_r=1;
		q[1]=0;
		l[1]=1;
		r[1]=n;
		fr(i,1,n)
		{
#define F(i,j) f[j]+fpower(abs(a[i]-a[j]-1-A),p)
			f[i]=F(i,q[_l]);
			pre[i]=q[_l];
//			printf("%d %lld %lld %lld\n",i,q[_l],f[q[_l]],f[i]);
			l[_l]++;
			if(l[_l]>r[_l])
				_l++;
			while(_l<=_r&&F(l[_r],i)<=F(l[_r],q[_r]))
				_r--;
			if(_l<=_r)
			{
				int l_=l[_r],r_=r[_r]+1;
				while(l_<r_)
				{
					int mid=(l_+r_)>>1;
					if(F(mid,i)<=F(mid,q[_r]))
						r_=mid;
					else
						l_=mid+1;
				}
//				printf(" %d %d\n",i,r_);
				r[_r]=r_-1;
				if(r_<=n)
				{
					_r++;
					q[_r]=i;
					l[_r]=r_;
					r[_r]=n;
				}
			}
			else
			{
				_r++;
				q[_r]=i;
				l[_r]=i+1;
				r[_r]=n;
			}
//			fr(i,_l,_r)
//				printf("  %d %d %d\n",q[i],l[i],r[i]);
		}
		if(f[n]>inf)
			printf("Too hard to arrange\n");
		else
		{
			printf("%lld\n",(i64)f[n]);
			int k=n;
			t=0;
			while(k)
			{
				S[++t]=k;
				k=pre[k];
			}
			S[t+1]=0;
			fd(i,t,1)
				fr(j,S[i+1]+1,S[i])
					printf("%s%c",s[j],j==end_j?'\n':' ');
		}
		printf("--------------------\n");
	}
	return 0;
}
