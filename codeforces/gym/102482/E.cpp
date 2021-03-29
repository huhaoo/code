/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Thu 22 Oct 2020 04:07:11 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=50;
const double eps=1e-9,g=9.80665;
int n,m,x,y;
double w,v,h[N][N];
int d[N*N][N*N]; 
int k;
double H[N],l[N];
int X,Y;
void solve(double x,double y,double dx,double dy,double l,double r)
{
	if(r-l<eps) return ;
//	printf("%.10lf %.10lf      %.10lf %.10lf %.10lf %.10lf\n",l,r,x+l*dx,x+r*dx,y+l*dy,y+r*dy);
	if(int(x+l*dx)==int(x+r*dx)&&int(y+l*dy)==int(y+r*dy))
	{
		int _x=int(x+l*dx),_y=int(y+l*dy);
//		printf("%.10lf %.10lf %d %d\n",l,r,_x,_y);
		if(_x==X&&_y==Y) ::l[k]=r;
		else
		{
			if(::l[k]-::l[k-1]>1e-8) k++;
			H[k]=h[_x][_y]; ::l[k]=r;
			X=_x; Y=_y;
		}
		return ;
	}
	double mid=(l+r)/2;
	solve(x,y,dx,dy,l,mid); solve(x,y,dx,dy,mid,r);
}
double calc(double dx,double t){ return t*(2*dx-g*t)/2; }
double Calc(double dx,double d)
{
	double dy=sqrt(v*v-dx*dx),t=d/dx;
	return t*(2*dy-t*g)/2;
}
int main()
{
	m=read(); n=read(); w=read(); v=read(); y=read(); x=read();
	fr(i,0,n-1) fr(j,0,m-1) h[i][j]=read();
	fr(i,0,n*m-1) fr(j,0,n*m-1) d[i][j]=N*N;
	fr(i,0,n-1) fr(j,0,m-1) fr(I,0,n-1) fr(J,0,m-1)
	{
		int p1=i*m+j,p2=I*m+J;
		if(p1==p2){ d[p1][p2]=0; continue; }
		X=i; Y=j; H[k=1]=h[X][Y];
		double _d=sqrt((i-I)*(i-I)+(j-J)*(j-J));
		solve(i+0.5,j+0.5,(I-i)/_d,(J-j)/_d,0,_d);
		_d*=w; fr(i,1,k) l[i]*=w;
		double l=eps,r=v;
		while(r-l>eps)
		{
			double p=(r-l)/3,p1=l+p,p2=r-p;
			if(Calc(p1,_d)<Calc(p2,_d)) l=p1;
			else r=p2;
		}
//		printf(" %.10lf %.10lf %.10lf\n",l,Calc(l,_d),_d/l);
		if(Calc(l,_d)<h[I][J]-h[i][j]) continue;
		l=eps;
		while(r-l>eps)
		{
			double mid=(l+r)/2;
			if(Calc(mid,_d)<h[I][J]-h[i][j]) l=mid;
			else r=mid;
		}
//		printf("%d %d %d %d  %.10lf %.10lf  %.10lf %d\n",i,j,I,J,l,Calc(l,_d),_d/l,k);
		double _x=l,_y=sqrt(v*v-_x*_x);
		int flag=1;
/*		fr(o,1,k) printf("%.5lf%c",::l[o],o==end_o?'\n':' ');
		fr(o,1,k) printf("%.5lf%c",calc(_y,::l[o]/_x),o==end_o?'\n':' ');
		fr(o,1,k) printf("%.5lf%c",H[o],o==end_o?'\n':' ');
		putchar(10);*/
		fr(o,1,k)
		{
			if(o!=k&&calc(_y,::l[o]/_x)<H[o]-h[i][j]) flag=0;
			if(o!=1&&calc(_y,::l[o-1]/_x)<H[o]-h[i][j]) flag=0;
		}
		fr(a,std::min(i,I)+1,std::max(i,I)) fr(b,std::min(j,J)+1,std::max(j,J)) if((a*2-(i*2+1))*((J*2+1)-b*2)==(b*2-(j*2+1))*((I*2+1)-a*2))
		{
			double D=sqrt((a-i-0.5)*(a-i-0.5)+(b-j-0.5)*(b-j-0.5))*w;
			fr(A,-1,0) fr(B,-1,0) if(calc(_y,D/_x)<h[a+A][b+B]-h[i][j]) flag=0;
		}
		if(flag) d[p1][p2]=1;
	}
	fr(k,0,n*m-1) fr(i,0,n*m-1) fr(j,0,n*m-1) d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
	x=(x-1)*m+y-1;
	fr(i,0,n-1) fr(j,0,m-1)
	{
		if(d[x][i*m+j]==N*N) printf("X");
		else printf("%d",d[x][i*m+j]);
		putchar(j==m-1?'\n':' ');
	}
	return 0;
}
