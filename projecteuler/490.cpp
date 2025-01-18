#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const int N=50,L=600,D=3-1,mod=1000000000; const i64 MOD=(i64)mod*mod;
int Id;
std::map<std::vector<int>,int> id;
std::vector<int> e[N];
i64 n; int m,l;
int _id[N][N][N];
int a[L][L],b[L][L],c[L][L];
int mulcnt;
void mul(int (*a)[L],int (*b)[L])
{
	mulcnt++;
	static i64 c[L][L];
	fr(i,1,l) fr(j,1,l) c[i][j]=0;
	fr(i,1,l) fr(k,1,l) if(a[i][k]) fr(j,1,l){ c[i][j]+=(i64)a[i][k]*b[k][j]; if(c[i][j]>MOD) c[i][j]-=MOD; }
	fr(i,1,l) fr(j,1,l) a[i][j]=c[i][j]%mod;
}
int dfs(std::vector<int> a)
{
	if(!id.count(a)) id[a]=++Id; else return id[a];
	int _id=id[a];
//	for(auto i:a) printf("%d ",i);; putchar(10);
	for(int i=0;i<a.size();i++)
	{
		auto b=a; for(auto &j:b) j--; b[i]=D;
		int flag=1; for(auto j:b) flag&=(j>=0); if(flag) e[dfs(b)].push_back(_id);
	}
	for(int i=0;i<a.size();i+=2)
	{
		auto b=a; for(auto &j:b) j--; b.insert(b.begin()+i+1,{D,D});
		int flag=1; for(auto j:b) flag&=(j>=0); if(flag) e[dfs(b)].push_back(_id);
	}
	for(int i=0;i+1<a.size();i+=2)
	{
		auto b=a; for(auto &j:b) j--; b.erase(b.begin()+i,b.begin()+i+2);
		int flag=1; for(auto j:b) flag&=(j>=0); if(flag) e[dfs(b)].push_back(_id);
	}
	return _id;
}
int id_[N],Id_[N],A[N][N];
void getID()
{
	static i64 f[N],F[N],g[N]; std::map<i64,int> M; const int mod=998244353;
	f[1]=1; g[1]=1;
	fr(_,1,100)
	{
		fr(i,1,Id){ F[i]=f[i]; f[i]=0; }
		fr(i,1,Id) for(auto j:e[i]) f[j]=(f[j]+F[i])%mod;
		m=0; M.clear(); fr(i,1,Id) g[i]=g[i]+f[i]*10;
		fr(i,1,Id){ if(g[i]&&!M[g[i]]) M[g[i]]=++m; g[i]=M[g[i]]; }
	}
	fr(i,1,Id){ id_[i]=g[i]; Id_[g[i]]=i; }
//	printf("%d  ",m); fr(i,1,Id) printf("%d%c",id_[i],i==Id?'\n':' ');
}
int main()
{
	dfs({D}); getID();
	fr(i,1,Id) for(auto j:e[i]) if(j==Id_[id_[j]]) A[id_[i]][id_[j]]++;
	fr(i,1,m) fr(j,i,m) fr(k,j,m) _id[i][j][k]=++l;
	fr(i,1,m) fr(j,i,m) fr(k,j,m) fr(I,1,m) fr(J,1,m) fr(K,1,m)
	{
		int ii=I,jj=J,kk=K;
		if(ii>jj) std::swap(ii,jj);
		if(jj>kk) std::swap(jj,kk);
		if(ii>jj) std::swap(ii,jj);
//		assert(ii<=jj&&jj<=kk);
		a[_id[i][j][k]][_id[ii][jj][kk]]+=A[i][I]*A[j][J]*A[k][K];
	}
	l++; a[l][1]=1; a[l][l]=1;
	fr(i,1,l) fr(j,1,l) b[i][j]=c[i][j]=a[i][j];
	mul(b,b); mul(c,b);
	scanf("%lld",&n);
	if(n==1){ printf("%d\n",1); return 0; }
	static i64 _n[60],_m; _n[_m=1]=n; while(_n[_m]>1){ _n[_m+1]=_n[_m]/2; _n[_m]%=2; _m++; }
	if(_n[_m-1]) fr(i,1,l) fr(j,1,l) b[i][j]=c[i][j];
	_m-=2;
	while(_m)
	{
		if(!_n[_m]){ mul(b,b); _m--; }
		else if(_m>1&&_n[_m-1]){ mul(b,b); mul(b,b); mul(b,c); _m-=2; }
		else{ mul(b,b); mul(b,a); _m--; }
	}
	printf("%d\n",b[l][1]);
	printf("%d %.6lf\n",mulcnt,clock()*1./CLOCKS_PER_SEC);
	return 0;
}