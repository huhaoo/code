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
const int N=531441+10,L=12;
int m,n;
char s[N];
int f[N][L+2][3],g[N];
int p[N];
int query(int x,int y,int z,int v)
{
	assert(v%p[z]==0);
	if(y<z) return x<<2|2;
	if(v%p[z+1]==0) return query(x,y,z+1,v);
	if(x==n+1) return v<<2;
	if(y==z) return f[x][z][v/p[z]];
	int r=f[x][z][v/p[z]%3];
	v=v/p[z+1]*p[z+1];
	if(r&1) fr(i,z+1,y){ int k=v/p[i]%3; k=k==1?1:k==2?-1:0; v+=k*p[i]; }
	if(r&2) v=(v+p[z+1])%p[y+1];
	else return ((v+(r>>2))<<2)|(r&1);
	return query(r>>2,y,0,v)^(r&1);
}
int ans[N];
int main()
{
	m=read(); scanf("%s",s+1); n=strlen(s+1);
	p[0]=1; fr(i,1,m) p[i]=p[i-1]*3;
	fd(i,n,1) fr(j,0,m-1) fr(k,1,2) f[i][j][k]=query(i+1,j,0,p[j]*(s[i]=='R'?k:3-k)+(s[i]=='R'?1:0))^(s[i]=='R'?0:1);
//	fr(i,1,n) fr(j,0,m-1) printf("%d %d\n",f[i][j][1],f[i][j][2]);
	fd(i,n,1)
	{
		if(s[i]=='R')
		{
			int r=query(i+1,m-1,0,1);
			g[i]=(r&2?g[r>>2]:r>>2);
		}
		else g[i]=g[i+1];
	}
	fr(i,0,p[m]-1)
	{
		int r=query(1,m-1,0,i);
		ans[i]=(r&2?g[r>>2]:r>>2);
	}
	fr(i,0,p[m]-1) printf("%d%c",ans[i],i==end_i?'\n':' ');
	return 0;
}