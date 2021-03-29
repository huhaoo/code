/***************************************************************
	File name: lonely.cpp
	Author: huhao
	Create time: Fri 08 Jan 2021 10:45:11 AM CST
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
#include<map>
#include<vector>
std::map<int,double> a,b,A,B;
void update(std::map<int,double> &a,std::map<int,double> &b,int x,int X,int y,int Y)
{
//	printf("%d %d  %d %d\n",x,y,X,Y);
	if(x==X) return ;
	double t=(double)(Y-y)/(X-x);
	a[x]+=y; a[X]-=Y; b[x]+=t; b[X]-=t;
}
std::vector<std::pair<int,double> > c,d,C,D;
double ans;
int main()
{
	freopen("lonely.in","r",stdin); freopen("lonely.out","w",stdout);
	int mx=0,Mx=0;
	for(int n=read()-1,x=read(),y=read(),X,Y;n--;)
	{
		X=read(); Y=read(); mx=std::max(mx,Y);
//		printf("        %d %d %d %d\n",x,y,X,Y);
		if(y<Y) update(a,b,y,Y,-x,-X);
		else update(a,b,Y,y,X,x);
		x=X; y=Y;
	}
	for(int n=read()-1,x=read(),y=read(),X,Y;n--;)
	{
		X=read(); Y=read(); Mx=std::max(Mx,Y);
		if(y<Y) update(A,B,y,Y,-x,-X);
		else update(A,B,Y,y,X,x);
		x=X; y=Y;
	}
	if(mx!=Mx){ printf("Invalid plan\n"); return 0; }
	for(auto i:a){ A[i.first]+=0; B[i.first]+=0; }
	for(auto i:A){ a[i.first]+=0; b[i.first]+=0; }
	for(auto i:a) c.push_back(i);
	for(auto i:b) d.push_back(i);
	for(auto i:A) C.push_back(i);
	for(auto i:B) D.push_back(i);
	double x=0,y=0,z=0,w=0;
	fr(i,0,c.size()-2)
	{
		int m=c[i+1].first-c[i].first;
		x+=c[i].second; y+=d[i].second; z+=C[i].second; w+=D[i].second;
//		printf("%d  %.10lf %.10lf %.10lf %.10lf\n",m,x,y,z,w);
		double a=x*z,b=x*w+y*z,c=y*w;
		ans+=a*m+b*m*m/2+c*m*m*m/3; x+=y*m; z+=w*m;
	}
	printf("%.10lf\n",ans);
	return 0;
}
