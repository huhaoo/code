/***************************************************************
	File name: kingdom.cpp
	Author: huhao
	Create time: Fri 08 Jan 2021 09:22:58 AM CST
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
const int N=2010; const double pi=acos(-1.);
int n,p[N][N],P[N][N];
double x[N],y[N],R;
int f[N];
int main()
{
	freopen("kingdom.in","r",stdin); freopen("kingdom.out","w",stdout);
	n=read(); R=read();
	fr(i,1,n){ x[i]=read(); y[i]=read(); }
	fr(i,1,n)
	{
		double l=0,r=pi*4;
		fr(j,i+1,n)
		{
			double d=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			double t=atan2(y[j]-y[i],x[j]-x[i]);
			if(t<0) t+=2*pi;
			if((l<=t&&t<=r)||(l<=t+2*pi&&t+2*pi<=r)) p[i][j]=1;
//			printf("%d %d   %.10lf %.10lf  %d\n",i,j,d,t,p[i][j]);
			if(d-1e-6>R)
			{
				double dt=asin(R/d);
				double L=t-dt,R=t+dt;
//				printf("%.10lf %.10lf\n",L,R);
				if(L<0){ L+=2*pi; R+=2*pi; }
				if(r<L){ l+=2*pi; r+=2*pi; }
				if(R<l){ L+=2*pi; R+=2*pi; }
				l=std::max(l,L); r=std::min(r,R);
			}
		}
	}
	fr(i,1,n)
	{
		double l=0,r=pi*4;
		fd(j,i-1,1)
		{
			double d=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			double t=atan2(y[j]-y[i],x[j]-x[i]);
			if(t<0) t+=2*pi;
			if((l-1e-6<=t&&t<=r+1e-6)||(l-1e-6<=t+2*pi&&t+2*pi<=r+1e-6)) P[i][j]=1;
//			printf("%d %d   %.10lf %.10lf  %d\n",i,j,d,t,P[i][j]);
			if(d-1e-6>R)
			{
				double dt=asin(R/d);
				double L=t-dt,R=t+dt;
//				printf("%.10lf %.10lf\n",L,R);
				if(L<0){ L+=2*pi; R+=2*pi; }
				if(r<L){ l+=2*pi; r+=2*pi; }
				if(R<l){ L+=2*pi; R+=2*pi; }
				l=std::max(l,L); r=std::min(r,R);
			}
		}
	}
//	fr(i,1,n) fr(j,i+1,n) printf("%d%c",p[i][j]&&P[j][i],j==n?'\n':' ');
	f[1]=1;
	fr(i,2,n)
	{
		f[i]=N;
		fr(j,1,i-1) if(P[i][j]&&p[j][i]) f[i]=std::min(f[i],f[j]+1);
	}
	printf("%d\n",f[n]);
	return 0;
}
