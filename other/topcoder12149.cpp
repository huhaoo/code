/***************************************************************
	File name: topcoder12149.cpp
	Author: huhao
	Create time: Wed 15 Jan 2020 09:51:31 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const int mod=1000000007,N=60;
int n,l,k;
i64 ans;
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
struct matrix
{
	i64 a[N][N];
	matrix(){ memset(a,0,sizeof(a)); }
	i64 *operator[](int p){ return a[p]; }
};
matrix operator*(matrix a,matrix b)
{
	matrix c;
	fr(i,1,k) fr(j,1,k) fr(l,1,k) c[i][j]=(a[i][l]*b[l][j]+c[i][j])%mod;
	return c;
}
matrix &operator*=(matrix &a,matrix b){ return a=a*b; }
i64 solve()
{
	k=l<k-1?l:k-1; n--;
	matrix a,b;
	fr(i,1,k) b[i][i]=1;
	fr(i,1,k){ a[i+1][i]=(1<<i)*((1<<(l-i))-1)%mod; fr(j,1,i) a[j][i]=(1<<(j-1)); }
	while(n)
	{
		if(n&1) b*=a;
		a*=a; n>>=1;
	}
	/*
	fr(i,2,n)
	{
		fr(j,1,k){ F[j]=f[j]; f[j]=0; }
		fr(j,1,k)
		{
			Add(f[j+1],(1<<j)*((1<<(l-j))-1)%mod*F[j]);
			fr(o,1,j) Add(f[o],(1<<(o-1))*F[j]);
		}
//		fr(j,1,k) printf("%lld%c",f[j],j==k?'\n':' ');
	}
	*/
	fr(i,1,k) Add(ans,b[i][1]);
	return ans*((1<<l)-1)%mod;
}
/*
 * 考虑某个时候线性基元素个数，DP+矩阵快速幂优化即可
 */
class YetAnotherNim
{
public:
	int solve(int n,int m,int k){ ::n=n; ::k=k; while((1<<l)<m+1) l++; return ::solve(); }
};
/*
int main()
{
	YetAnotherNim ans;
	printf("%d\n",ans.solve(100,31,10));
	return 0;
}
*/
