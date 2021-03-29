/**************************************************************
	File name: 2048.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/14/2018, 2:05:10 PM
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
#include<queue>
#define A 1000000000
#define N 500010
#define B 40
int n,k,L,R,a[N],s[N*B][2],v[N*B],r[N],cnt,w[N],K[N],m[N];
long long ans;
struct node
{
	int p;
	node(int a=0){p=a;}
};
bool operator<(node b,node c)
{
	return a[b.p]-w[b.p]<a[c.p]-w[c.p];
}
priority_queue<node>q;
int add(int k,int p,int l,int r)
{
	cnt++;int t=cnt;v[t]=v[k]+1;
	if(l==r)return t;
	int mid=(l+r)>>1;
	if(p<=mid)
	{
		s[t][1]=s[k][1];
		s[t][0]=add(s[k][0],p,l,mid);
	}
	else
	{
		s[t][0]=s[k][0];
		s[t][1]=add(s[k][1],p,mid+1,r);
	}
	return t;
}
int kth(int a,int b,int l,int r,int k)
{
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(v[s[a][0]]-v[s[b][0]]>=k)return kth(s[a][0],s[b][0],l,mid,k);
	else return kth(s[a][1],s[b][1],mid+1,r,k-(v[s[a][0]]-v[s[b][0]]));
}
void print(int x,int l,int r)
{
	if(!x)return;
	int mid=(l+r)>>1;
	print(s[x][0],l,mid);
	if(v[x])printf("%d %d %d\n",v[x],l,r);
	print(s[x][1],mid+1,r);
}
int main()
{
	n=read();k=read();L=read();R=read();
	r[1]=add(r[0],0,-A,A);
	fr(i,1,n)r[i+1]=add(r[i],a[i]=a[i-1]+read(),-A,A);
//	print(r[n+1],-A,A);
	fr(i,L,n)K[i]=2,w[i]=kth(r[i-L+1],r[max(i-R,0)],-A,A,1),m[i]=(i-L+1)-max(i-R,0);
//	fr(i,1,n)printf("%d%c",w[i],i==n?'\n':' ');
	fr(i,L,n)q.push(i);
	while(k--)
	{
		int aa=q.top().p;q.pop();
		ans+=a[aa]-w[aa];
		if(K[aa]<=m[aa])
		{
			w[aa]=kth(r[aa-L+1],r[max(aa-R,0)],-A,A,K[aa]);
			K[aa]++;
			q.push(aa);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
//1112