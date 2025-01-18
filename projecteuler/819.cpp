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
#define f80 long double
const int N=1010;
int n;
f80 l[N],L[N];
f80 logC(int a,int b){ assert(a>=b&&b>=0); return L[a]-L[a-b]-L[b]; }
f80 A[N][N];
int main()
{
	n=read();
	fr(i,1,n) L[i]=(L[i-1]+(l[i]=logl((f80)i)));
	fr(i,1,n-1)
	{
		f80 p=logl((f80)i/n),q=logl((f80)(n-i)/n),s=0;
		fr(j,0,n) s+=(A[i][j]=expl(p*j+q*(n-j)+logC(n,j)));
		assert(fabsl(s-1)<1e-8);
//		fr(j,0,n) printf("%.10lf%c",(double)A[i][j],j==n?'\n':' '); printf("%.10lf\n",(double)s);
	}
//	fr(i,1,n-1) fr(j,1,n) printf("%.10lf%c",(double)A[i][j],j==n?'\n':' ');
	fr(i,1,n-1) fr(j,1,n-1) A[i][j]=((i==j)-A[i][j]);
	fr(i,1,n-1) A[i][n]=(f80)i/n;
	fr(i,1,n-1) std::swap(A[i][1],A[i][n-1]);
	fr(i,1,n-1)
	{
		int j=i; while(fabsl(A[j][i])<1e-4&&j<n) j++; assert(j<n);
		fr(k,i,n) std::swap(A[i][k],A[j][k]);
		f80 a=A[i][i];
		fr(k,i,n) A[i][k]/=a;
		fr(k,i+1,n-1)
		{
			a=A[k][i];
			fr(l,i,n) A[k][l]-=a*A[i][l];
		}
	}
	printf("%.6lf\n",(double)A[n-1][n]*n);
	return 0;
}