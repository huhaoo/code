/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Sun 03 Jan 2021 09:11:58 AM CST
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
const int N=6010;
int a[N][N],b[N][N],c[N][N];
int t[N];
int A[N][N],B[N][N],C[N][N];
int n,m;
i64 ans;
void Add(int u,int v){ for(;u;u&=u-1) t[u]+=v; }
int query(int u){ int ans=0; for(;u<N;u+=u&(-u)) ans+=t[u]; return ans; }
void dfs(int x,int y,int a[N][N],int b[N][N],int dx,int dy)
{
	if(a[x][y]!=-1) return ;
	if(b[x][y])
	{
		dfs(x+dx,y+dy,a,b,dx,dy);
		a[x][y]=a[x+dx][y+dy]+1;
	}
	else a[x][y]=0;
}
void Read(char *s)
{
	s[0]=getchar();
	if(s[0]==EOF||s[0]=='\n'){ s[0]=0; return; }
	Read(s+1);
}
#include<vector>
int solve(int n,int *a,int *b)
{
	std::vector<int> Q[N]; memset(t,0,sizeof(t));
	fr(i,1,n) Q[i].clear();
	fr(i,1,n) Q[std::max(1,b[i])].push_back(i);
	int ans=0;
	fr(i,1,n)
	{
		for(auto j:Q[i]) Add(j,1);
		ans+=query(i+1)-query(a[i]+1);
	}
	return ans;
}
int main()
{
	n=read(); m=read();
	fr(i,2,n<<1)
	{
		static int st=1; if(i%4==0) st++;
		static char s[N<<2]; memset(s,0,sizeof(s)); Read(s);
		if(i&1)
		{
			if(i%4==3) for(int j=1,k=st;s[j];j+=4,k++)
			{
				if(s[j]=='\\') b[i>>1][k]=1;
				if(s[j+2]=='/') c[i>>1][k+1]=1;
			}
			else for(int j=1,k=st;s[j];j+=4,k++)
			{
				if(s[j]=='/') c[i>>1][k]=1;
				if(s[j+2]=='\\') b[i>>1][k]=1;
			}
		}
		else
		{
			for(int j=3,k=st;s[j];j+=4,k++)
				if(s[j]=='-') a[i>>1][k]=1;
		}
	}
	m=(m+n)/2+5;
	fr(i,1,n) fr(j,1,m) A[i][j]=B[i][j]=C[i][j]=-1;
	fr(i,1,n) fr(j,1,m){ dfs(i,j,A,a,0,1); dfs(i,j,B,b,1,1); dfs(i,j,C,c,1,0); }
//	fr(i,1,n) fr(j,1,m) printf("%d%d%d%c",a[i][j],b[i][j],c[i][j],j==m?'\n':' ');
	fr(i,1,n)
	{
		static int A[N],B[N];
		fr(j,1,m)
		{
			A[j]=j+std::min(::A[i][j],::B[i][j]);
			B[j]=j-::C[i][j];
		}
		ans+=solve(m,A,B);
	}
	fr(i,1,m)
	{
		static int A[N],B[N];
		fr(j,1,n)
		{
			A[j]=j+std::min(::B[j][i],::C[j][i]);
			B[j]=j-::A[j][i];
		}
		ans+=solve(n,A,B);
	}
	printf("%lld\n",ans);
	return 0;
}
