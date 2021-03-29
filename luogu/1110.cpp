/**************************************************************
	File name: 1110.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 9/9/2018, 12:57:54 PM
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
#include<set>
#define N 500010
int n,q,a[N],l[N],ans=(1<<29);
char opt[10];
multiset<int>s1;
set<int>s2;
int main()
{
	n=read();q=read();
	fr(i,1,n)
	{
		a[i]=l[i]=read();
		auto _=s2.size();
		auto it=s2.insert(a[i]).first;
		if(s2.size()==_)ans=0;
		if(it!=s2.begin())
		{
			int k=*it;
			it--;
			ans=min(ans,abs(k-*it));
			it++;
		}
		if(it!=s2.end())
		{
			int k=*it;
			it++;
			ans=min(ans,abs(k-*it));
			it--;
		}
		if(i!=1)
			s1.insert(abs(a[i]-a[i-1]));
	}
	while(q--)
	{
		scanf("%s",opt);
		if(*opt=='I')
		{
			int p=read(),v=read();
			auto _=s2.size();
			auto it=s2.insert(v).first;
			if(s2.size()==_)ans=0;
			if(it!=s2.begin())
			{
				int k=*it;
				it--;
				ans=min(ans,abs(k-*it));
				it++;
			}
			if(it!=s2.end())
			{
				int k=*it;
				it++;
				ans=min(ans,abs(k-*it));
				it--;
			}
			if(p!=n)
			{
 				s1.erase(s1.find(abs(a[p+1]-l[p])));
				s1.insert(abs(l[p]-v));
				s1.insert(abs(a[p+1]-v));
				l[p]=v;
			}
			else
			{
				s1.insert(abs(l[p]-v));
				l[p]=v;
			}
		}
		else if(opt[4]=='G')
			printf("%d\n",*s1.begin());
		else
			printf("%d\n",ans);
	}
	return 0;
}