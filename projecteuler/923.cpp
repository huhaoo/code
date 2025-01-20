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
const int mod=1000000007,S=1000;
// std::map<std::array<int,3>, int> f;
int f[10][1000][S*2]; bool F[10][1000][S*2];
int val[100][100][100]; int t[100][100][100];
std::vector<std::array<int,3> > V;
int C[100][100];
int dfs(int m, int o, int i,int s)
{
	if(m==0) return s>0;
	if(i==V.size()) return 0;
	if(m>=10||i>=1000||s>=S||s<-S){ printf("%d %d %d\n",m,i,s); fflush(stdout); exit(0); }
	if(F[m][i][s+S]) return f[m][i][s+S];
	int ans=0; F[m][i][s+S]=1; int I=i;
	while(i<V.size())
	{
		i64 p=1;
		fr(j,1,m)
		{
			p=p*V[i][2]%mod;
			int t=dfs(m-j,o^(j&1),i+1,s+V[i][1]*j+V[i][0]*((j+o)/2));
			ans=(ans+p*t%mod*C[m][j])%mod;
		}
		i++;
	}
	return f[m][I][s+S]=ans;
}
std::vector<std::pair<int,int> > v;
int main()
{
	int n=64,m=8;
	// int n=9,m=3;
	// int n=4,m=2;
	fr(a,1,n) fr(b,1,n) fr(k,1,n) if(a+b+k<=n)
	{
		int mx=-1;
		fr(i,1,k)
		{
			int l=std::min(i*a,(k-i+1)*b);
			if(l>mx){ mx=l; val[a][b][k]=i*a-(k-i+1)*b; t[a][b][k]=0; }
			else if(l==mx)
			{
				int v1=i*a-(k-i+1)*b,v2=val[a][b][k];
				if(v1>v2) std::swap(v1,v2);
				val[a][b][k]=v1; t[a][b][k]=v2-v1;
			}
		}
		v.push_back({t[a][b][k],val[a][b][k]});
	}
	std::sort(v.begin(),v.end(),std::greater<std::pair<int,int> >());
	for(auto i:v)
		if(!V.empty()&&i.first==V.back()[0]&&i.second==V.back()[1]) V.back()[2]++;
		else V.push_back({i.first,i.second,1});
	// for(auto i:v) printf("%d %d\n",i.first,i.second);
	// for(auto i:V) printf("%d %d %d\n",i[0],i[1],i[2]);
	// printf("%d %d\n",V.size(),v.size()); fflush(stdout);
	fr(i,0,m)
	{
		C[i][0]=C[i][i]=1;
		fr(j,1,i-1) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	printf("%d\n",dfs(m,1,0,0));
	return 0;
}