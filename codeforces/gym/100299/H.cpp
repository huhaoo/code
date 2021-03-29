/***************************************************************
	File name: H.cpp
	Author: huhao
	Create time: Fri 16 Oct 2020 04:13:40 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<bits/extc++.h>
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
const int N=1000010,inf=1000000001;
int l[N][3],r[N][3],n,op[N];
int opt(int i){ fr(j,0,2) if(l[i][j]==r[i][j]) return j; return 0; }
bool in(int l,int r,int p){ return l<=p&&p<=r; }
int l1[N],r1[N],l2[N],r2[N],m1,m2;
int solve()
{
	struct GG
	{
		int x,y,op;
		GG(int X=0,int Y=0,int Op=0){ x=X; y=Y; op=Op; }
	} ;
	static GG g[N]; int m=0;
	fr(i,1,m1) g[++m]=GG(l1[i],r1[i],1);
	fr(i,1,m2) g[++m]=GG(l2[i],r2[i],2);
	std::sort(g+1,g+m+1,[](GG a,GG b){ return a.x>b.x; });
	int mi=inf,mx=-inf,Mi=inf,Mx=-inf;
	fr(i,1,m)
		if(g[i].op==2)
		{
			if(g[i].y>=mi) return 0;
			if(g[i].y<=mx) return 0;
			Mx=std::max(Mx,g[i].x);
			Mi=std::min(Mi,g[i].y);
		}
		else
		{
			if(g[i].y>=Mi) return 0;
			if(g[i].y<=Mx) return 0;
			mx=std::max(mx,g[i].x);
			mi=std::min(mi,g[i].y);
		}
	return 1;
}
int main()
{
	fr(T,1,read())
	{
		n=read();
		fr(i,1,n)
		{
			fr(j,0,2) l[i][j]=read();
			fr(j,0,2) r[i][j]=read();
			fr(j,0,2) if(l[i][j]>r[i][j]) std::swap(l[i][j],r[i][j]);
			op[i]=opt(i);
		}
		int ans=0;
		fr(t,0,2)
		{
			int flag=1,f0=0,f1=0;
			fr(i,1,n) if(op[i]==t) f0=1;
			fr(i,1,n) if(op[i]!=t) f1=1;
			if(!f0||!f1) continue;
			int L=inf,R=-inf;
			fr(i,1,n) if(op[i]==t){ L=std::min(L,l[i][t]); R=std::max(R,r[i][t]); }
			fr(i,1,n) if(op[i]!=t&&(l[i][t]>L||r[i][t]<R)) flag=0;
			if(!flag) continue;
			int t1=t==0?1:0,t2=t==2?1:2;
			m1=m2=0;
			L=-inf; R=inf;
			fr(i,1,n) if(op[i]==t){ L=std::max(L,l[i][t2]); R=std::min(R,r[i][t2]); }
			fr(i,1,n)
				if(op[i]==t){ m1++; l1[m1]=l[i][t1]; r1[m1]=r[i][t1]; }
				else if(op[i]==t2){ m2++; l2[m2]=l[i][t1]; r2[m2]=r[i][t1]; if(!in(L,R,l[i][t2])) flag=0; }
			if(!solve()) flag=0;
			m1=m2=0;
			L=-inf; R=inf;
			fr(i,1,n) if(op[i]==t){ L=std::max(L,l[i][t1]); R=std::min(R,r[i][t1]); }
			fr(i,1,n)
				if(op[i]==t){ m1++; l1[m1]=l[i][t2]; r1[m1]=r[i][t2]; }
				else if(op[i]==t1){ m2++; l2[m2]=l[i][t2]; r2[m2]=r[i][t2]; if(!in(L,R,l[i][t1])) flag=0; }
			if(!solve()) flag=0;
			if(flag)
			{
				ans=1;
//				printf("%d\n",t);
			}
		}
		printf("%s\n",ans?"YES":"NO");
	}
	return 0;
}
