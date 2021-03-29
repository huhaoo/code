/***************************************************************
	File name: 5598.cpp
	Author: huhao
	Create time: Wed 23 Oct 2019 04:03:06 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
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
const int N=500010,P=10;
i64 n,p,c[P][P],a[N],m,_p[N],nex[N],ans,s[N];
#include<vector>
vector<pair<int,int>>nz[N];
int main()
{
	n=read();
	p=read();
	fr(i,0,p-1)
		c[i][i]=c[i][0]=1;
	fr(i,1,p-1)
		fr(j,1,i-1)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%p;
	_p[m=0]=1;
	while(1000000000000000000ll>=_p[m]*p)
	{
		m++;
		_p[m]=_p[m-1]*p;
	}
	fr(i,1,n)
	{
		a[i]=read();
		fr(j,1,m)
			if((a[i]/_p[j-1])%p)
				nz[i].push_back(make_pair(j,(int)((a[i]/_p[j-1])%p)));
	}
	nex[n]=n+1;
	fd(i,n-1,1)
		if(a[i+1])
			nex[i]=i+1;
		else
			nex[i]=nex[i+1];
	fr(i,1,n)
	{
		i64 v=1,j=i;
		fr(i,1,m)
			s[i]=0;
		while(j<=n)
			if(!a[j])
			{
				ans=ans+v*(nex[j]-j);
				j=nex[j];
			}
			else
			{
				for(auto k:nz[j])
				{
					if((s[k.first]+=k.second)>=p)
					{
						v=0;
						break;
					}
					v=v*c[s[k.first]][k.second]%p;
				}
				if(!v)
					break;
				ans=ans+v;
				j++;
			}
	}
	printf("%lld\n",ans);
	return 0;
}
