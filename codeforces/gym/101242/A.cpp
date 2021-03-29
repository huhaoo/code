/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Wed 18 Nov 2020 09:58:30 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#include<queue>
const int N=100010;
int m,k,n,a[N],b[N],c[N],ans;
std::vector<int> e[N];
std::priority_queue<int,std::vector<int>,std::greater<int> > q;
int main()
{
	m=read(); k=read();
	fr(i,1,m) n+=(a[i]=read());
	fr(i,1,k){ b[(i-1)%n+1]=read(); }
	k%=n;
	fr(i,1,k) c[b[i]]++;
	fr(i,1,m)
	{
		int lst=0;
		fr(j,1,a[i])
		{
			int p=((i64)j*n-1)/a[i]+1;
			if((i64)lst*n%a[i]==0) lst++;
			if(j>c[i]) e[std::max(lst,k+1)].push_back(p);
//			printf("%d/%d %d   [%d,%d]\n",a[i],n,j,lst,p);
			lst=p;
		}
	}
	ans=n;
	fr(i,k+1,n)
	{
		for(auto j:e[i]) q.push(j);
		if(q.empty()){ ans=i-1; break; }
		q.pop();
		if(!q.empty()&&q.top()==i){ ans=i-1; break; }
	}
	if(ans==n) printf("forever\n");
	else printf("%d\n",ans-k);
	return 0;
}
