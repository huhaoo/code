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
const int N=1010;
int n,a[N][N],b[N][N];
std::pair<int,int> transform(int a[N][N],int u,int v,int op)
{
	int x=0,y=0;
	fr(i,1,n) if(a[i][u]&&a[i][v]) (x?y:x)=i;
	a[u][v]=a[v][u]=0; a[x][y]=a[y][x]=1;
	return op==0?std::pair<int,int>{u,v}:std::pair<int,int>{x,y};
}
std::vector<std::pair<int,int> > solve(int a[N][N],int op)
{
	std::vector<std::pair<int,int> > ans;
	while(1)
	{
		int i=2;
		while(i<=n&&a[1][i]) i++;
		if(i>n) break;
		int j=i;
		while(!a[1][j]) j++;
		ans.push_back(transform(a,i-1,j,op));
	}
	return ans;
}
int main()
{
	n=read();
	fr(i,1,n){ int j=i%n+1; a[i][j]=a[j][i]=b[i][j]=b[j][i]=1; }
	fr(i,1,n-3){ int x=read(),y=read(); a[x][y]=a[y][x]=1; }
	fr(i,1,n-3){ int x=read(),y=read(); b[x][y]=b[y][x]=1; }
	auto A=solve(a,0),B=solve(b,1); while(!B.empty()){ A.push_back(B.back()); B.pop_back(); }
	printf("%d\n",A.size());
	assert(A.size()<=n+n);
	for(auto i:A) printf("%d %d\n",i.first,i.second);
	return 0;
}