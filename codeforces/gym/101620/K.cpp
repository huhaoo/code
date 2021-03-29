/***************************************************************
	File name: LK.cpp
	Author: huhao
	Create time: Thu 19 Nov 2020 02:38:56 PM CST
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
const int N=510;
int n,a[N],ans,c[N];
int p[N]={1,10,100,1000,10000,100000,1000000,10000000};
int v[N];
void Min(int &a,int b){ if(a>b) a=b; }
short f[N][N][N]; bool vis[N][N][N];
int solve(int u,int v,int w,int x,int y,int z)
{
	if(vis[x][y][z]) return f[x][y][z];
	vis[x][y][z]=1; short &ans=f[x][y][z];
	fr(i,0,std::min(x,7)) fr(j,0,std::min(y,7)) fr(k,0,std::min(z,7))
		if((i||j||k)&&(i*u+j*v+k*w)%7==0) ans=std::max((int)ans,solve(u,v,w,x-i,y-j,z-k)+1);
	return ans;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		int A=read(),mx=A;
		fr(j,1,6) mx=std::max(mx,A/p[j]+A%p[j]*p[7-j]);
		static int q[N];
		fr(j,0,6) if(mx==A/p[j]+A%p[j]*p[7-j]) q[j]=1; else q[j]=0;
		if(q[0]&&q[1]){ n--; i--; }
		else while(!q[a[i]]) a[i]++;
	}
	if(!n){ printf("0\n"); return 0; }
//	fr(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
	fd(i,n,1) c[a[i]=(a[i]-a[i-1]+7)%7]++;
	ans=n;
//	printf("%d\n",ans);
//	fr(i,0,6) printf("%d%c",c[i],i==6?'\n':' ');
	ans-=c[0]; c[0]=0;
	fr(i,1,3){ int k=std::min(c[i],c[7-i]); ans-=k; c[i]-=k; c[7-i]-=k; }
	int u=0,v=0,w=0;
	fr(i,1,6) if(c[i])
	{
		if(u&&v) w=i;
		else if(u) v=i;
		else u=i;
	}
	ans-=solve(u,v,w,c[u],c[v],c[w]);
	printf("%d\n",ans);
	return 0;
}
