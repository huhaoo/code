/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Sat 14 Nov 2020 09:00:24 AM CST
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
#include<set>
#define pii std::pair<int,int>
#define piii std::pair<pii,int>
const int N=800010,inf=1000000001;
int n,m;
int f[N];
pii p[N],P[N];
std::set<piii> s;
piii a[N];
pii rev(pii a){ return pii(a.second,a.first); }
struct seg
{
	int h,l,r,op;
	seg(int H=0,int L=0,int R=0,int Op=0){ h=H; l=L; r=R; op=Op; }
} b[N];
void ins(int x,int y,int X,int Y)
{
//	printf("+ %d %d   %d %d\n",x,y,X,Y);
	b[++m]=seg(x,y,Y,1); b[++m]=seg(X+1,y,Y,-1);
}
std::set<pii> S;
int main()
{
	n=read();
	fr(i,1,n){ p[i].first=read(); p[i].second=read(); a[++m]=piii(p[i],i); }
	fr(i,1,n){ P[i].first=read(); P[i].second=read(); a[++m]=piii(P[i],-i); }
	std::sort(a+1,a+m+1); std::reverse(a+1,a+m+1);
	fr(i,1,m)
	{
//		printf("%d %d  %d\n",a[i].first.first,a[i].first.second,a[i].second);
		if(a[i].second>0)
		{
			auto it=s.upper_bound(piii(rev(a[i].first),-inf));
			if(it==s.end()){ printf("syntax error\n"); return 0; }
			f[a[i].second]=-(it->second); s.erase(it);
		}
		else s.insert(piii(rev(a[i].first),a[i].second));
	}
	m=0;
	fr(i,1,n)
	{
		int j=f[i];
		int x=p[i].first,y=p[i].second,X=P[j].first,Y=P[j].second;
		if(x+1>=X||y+1>=Y)
		{
			ins(x,y,X,Y);
			continue;
		}
		ins(x,y,X,y);
		ins(x,Y,X,Y);
		ins(x,y+1,x,Y-1);
		ins(X,y+1,X,Y-1);
	}
//	fr(i,1,n) printf("%d\n",f[i]);
	std::sort(b+1,b+m+1,[](seg a,seg b){ return a.h==b.h?a.op<b.op:a.h<b.h; });
	fr(i,1,m)
	{
//		printf("%d   %d %d   %d\n",b[i].h,b[i].l,b[i].r,b[i].op);
//		continue;
		if(b[i].op==1)
		{
			auto it=S.upper_bound(pii(b[i].l,inf));
			if(it!=S.end())
			{
				if(it->first<=b[i].r)
				{
					printf("syntax error\n");
					return 0;
				}

			}
			if(it!=S.begin())
			{
				it--;
				if(it->second>=b[i].l)
				{
					printf("syntax error\n");
					return 0;
				}
			}
			S.insert(pii(b[i].l,b[i].r));
		}
		else S.erase(S.find(pii(b[i].l,b[i].r)));
	}
	fr(i,1,n) printf("%d\n",f[i]);
	return 0;
}
