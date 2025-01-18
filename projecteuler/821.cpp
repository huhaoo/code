#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=60;
int vis[N][N];
i64 n;
i64 q23(i64 n){ return n/2+n/3-n/6; }
i64 n23(i64 l,i64 r){ return r-l-q23(r)+q23(l); }
i64 ans;
i64 Ans,k; int I;
std::array<i64,3> c[N*N]; int m;
void dfs(i64 n,i64 x,i64 y)
{
	if(n>::n) return ;
	c[++m]={n,x,y};
	dfs(n*2,x+1,y); if(!x) dfs(n*3,x,y+1);
}
void solve(int t,int x,int y)
{
	if(t>=Ans) return ;
	if(x>y)
	{
		if(y>20)
		{
			printf("%d\n",y);
			int l2=0,l3=0; i64 p2=1,p3=1;
			while(p2<=c[y][0]){ p2*=2; l2++; }
			while(p3<=c[y][0]){ p3*=3; l3++; }
		//	printf("%d  %lld %lld   %lld  %lld %lld %d\n",i,n/c[i+1][0],n/c[i][0],c[i][0],C,Ans,k); fflush(stdout);
			fr(i,0,l2) fr(j,0,l3) printf("%d%c",vis[i][j],j==end_j?'\n':' ');
			exit(0);
		}
		Ans=t; return ;
	}
	int X=c[x][1],Y=c[x][2]; solve(t+(!vis[X][Y]),x+1,y);
	if(!vis[X][Y]&&!vis[X+1][Y]&&!vis[X][Y+1])
	{
		vis[X][Y]=vis[X+1][Y]=vis[X][Y+1]=++I;
		solve(t,x+1,y);
		vis[X][Y]=vis[X+1][Y]=vis[X][Y+1]=0; I--;
	}
}
int main()
{
	n=10000000000000000ll; dfs(1,0,0);
	std::sort(c+1,c+m+1);
	c[m+1][0]=n+1;
	i64 p=4;
	fr(i,1,m)
	{
		if(c[i][1]%3==2&&!c[i][2]) k++;
		if(c[i][2]%3==2&&!c[i][1]) k++;
		i64 C=n23(n/c[i+1][0],n/c[i][0]);
		Ans=k;
		if(p*8<=c[i][0]) p*=8;
		if(c[i][0]>=p&&c[i][0]<p/2*3) Ans--;
		if(i<100) solve(0,1,i);
		ans+=C*(i-Ans);
	}
	printf("%lld\n",ans);
//	fr(i,1,m) printf("%lld %lld %lld\n",c[i][0],c[i][1],c[i][2]);
	return 0;
}