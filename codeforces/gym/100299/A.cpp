/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Tue 29 Dec 2020 05:02:44 PM CST
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
#include<string>
#include<iostream>
const int N=110;
int n,m,a[N][N],A[N][N],x,y;
std::vector<std::string> ans;
#define nosol { printf("IMPOSSIBLE\n"); return ; }
void R(int u)
{
	fr(i,1,y) std::swap(a[u][i],a[u][m+1-i]);
	ans.push_back("R"+std::to_string(u));
}
void C(int u)
{
	fr(i,1,x) std::swap(a[i][u],a[n+1-i][u]);
	ans.push_back("C"+std::to_string(u));
}
void solve()
{
	m=read(); n=read(); x=n/2; y=m/2; ans.clear();
	fr(i,1,n) fr(j,1,m) a[i][j]=read();
	fr(i,1,n) fr(j,1,m) A[i][j]=(i-1)*m+j;
	if(n&1)
	{
		if(a[x+1][1]!=A[x+1][1]) R(x+1);
		fr(i,1,m) if(a[x+1][i]!=A[x+1][i]) nosol;
	}
	if(m&1)
	{
		if(a[1][y+1]!=A[1][y+1]) C(y+1);
		fr(i,1,m) if(a[i][y+1]!=A[i][y+1]) nosol;
	}
	fr(i,1,x) fr(j,1,y)
	{
		int I=n-i+1,J=m-j+1;
		     if(a[i][j]==A[i][j]) ;
		else if(a[I][j]==A[i][j]){ C(j); R(i); C(j); R(i); }
		else if(a[i][J]==A[i][j]){ R(i); C(j); R(i); C(j); }
		else if(a[I][J]==A[i][j]){ R(i); C(J); R(i); C(J); }
		else nosol;
		     if(a[i][J]==A[i][J]) ;
		else if(a[I][J]==A[i][J]){ R(I); C(J); R(I); C(J); }
		else if(a[I][j]==A[i][J]){ C(J); R(I); C(J); R(I); }
		else nosol;
	}
//	fr(i,1,n) fr(j,1,m) printf("%d%c",a[i][j],j==m?'\n':' ');
	fr(i,n-x+1,n-x+1) fr(j,1,y) if(a[i][j]!=A[i][j])
	{
		fr(I,i,n){ R(I); C(j); R(I); C(j); }
		C(j);
		fr(t,1,2) fr(I,i,n){ R(I); C(j); R(I); C(j); }
	}
//	fr(i,1,n) fr(j,1,m) printf("%d%c",a[i][j],j==m?'\n':' ');
	fr(i,n-x+2,n)
	{
		if(a[i][1]!=A[i][1]) R(i);
		fr(j,1,m) if(a[i][j]!=A[i][j]) nosol;
	}
	printf("POSSIBLE %d",ans.size());
	for(auto i:ans) std::cout<<" "<<i;
	putchar(10);
}
int main()
{
	fr(T,1,read()) solve();
	return 0;
}
