/***************************************************************
	File name: 5470.cpp
	Author: huhao
	Create time: Tue 30 Jul 2019 09:25:39 PM CST
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
#include<queue>
#define i64 long long
const int N=200010;
const i64 inf=1ll<<50;
i64 c[N],d[N],ans;
int n,C[N],D[N],k,l,T;
int s1[N],s2[N],s3[N],*i1,*i2,*i3;
struct cmp1
{
	int k;
	cmp1(int _k=0)
	{
		k=_k;
	}
};
struct cmp2
{
	int k;
	cmp2(int _k=0)
	{
		k=_k;
	}
};
struct cmp3
{
	int k;
	cmp3(int _k=0)
	{
		k=_k;
	}
};
int operator<(cmp1 a,cmp1 b)
{
	return c[a.k]==c[b.k]?a.k>b.k:c[a.k]<c[b.k];
}
int operator<(cmp2 a,cmp2 b)
{
	return d[a.k]==d[b.k]?a.k>b.k:d[a.k]<d[b.k];
}
int operator<(cmp3 a,cmp3 b)
{
	return c[a.k]+d[a.k]==c[b.k]+d[b.k]?a.k>b.k:c[a.k]+d[a.k]<c[b.k]+d[b.k];
}
priority_queue<cmp1>s4;
priority_queue<cmp2>s5;
void choosec(int p)
{
	ans+=c[p];
	C[p]=1;
	if(D[p])
	{
		l++;
	}
	else
	{
		s5.push(p);
	}
}
void choosed(int p)
{
	ans+=d[p];
	D[p]=1;
	if(C[p])
	{
		l++;
	}
	else
	{
		s4.push(p);
	}
}
int top1()
{
	int k=*i1;
	while(k&&C[k])
	{
		i1++;
		k=*i1;
	}
	return k;
}
int top2()
{
	int k=*i2;
	while(k&&D[k])
	{
		i2++;
		k=*i2;
	}
	return k;
}
int top3()
{
	int k=*i3;
	while(k&&(C[k]||D[k]))
	{
		i3++;
		k=*i3;
	}
	return k;
}
int top4()
{
	int k=s4.top().k;
	while(k&&(C[k]||!D[k]))
	{
		s4.pop();
		k=s4.top().k;
	}
	return k;
}
int top5()
{
	int k=s5.top().k;
	while(k&&(!C[k]||D[k]))
	{
		s5.pop();
		k=s5.top().k;
	}
	return k;
}
int cmp4(int a,int b)
{
	return c[a]>c[b];
}
int cmp5(int a,int b)
{
	return d[a]>d[b];
}
int cmp6(int a,int b)
{
	return c[a]+d[a]>c[b]+d[b];
}
int main()
{
//	freopen("sequence.in","r",stdin);
//	freopen("sequence.out","w",stdout);
	T=read();
	while(T--)
	{
		while(!s4.empty())
			s4.pop();
		while(!s5.empty())
			s5.pop();
		n=read();
		k=read();
		l=k-read();
		fr(i,1,n)
			c[i]=read();
		fr(i,1,n)
			d[i]=read();
		fr(i,1,n)
			s1[i]=s2[i]=s3[i]=i;
		sort(s1+1,s1+n+1,cmp4);
		sort(s2+1,s2+n+1,cmp5);
		sort(s3+1,s3+n+1,cmp6);
		i1=s1+1;
		i2=s2+1;
		i3=s3+1;
		fr(i,1,n)
			C[i]=D[i]=0;
		ans=0;
		c[0]=d[0]=-inf;
		s4.push(0);
		s5.push(0);
		while(k--)
		{
			if(l)
			{
				choosec(top1());
				choosed(top2());
			}
			else
			{
				i64 v1=top3(),v2=c[top4()]+d[top2()],v3=d[top5()]+c[top1()],v;
				v1=c[v1]+d[v1];
				v=max(v1,max(v2,v3));
				if(v1==v)
				{
					v1=top3();
					choosec(v1);
					choosed(v1);
				}
				else if(v2==v)
				{
					choosec(top4());
					choosed(top2());
				}
				else
				{
					choosed(top5());
					choosec(top1());
				}
			}
			l--;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
