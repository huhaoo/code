/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 07:24:14 PM CST
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
#include<queue>
#include<random>
#include<map>
std::mt19937 _rand;
#define rand _rand
const int N=10010;
int n,m;
int p1[N],p2[N];
std::map<int,bool> Q[N];
int ask(int i,int j){ printf("? %d %d\n",i,j); fflush(stdout); char c=getchar(); while(c!='<'&&c!='>') c=getchar(); return c=='>'; }
void answer(std::vector<int> e,std::vector<int> o){ printf("!"); for(auto i:e) printf(" %d",i); for(auto i:o) printf(" %d",i); putchar(10); }
void answer()
{
	std::vector<int> e(n),o(m);
	fr(i,1,n) e[p1[i]-1]=i*2;
	fr(i,1,m) o[p2[i]-1]=i*2-1;
	answer(e,o);
}
int ask(int i,int j,int op){ if(op==2) std::swap(i,j); return (op==2)^(Q[i].count(j)?Q[i][j]:Q[i][j]=ask(i,j)); }
struct ran
{
	int l,r,op;
	ran(int L,int R,int Op){ l=L; r=R; op=Op; }
} ;
bool operator<(ran a,ran b){ return a.r-a.l<b.r-b.l; }
int id1[N],id2[N],c1,c2;
std::priority_queue<ran> q;
void work(int _n)
{
	n=_n/2; m=_n-n;
	fr(i,1,n) p1[i]=i;
	fr(i,1,m) p2[i]=i;
	c1=c2=1;
	fr(i,1,n) id1[i]=1;
	fr(i,1,m) id2[i]=1;
	if(n>1) q.push({1,n,1});
	if(m>1) q.push({1,m,2});
	while(!q.empty())
	{
		ran t=q.top(); q.pop();
		int l=t.l,r=t.r,op=t.op;
/*		printf("> %d %d  %d\n",l,r,op);
		fr(i,1,n) printf("%d%c",p1[i],i==n?'\n':' ');
		fr(i,1,n) printf("%d%c",id1[i],i==n?'\n':' ');
		fr(i,1,m) printf("%d%c",p2[i],i==m?'\n':' ');
		fr(i,1,m) printf("%d%c",id2[i],i==m?'\n':' ');*/
		int mid=(l+r)>>1;
		if(op==1) mid++;
		static int a[N],A; A=0;
		fr(i,mid,op==1?m:n)
			if((op==1?id2:id1)[i]==(op==1?id2:id1)[mid]) a[++A]=(op==1?p2:p1)[i];
			else break;
		fd(i,mid-1,1)
			if((op==1?id2:id1)[i]==(op==1?id2:id1)[mid]) a[++A]=(op==1?p2:p1)[i];
			else break;
		while(1)
		{
			static int s1[N],s2[N],t1,t2; t1=0; t2=0;
			int u=a[rand()%A+1],v;
			fr(i,l,r) if(ask(v=(op==1?p1:p2)[i],u,op)) s2[++t2]=v; else s1[++t1]=v;
			if(t1&&t2)
			{
//				printf("%d %d  %d %d   %d\n",l,l+t1-1,r-t2+1,r,op);
				fr(i,1,t1) (op==1?p1:p2)[l+i-1]=s1[i];
				fr(i,1,t2) (op==1?p1:p2)[r-i+1]=s2[i];
				if(op==1)
				{
					c1++;
					fr(i,1,t1) id1[i+l-1]=c1;
				}
				else
				{
					c2++;
					fr(i,1,t1) id2[i+l-1]=c2;
				}
				if(t1>1) q.push({l,l+t1-1,op});
				if(t2>1) q.push({r-t2+1,r,op});
				break;
			}
		}
	}
	answer();
}
int main(){ int n=read(); work(n); return 0; }
