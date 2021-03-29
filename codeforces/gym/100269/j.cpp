/***************************************************************
	File name: j.cpp
	Author: huhao
	Create time: Sun 25 Oct 2020 04:42:43 PM CST
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
#include<assert.h>
#include<vector>
#define i64 long long
const int N=100010,mod=1000000000,M=15;
int n,m;
int a[N];
int s[M];
int p[N];
char c[N];
struct num
{
	int a[M]; int op;
	void init(){ op=0; memset(a,0,sizeof(a)); }
	num(int A){ init(); a[0]=A; }
	num(std::vector<int> A){ init(); op=1; fr(i,0,A.size()-1) a[i]=A[i]; }
	int &operator[](int p){ return a[p]; }
};
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
num operator+(num a,num b)
{
	fr(i,0,10) Add(a[i],b[i]);
	a.op|=b.op;
	return a;
}
num operator-(num a,num b)
{
	fr(i,0,10) Add(a[i],mod-b[i]);
	a.op|=b.op;
	return a;
}
num operator*(num a,num b)
{
	static i64 c[M];
	fr(i,0,10) c[i]=0;
	fr(i,0,10) fr(j,0,10-i) c[i+j]+=(i64)a[i]*b[j];
	fr(i,0,10) a[i]=c[i]%mod;
	a.op|=b.op;
	return a;
}
int ps(num a)
{
	if(!a.op) return a[0];
	int S=0;
	fr(i,0,10) Add(S,(i64)s[i]*a[i]%mod);
	return S;
}
num solve(int,int);
void Exit(int t){ printf("- %d\n",t); fflush(stdout); assert(0); }
num solve(num a,int l,int r)
{
//	printf(". %d %d\n",l,r);
	if(l>r) return a;
	if(c[l]=='+') return a+solve(l+1,r);
	if(c[l]=='-') return a-solve(l+1,r);
	if(c[l]=='*') return a*solve(l+1,r);
	Exit(1);
}
num solve(std::vector<int> a,int l,int r){ return solve(num(a),l,r); }
num solve(int l,int r)
{
//	printf("/ %d %d\n",l,r);
	if(l>r) Exit(2);
	if(c[l]=='(') return solve(solve(l+1,p[l]-1),p[l]+1,r); // (...)...
	if(c[l]=='+') return ps(solve(l+2,r));                  // +/...
	if(c[l]=='X') return solve({0,1},l+1,r);                // X...
	if(c[l]=='N') return solve(n,l+1,r);                    // N...
	if(c[l]>='0'&&c[l]<='9')                                // x...
	{
		int L=0;
		while(l<=r&&c[l]>='0'&&c[l]<='9'){ L=((i64)L*10+c[l]-48)%mod; l++; }
		return solve(L,l,r);
	}
	if(c[l]=='-') return num(0)-solve(l+1,r);                // -...
	if(c[l]=='*')                                           // *:...
	{
		num ans=solve(l+2,r);
		return ans*ans;
	}
	Exit(3);
}
int main()
{
	freopen("j.in","r",stdin); freopen("j.out","w",stdout);
	n=read();
	fr(i,1,n)
	{
		int _a=1;
		a[i]=read();
		fr(j,0,10){ Add(s[j],_a); _a=(i64)_a*a[i]%mod; }
	}
	scanf("%s",c+1); m=strlen(c+1);
	static int _s[N],_t;
	fr(i,1,m)
	{
		if(c[i]=='(') _s[++_t]=i;
		else if(c[i]==')'){ int u=_s[_t--]; p[i]=u; p[u]=i; }
	}
	printf("%d\n",solve(1,m)[0]);
	return 0;
}
