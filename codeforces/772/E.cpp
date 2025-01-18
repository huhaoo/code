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
const int N=2010;
int n;
int f[N],s[N][2],S[N];
int r,R;
int c[N];
int w[N],m;
void dfs1(int u){ w[u]=1; if(c[u]) return ; fr(i,0,1){ dfs1(s[u][i]); w[u]+=w[s[u][i]]; } }
void dfs2(int u){ if(w[u]+w[u]>w[R]) m=u; if(c[u]) return ; fr(i,0,1) dfs2(s[u][i]); }
std::string query(int a,int b,int c)
{
	printf("%d %d %d\n",a,b,c); fflush(stdout);
	std::string s; std::cin>>s; return s=="X"?"ab":s=="Y"?"bc":"ac";
}
int main()
{
	n=read();
	fr(i,1,n){ S[i]=i; c[i]=1; }
	fr(i,2,n) S[i+n-1]=i; 
	f[1]=f[2]=r=n+1; s[n+1][0]=1; s[n+1][1]=2;
	fr(i,3,n)
	{
		fr(j,n+1,n+i-2) c[j]=0;
		R=r;
		while(!c[R])
		{
			dfs1(R); dfs2(R);
			auto q=query(i,S[s[m][0]],S[s[m][1]]);
			if(q=="bc") c[m]=1;
			else if(q=="ab") R=s[m][0];
			else R=s[m][1];
		}
		f[n+i-1]=f[R]; s[f[R]][s[f[R]][1]==R]=n+i-1; f[R]=f[i]=n+i-1; s[n+i-1][0]=R; s[n+i-1][1]=i;
		if(R==r) r=n+i-1;
	}
	printf("-1\n");
	fr(i,1,n+n-1) printf("%d%c",f[i]?f[i]:-1,i==end_i?'\n':' ');
	fflush(stdout);
	return 0;
}