/***************************************************************
	File name: interactive.cpp
	Author: huhao
	Create time: Fri 13 Nov 2020 02:30:00 PM CST
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
const int N=110,inf=1000000000,offline_mode=0;
int f[N],o[N],m,t;
int x,y,T;
bool check(int l,int r)
{
	printf("check %d %d\n",l,r); fflush(stdout);
	if(offline_mode){ int v=x; T++; x+=y; if(l<=v&&v<=r){ printf("> Yes\n"); return 1; } else{ printf("> No\n"); return 0; } }
	char c=0; while(c!='Y'&&c!='N') c=getchar(); return c=='Y';
}
void solve(int x,int y,int dx,int dy,int n)
{
	if(!n) return ;
	int m=n>>1; t++;
	f[t]=(x+m*dx)+(y+m*dy)*t;
	if(o[t]=check(0,f[t])) solve(x,y,dx,dy,m);
	else solve(x+(m+1)*dx,y+(m+1)*dy,dx,dy,n-m-1);
}
#define pii std::pair<int,int>
std::vector<pii> a;
int intercept(int,int)
{
	m=100000; check(0,0); t=1;
	if(o[1]=check(0,f[1]=m))
	{
		solve(0,0,1,0,m);
		fr(i,1,10){ t++; f[t]=0; o[t]=check(0,f[t]); }
		solve(0,0,0,1,m);
		solve(m,0,-1,1,m);
	}
	else
	{
		solve(0,m,1,0,m);
		fr(i,1,10){ t++; f[t]=0; o[t]=check(0,f[t]); }
		solve(m,0,0,1,m);
		solve(m,0,-1,1,m);
	}
	fr(i,0,m)
	{
		int l=0,r=m;
		fr(j,1,t)
		{
			int p=f[j]-i*j;
			if(o[j]) r=std::min(r,p);
			else l=std::max(l,p+1);
		}
		fr(j,l,r) a.push_back(pii(j,i));
	}
	while(a.size()>1)
	{
		int n=a.size(); std::vector<int> b(n); std::vector<pii> A,B; t++;
		fr(i,0,n-1) b[i]=a[i].first+a[i].second*t;
		std::sort(b.begin(),b.end());
		int v=b[(n-1)/2];
		fr(i,0,n-1)
			if(a[i].first+a[i].second*t<=v) A.push_back(a[i]);
			else B.push_back(a[i]);
		if(check(0,v)) a=A;
		else a=B;
	}
	t++;
	return a[0].first+a[0].second*t;
}
int main()
{
	x=read(); y=read();
	printf("answer %d\n",intercept(x,y));
	if(offline_mode) printf("%d  %d\n",x,T);
	return 0;
}
