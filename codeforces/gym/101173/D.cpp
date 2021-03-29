/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Wed 25 Nov 2020 08:19:15 AM CST
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
#include<vector>
const int N=10,M=40010;
int n,f[N][N];
void solve(int x,int y,std::vector<int> a)
{
	if((x==6&&y==6)||a.empty()) return ;
	assert(a.size()<=f[x][y]);
	int mi=a[0];
	for(auto i:a) mi=std::min(mi,i);
	fr(i,0,a.size()-1) a[i]-=mi;
//	printf("%d %d\n",x,y);
//	for(auto i:a) printf(" %d",i);; putchar(10);
	if(x+y==11)
	{
		int c=(x==6?'R':'D');
		if(a.size()==1||(a[0]>a[1])) printf("%d %d %c %d\n",x,y,c,a.size());
		else fr(i,0,1) printf("%d %d %c 1\n",x,y,c);
		return ;
	}
	static int X[M],Y[M]; std::vector<int> A[N][N]; int t=0,n=a.size();
	fr(i,x,6) fr(j,y,6) if(i!=x||j!=y) fr(k,1,f[i][j])
	{
		X[t]=i; Y[t]=j; t++;
		if(t==n) goto end;
	}
end:;
//	fr(i,0,n-1) printf("(%d %d)%c",X[i],Y[i],i==n-1?'\n':' ');
//	return ;
	fd(i,n-1,0)
	{
		int _x=X[a[i]],_y=Y[a[i]],x_=x,y_=y;
		assert(x_<=_x&&y_<=_y);
		A[_x][_y].push_back(a[i]);
		while(x_!=_x){ printf("%d %d D 1\n",x_,y_); x_++; }
		while(y_!=_y){ printf("%d %d R 1\n",x_,y_); y_++; }
	}
	fd(i,6,x) fd(j,6,y) solve(i,j,A[i][j]);
}
int main()
{
	n=read();
	std::vector<int> a;
	fr(i,1,n) a.push_back(read());
	f[6][6]=1;
	fd(i,6,1) fd(j,6,1) if(i!=6||j!=6)
	{
		fr(x,i,6) fr(y,j,6) f[i][j]+=f[x][y];
		if(i+j==11) f[i][j]++;
	}
	solve(1,1,a);
//	fr(i,1,6) fr(j,1,6) printf("%d%c",f[i][j],j==6?'\n':' ');
	return 0;
}
