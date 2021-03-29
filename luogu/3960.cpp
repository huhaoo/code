/****************************************************************
	File name: 3960.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/30/2018, 2:15:58 PM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#include<vector>
#define N 300010
struct tree
{
	long long val;
	tree *l,*r;
	tree(){val=0;l=r=NULL;}
}*root[N];
void del(tree *k,long long l,long long r,long long pos)
{
	if(l==r)
	{
		k->val=1;
		return;
	}
	k->val++;
	long long mid=(l+r)>>1;
	if(pos<=mid)
	{
		if(k->l==NULL)k->l=new tree;
		del(k->l,l,mid,pos);
	}
	else
	{
		if(k->r==NULL)k->r=new tree;
		del(k->r,mid+1,r,pos);
	}
}
long long kth(tree *k,long long l,long long r,long long kk)
{
	if(k==NULL)return l+kk-1;
	long long mid=(l+r)>>1,del;del=mid+1-l;
	if(k->l!=NULL)
	{
		del=del-k->l->val;
		if(kk<=del)return kth(k->l,l,mid,kk);
	}
	return kth(k->r,mid+1,r,kk-del);
}
long long n,m,q,M;
vector<long long>v[N];
int main()
{
	n=read();m=read();q=read();M=2*(n+m+q);
	fr(i,0,n)root[i]=new tree;
	while(q--)
	{
		long long x=read(),y=read();
		if(y==m)
		{
			long long pos=kth(root[0],1,M,x),ans;
			del(root[0],1,M,pos);
			if(pos<=n)ans=pos*m;
			else ans=v[0][pos-1-n];
			v[0].push_back(ans);
			printf("%lld\n",ans);
		}
		else
		{
			long long pos1=kth(root[x],1,M,y),pos2=kth(root[0],1,M,x),ans1,ans2;
			del(root[x],1,M,pos1);del(root[0],1,M,pos2);
			if(pos1<m)ans1=(x-1)*m+pos1;
			else ans1=v[x][pos1-m];
			if(pos2<=n)ans2=pos2*m;
			else ans2=v[0][pos2-1-n];
			v[0].push_back(ans1);v[x].push_back(ans2);
			printf("%lld\n",ans1);
		}
	}
	return 0;
}