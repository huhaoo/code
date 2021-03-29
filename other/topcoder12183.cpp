/***************************************************************
	File name: topcoder12183.cpp
	Author: huhao
	Create time: Wed 15 Jan 2020 09:02:20 PM CST
***************************************************************/
#include<stdio.h>
#include<vector>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const int N=210,mod=1234567891;
int n,a[N],s;
i64 f[N][N];
int min(int a,int b){ return a<b?a:b; }
i64 I[N]={1,1,(mod+1)/2,(1+mod*5ll)/6,(1+mod*5ll)/24};
i64 C(i64 a,i64 b)
{
	i64 ans=1;
	fr(i,0,b-1) ans=ans*(a-i)%mod;
	return ans*I[b]%mod;
}
i64 A(i64 a,i64 b)
{
	i64 ans=1;
	fr(i,0,b-1) ans=ans*(a-i)%mod;
	return ans;
}
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod;}
i64 solve()
{
	f[0][0]=1;
	fr(i,1,n)
	{
		fr(j,0,s) fr(k,0,std::min(s-j,4)) fr(l,0,a[i]) Add(f[i][j+k+l],f[i-1][j]*A(s-j,k)%mod*C(4,k)%mod*A((i-1)*4-j,l)%mod*C(a[i],l)%mod);
		s+=a[i];
//		fr(j,0,s) printf("%lld%c",f[i][j],j==s?'\n':' ');
	}
	return f[n][s];
}
class TheAnimalProgrammingCompetitions
{
public:
	int find(std::vector<int> A){ n=A.size(); fr(i,1,n) a[i]=A[i-1]; return solve(); }
};
/*
int main()
{
	TheAnimalProgrammingCompetitions ans;
	printf("%d\n",ans.find({0,1,2,3,4}));
	return 0;
}
*/
