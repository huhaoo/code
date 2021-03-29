/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Tue 27 Oct 2020 11:15:37 AM CST
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
const int N=12,M=1<<10|10,inf=1<<20;
int vis[M][N][N][N][N],f[M][N][N][N][N];
int n,l[N],a[N][N],A[N][N],r[N][N];
inline int at(int s,int i){ return (s>>i)&1; }
void Min(int &a,int b){ if(a>b) a=b; }
int S;
int addpre(int c,int p,int v)
{
	if(!A[c][v]) return -1;
	if(p==l[c]) return p;
	fr(i,1,p+1) if(r[c][i]==v) return i;
	fr(i,p+2,l[c]) if(r[c][i]==v) return p;
	return -1;
}
int addsuf(int c,int p,int v)
{
	if(!A[c][v]) return -1;
	if(p==l[c]) return p;
	if(a[c][p+1]==v) return p+1;
	fr(i,p+2,l[c]) if(a[c][i]==v) return -1;
	fr(i,1,p) if(a[c][i]==v) return p;
	return -1;
}
int solve(int s,int p1,int l1,int p2,int l2)
{
	if(s==S||(p2!=-1&&l2==l[p2]&&s+(1<<p2)==S)) return 0;
	if(vis[s][p1+1][l1][p2+1][l2]) return f[s][p1+1][l1][p2+1][l2];
	vis[s][p1+1][l1][p2+1][l2]=1; int &ans=(f[s][p1+1][l1][p2+1][l2]=inf);
	if(p1!=-1&&l1==l[p1])
	{
		fr(i,0,n-1) if(!at(s,i)&&i!=p1&&i!=p2)
		{
			int p=0;
			fr(j,1,l[p1]) if((p=addpre(i,p,r[p1][j]))==-1) break;
			if(p!=-1) Min(ans,solve(s+(1<<p1),i,p,p2,l2));
		}
		Min(ans,solve(s+(1<<p1),-1,0,p2,l2));
		return ans;
	}
	fr(i,0,n-1) if(!at(s,i)&&i!=p1&&i!=p2)
	{	
		if(p2!=-1)
		{
			int p=l2;
			fr(j,1,l[i]) if((p=addsuf(p2,p,a[i][j]))==-1) break;
			if(p!=l[p2]) continue;
		}
		Min(ans,solve(s+(p2==-1?0:1<<p2),p1,l1,i,0));
	}
	fr(i,1,9)
	{
		int L1,L2;
		if(p1==-1) L1=0;
		else L1=addpre(p1,l1,i);
		if(p2==-1) L2=0;
		else L2=addsuf(p2,l2,i);
		if(L1==-1||L2==-1) continue;
		if(L1<=l1&&L2<=l2) continue;
		Min(ans,solve(s,p1,L1,p2,L2)+1);
	}
	return ans;
}
int main()
{
	n=read(); S=(1<<n)-1;
	fr(i,0,n-1){ do A[i][a[i][++l[i]]=read()]=1; while(a[i][l[i]]); l[i]--; }
	fr(i,0,n-1) fr(j,1,l[i]) r[i][j]=a[i][l[i]-j+1];
	int ans=solve(0,-1,0,-1,0);
	fr(i,0,n-1) ans=std::min(ans,solve(0,i,0,-1,0));
	printf("%d\n",ans>=inf?-1:ans);
	return 0;
}
