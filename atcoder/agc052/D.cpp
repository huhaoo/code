/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Tue 09 Mar 2021 03:21:30 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#include<vector>
const int N=200010;
int add(std::vector<int> &a,int v)
{
	int ans;
	if(a.empty()||a[a.size()-1]<v){ a.push_back(v); ans=a.size()-1; }
	else a[ans=std::lower_bound(a.begin(),a.end(),v)-a.begin()]=v;
	return ans;
}
int T;
int n,p[N];
int a[N],b[N],c,q[N];
std::vector<int> A,B;
int main()
{
	T=read();
	while(T--)
	{
		n=read(); A.clear(); B.clear();
		fr(i,1,n){ p[i]=read(); q[i]=0; }
		fr(i,1,n) a[i]=add(A,p[i]);
		fd(i,n,1) b[i]=add(B,-p[i]);
		c=A.size(); p[n+1]=n+1; int lst=n+1;
//		printf("%d\n",c);
//		fr(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
		for(int i=c,j=n;i;i--)
		{
			while((a[j]+1)!=i||p[j]>p[lst]) j--;
			q[j]=1; lst=j;
		}
		int ans=(c%2==0);
		fr(i,1,n) if(!q[i]&&a[i]+b[i]+1>=(c+1)/2) ans=1;
		printf("%s\n",ans?"YES":"NO");
	}
	return 0;
}
