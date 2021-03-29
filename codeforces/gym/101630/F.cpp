/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Mon 04 Jan 2021 03:33:18 PM CST
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
std::vector<std::vector<int> > ans;
int n;
void solve(int x,int y,int op)
{
//	printf(" %d %d %d\n",x,y,op);
	if(x<=n&&y<=n)
	{
		if(op==0) ans.push_back({0,y-n,n,y});
		else ans.push_back({x,n,x-n,0});
		return ;
	}
	if(x<y)
	{
		ans.push_back({x,y,x-n,y-n}); x-=n; y-=n+1;
		if(x<0) x=0;
		solve(x,y,0);
	}
	else
	{
		ans.push_back({x-n,y-n,x,y}); x-=n+1; y-=n;
		if(y<0) y=0;
		solve(x,y,1);
	}
}
int main()
{
	fr(T,1,read())
	{
		int x=read(),y=read(); n=read(); int rx=0,ry=0; ans.clear(); n--;
		if(x<0){ x=-x; rx=1; }
		if(y<0){ y=-y; ry=1; }
		solve(x,y,0);
		printf("%d\n",ans.size());
		for(auto i:ans)
		{
			int x=i[0],y=i[1],z=i[2],w=i[3];
			if(rx){ x=-x; z=-z; }
			if(ry){ y=-y; w=-w; }
			printf("%d %d %d %d\n",x,y,z,w);
		}
	}
	return 0;
}
