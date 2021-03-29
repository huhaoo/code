/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Wed 06 Jan 2021 11:23:14 AM CST
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
#define poly std::vector<int>
poly operator*(int b,poly a)
{
	fr(i,0,a.size()-1) a[i]*=b;
	fr(i,0,a.size()-2){ a[i+1]+=a[i]/10; a[i]%=10; }
	while(a[a.size()-1]>=10){ a.push_back(a[a.size()-1]/10); a[a.size()-2]%=10; }
	return a;
}
poly operator+(poly a,poly b)
{
	a.resize(std::max(a.size(),b.size()));
	fr(i,0,b.size()-1) a[i]+=b[i];
	fr(i,0,a.size()-2){ a[i+1]+=a[i]/10; a[i]%=10; }
	while(a[a.size()-1]>=10){ a.push_back(a[a.size()-1]/10); a[a.size()-2]%=10; }
	return a;
}
poly operator-(poly a,poly b)
{
	fr(i,0,b.size()-1) a[i]-=b[i];
	fr(i,0,a.size()-2) if(a[i]<0){ a[i+1]--; a[i]+=10; }
	while(!a.empty()&&a[a.size()-1]==0) a.pop_back();
	return a;
}
poly init(int n){ poly a={n}; while(a[a.size()-1]>=10){ a.push_back(a[a.size()-1]/10); a[a.size()-2]%=10; } return a; }
#include<set>
#include<queue>
std::set<poly> vis;
std::set<std::vector<poly> > Vis;
int n,k;
std::queue<std::vector<poly> > q;
int main()
{
	k=read(); n=read();
	q.push({init(1),init(k),init(k*k+k)});
	while(n)
	{
		auto u=q.front(); q.pop();
		if(u[0].empty()||u[1].empty()||u[2].empty()) continue;
		std::sort(u.begin(),u.end());
		if(Vis.count(u)) continue;
		Vis.insert(u);
//		for(auto i:u){ fd(j,i.size()-1,0) putchar(i[j]+48); putchar(' '); } putchar('\n');
		if(!vis.count(u[0])&&!vis.count(u[1])&&!vis.count(u[2]))
		{
			n--;
			vis.insert(u[0]); vis.insert(u[1]); vis.insert(u[2]);
			for(auto i:u){ fd(j,i.size()-1,0) putchar(i[j]+48); putchar(' '); } putchar('\n');
		}
		q.push({k*(u[1]+u[2])-u[0],u[1],u[2]});
		q.push({u[0],k*(u[0]+u[2])-u[1],u[2]});
		q.push({u[0],u[1],k*(u[0]+u[1])-u[2]});
	}
	return 0;
}
