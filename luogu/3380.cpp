/**************************************************************
	File name: 3380.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 1/25/2019, 9:58:04 AM
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
#define M 20000010
#define V 100000000
#define inf 2147483647
int r[N],s[M][2],t[M],cnt,n,q,a[N],k;
void add(int k,int p,int v,int l,int r)
{
	t[k]+=v;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(p<=mid)
	{
		if(!s[k][0])
			s[k][0]=++cnt;
		add(s[k][0],p,v,l,mid);
	}
	else
	{
		if(!s[k][1])
			s[k][1]=++cnt;
		add(s[k][1],p,v,mid+1,r);
	}
}
void modfiy(int p,int v,int o)
{
	for(int i=k+p;i;i>>=1)
	{
		if(!r[i])
			r[i]=++cnt;
		add(r[i],v,o,0,V);
	}
}
int _rank(int k,int p,int l,int r)
{
	if(p<l||!k)
		return 0;
	if(p>=r)
		return t[k];
	int mid=(l+r)>>1;
	return _rank(s[k][0],p,l,mid)+_rank(s[k][1],p,mid+1,r);
}
int _rank(int _l,int _r,int v)
{
	int ans=1;
	for(int i=k+_l-1,j=k+_r+1;i^j^1;i>>=1,j>>=1)
	{
		if((i&1)==0)
			ans+=_rank(r[i^1],v-1,0,V);
		if((j&1)==1)
			ans+=_rank(r[j^1],v-1,0,V);
	}
	return ans;
}
int kth(int _l,int _r,int k)
{
	int l=0,r=V;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(_rank(_l,_r,mid)<=k)
			l=mid+1;
		else
			r=mid;
	}
	return l-1;
}
int _max(int k,int l,int r)
{
	if(!t[k])
		return -inf;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(t[s[k][1]])
		return _max(s[k][1],mid+1,r);
	else
		return _max(s[k][0],l,mid);
}
int lower(int k,int p,int l,int r)
{
	if(!t[k])
		return -inf;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(p<=mid)
		return lower(s[k][0],p,l,mid);
	else
		return max(lower(s[k][1],p,mid+1,r),_max(s[k][0],l,mid));
}
int lower(int _l,int _r,int v)
{
	int ans=-inf;
	for(int i=k+_l-1,j=k+_r+1;i^j^1;i>>=1,j>>=1)
	{
		if((i&1)==0)
			ans=max(ans,lower(r[i^1],v,0,V));
		if((j&1)==1)
			ans=max(ans,lower(r[j^1],v,0,V));
	}
	return ans;
}
int _min(int k,int l,int r)
{
	if(!t[k])
		return inf;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(t[s[k][0]])
		return _min(s[k][0],l,mid);
	else
		return _min(s[k][1],mid+1,r);
}
int upper(int k,int p,int l,int r)
{
	if(!t[k])
		return inf;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(p<=mid)
		return min(upper(s[k][0],p,l,mid),_min(s[k][1],mid+1,r));
	else
		return upper(s[k][1],p,mid+1,r);
}
int upper(int _l,int _r,int v)
{
	int ans=inf;
	for(int i=k+_l-1,j=k+_r+1;i^j^1;i>>=1,j>>=1)
	{
		if((i&1)==0)
			ans=min(ans,upper(r[i^1],v,0,V));
		if((j&1)==1)
			ans=min(ans,upper(r[j^1],v,0,V));
	}
	return ans;
}
int main()
{
	n=read();
	q=read();
	fr(i,1,n)
		a[i]=read();
	k=1;
	while(k<=n+1)
		k<<=1;
	fr(i,1,n)
		modfiy(i,a[i],1);
	while(q--)
	{
		int opt=read();
		switch(opt)
		{
			case 1:
			{
				int l=read(),r=read(),v=read();
				printf("%d\n",_rank(l,r,v));
				break;
			}
			case 2:
			{
				int l=read(),r=read(),k=read();
				printf("%d\n",kth(l,r,k));
				break;
			}
			case 3:
			{
				int p=read(),v=read();
				modfiy(p,a[p],-1);
				a[p]=v;
				modfiy(p,a[p],1);
				break;
			}
			case 4:
			{
				int l=read(),r=read(),v=read();
				printf("%d\n",lower(l,r,v-1));
				break;
			}
			case 5:
			{
				int l=read(),r=read(),v=read();
				printf("%d\n",upper(l,r,v+1));
				break;
			}
		}
	}
	return 0;
}