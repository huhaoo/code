/**************************************************************
	File name: 3923.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/17/2018, 3:56:20 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#define N 200010
#define T 100
#define A ((1<<20)-1)
#define B 18
int n,q,r[N],val[N*T],s[N*T][2],cnt;
int add(int k,int v,int l,int r)
{
	int t=++cnt;val[t]=val[k]+1;
	if(l==r)return t;
	int mid=(l+r)>>1;
	if(v<=mid)
	{
		s[t][0]=add(s[k][0],v,l,mid);
		s[t][1]=s[k][1];
	}
	else
	{
		s[t][0]=s[k][0];
		s[t][1]=add(s[k][1],v,mid+1,r);
	}
	return t;
}
int query(int a,int b,int l,int r,int ll,int rr)
{
	if(ll<=l&&r<=rr)return val[a]-val[b];
	int mid=(l+r)>>1,ans=0;
	if(ll<=mid)ans+=query(s[a][0],s[b][0],l,mid,ll,rr);
	if(rr>mid)ans+=query(s[a][1],s[b][1],mid+1,r,ll,rr);
	return ans;
}
int query(int r,int l,int s,int t)
{
	s=max(s,0);t=min(t,A);
	if(s>t)return 0;
	return query(r,l,0,A,s,t);
}
int main()
{
	n=read();q=read();
	fr(i,1,n)
	{
		int a=read();
		r[i]=add(r[i-1],a,0,A);
	}
	while(q--)
	{
		int b=read(),x=read(),l=read(),rr=read(),ans=0;
		fd(i,B,0)
		{
			int opt=!(b&(1<<i));
			if(query(r[rr],r[l-1],ans+(opt<<i)-x,ans+(opt<<i)+(1<<i)-1-x))ans=ans+(opt<<i);
			else ans=ans+((!opt)<<i);
		}
		printf("%d\n",ans^b);
	}
	return 0;
}