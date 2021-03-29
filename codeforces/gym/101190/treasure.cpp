/***************************************************************
	File name: treasure.cpp
	Author: huhao
	Create time: Sat 21 Nov 2020 04:18:05 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#include<string>
#include<iostream>
const int N=30;

#define io
//#define Auto

#ifdef io
#ifdef Auto
namespace A
{
	std::string St[N];
	int p[N],t[N][N],m,pos,n,s,vis[N][N];
}
std::string go(int st,std::string dir,int pa)
{
	using namespace A;
	static int cnt=0;
	if((++cnt)>20000){ printf("Wrong Answer: step greater than 20000.\n"); exit(0); }
	int P=(p[pos]+pa)%m; p[pos]=(p[pos]+st)%m;
	if(!vis[pos][P]){ vis[pos][P]=1; s++; if(s==n*m){ printf("Accept: step equal to %d.\n",cnt); exit(0); } }
	St[pos]=dir; pos=t[pos][P];
//	printf("Q %d %6s %d => %6s\n",st,dir.c_str(),pa,St[pos].c_str());
	return St[pos];
}
#else
std::string go(int st,std::string dir,int pa){ std::cout<<st<<' '<<dir<<' '<<pa<<std::endl; fflush(stdout); std::string s; std::cin>>s; if(s=="treasure") exit(0); return s; }
#endif
#else
#include"treasure.h"
#endif

const std::string L="left",R="right",C="center";
int n,p[N],mx[N],l[N]; std::string st;
void solve(int m)
{
	n=1; st=C; p[n]=-1;
	while(n)
	{
		if(p[n]==m-1)
		{
//			printf("A %d\n",n);
//			printf("%d %d\n",n,l[n]);
			if(l[n]-1>l[n-1]){ l[n-1]=l[n]-1; mx[n-1]=p[n-1]; }
			int d=(-p[n]+mx[n]+m)%m;
			st=go(d,L,d);
			while(st==L) st=go(0,L,0);
			fr(i,1,l[n]-2) st=go(0,R,0);
			n--; continue;
		}
		if(p[n]==-1) st=go(0,R,0); else st=go(1,R,1);
		p[n]++;
		while(st==C){ n++; l[n]=p[n]=mx[n]=0; st=go(0,R,0); }
		if(st==L)
		{
//			printf("B\n");
			while(st==L) st=go(0,L,0);
			int w=0;
			while(st==R){ st=go(0,R,0); w++; }
			while(st==L) st=go(0,L,0);
			fr(i,1,w-1) st=go(0,R,0);
			if(w>l[n]){ l[n]=w; mx[n]=p[n]; }
		}
		else
		{
//			printf("C\n");
			int w=1; st=go(0,L,0);
			while(st==R){ w++; st=go(0,R,0); }
			fr(i,1,w-1) st=go(0,R,0);
			if(w>l[n]){ l[n]=w; mx[n]=p[n]; }
		}
	}
}

#include<random>

#ifdef io
int main()
{
#ifdef Auto
	using namespace A;
	int &n=A::n,&m=A::m;
	std::cin>>n>>m;
	fr(i,1,n) St[i]=C;
	int op=2;
	switch(op)
	{
		case 1:	
		fr(i,1,n) fr(j,0,m-1) std::cin>>t[i][j];
		break;
		
		case 2:
		freopen("/dev/urandom","r",stdin);
		unsigned int s=0; fr(i,1,100) s=s*s+getchar()+s;
//		s=1909187158;
		printf("sed: %u\n",s);
		std::mt19937 Rand(s);
		static int p[N];
		fr(i,1,n) p[i]=i;
		fr(i,1,n) std::swap(p[i],p[Rand()%i+1]);
		fr(i,1,n) t[p[i]][m-1]=p[i==n?1:i+1];
		fr(i,1,n) fr(j,0,m-2) t[i][j]=Rand()%n+1;
		break;
	}
	printf("E:\n");
	fr(i,1,n) fr(j,0,m-1) printf("%d %d\n",i,t[i][j]);
	pos=1; solve(m);
	printf("Wrong Answer: visited edge : %d/%d.\n",s,A::n*A::m);
#else
	int n; std::string s; std::cin>>n>>s; solve(n); return 0;
#endif
}
#endif
