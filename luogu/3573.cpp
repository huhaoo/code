/***************************************************************
	File name: 3573.cpp
	Author: huhao
	Create time: Thu 24 Oct 2019 02:08:10 PM CST
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
#include<set>
namespace run
{
	const int N=2000010;
	int n,m,begin[N],next[N],to[N],d[N],q[N],l,r,e,s1[N],s2[N],id[N];
	multiset<int>s;
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int main()
	{
		n=read();
		m=read();
		fr(i,1,m)
		{
			int u=read(),v=read();
			add(u,v);
			d[v]++;
		}
		l=1;
		fr(i,1,n)
			if(!d[i])
				q[++r]=i;
		while(l<=r)
		{
			int u=q[l++];
			fo(i,u)
			{
				d[to[i]]--;
				if(!d[to[i]])
					q[++r]=to[i];
			}
		}
		fr(i,1,n)
			fo(j,q[i])
				s1[to[j]]=max(s1[to[j]],s1[q[i]]+1);
		fd(i,n,1)
			fo(j,q[i])
				s2[q[i]]=max(s2[to[j]]+1,s2[q[i]]);
		fr(i,1,n)
		{
			id[q[i]]=i;
			s.insert(s1[q[i]]);
		}
		fr(i,1,n)
			fo(j,q[i])
				if(id[to[j]]>i)
					add(to[j],q[i]);
		int ans=n,Ans=0;
//		for(auto j:s)
//			printf("%d ",j);
//		putchar(10);
		fd(i,n,1)
		{
//			printf("%d\n",q[i]);
			s.erase(s.find(s1[q[i]]));
			fo(j,q[i])
				if(id[to[j]]>i)
				{
//					printf("del %d %d\n",q[i],to[j]);
					s.erase(s.find(s1[q[i]]+s2[to[j]]+1));
				}
//			for(auto j:s)
//				printf("%d ",j);
//			putchar(10);
			if(ans>*(--s.end()))
			{
				ans=*(--s.end());
				Ans=q[i];
			}
			s.insert(s2[q[i]]);
			fo(j,q[i])
				if(id[to[j]]<i)
				{
//					printf("ins %d %d\n",q[i],to[j]);
					s.insert(s2[q[i]]+s1[to[j]]+1);
				}
//			for(auto j:s)
//				printf("%d ",j);
//			putchar(10);
		}
		printf("%d %d\n",Ans,ans);
		return 0;
	}
}
int main()
{
	return run::main();
}
