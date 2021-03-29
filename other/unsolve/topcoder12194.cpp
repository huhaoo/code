/***************************************************************
	File name: topcoder12194.cpp
	Author: huhao
	Create time: Wed 15 Jan 2020 08:28:05 PM CST
***************************************************************/
#include<stdio.h>
#include<vector>
#include<string>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const int N=110,mod=1000000007;
int m,d,n,a[N][N],vis[N];
i64 f[N],g[N],F[N];
i64 ans,Ans;
/*
 * 显然如果有a-b-c-d-...-a，那么它们必须相互有边
 * 于是一个联通块可以变为若干个团连成的链（不能是树，团大小<=d，大小不为1的团连出去的边不能是同一个点连出的，否则答案为0）
 * 可以分联通块DP，最后用这些DP值算即可
 * 第二行对应的似乎不太好写，咕咕咕
 */
int solve()
{
	return ans;
}
class DistanceGraph
{
public:
	int countArrangements(int N,int D,std::vector<std::string> A)
	{
		m=N; d=D; n=A.size();
		fr(i,0,n-1) fr(j,0,n-1) a[i+1][j+1]=(A[i][j]=='Y');
		return solve();
	}
};
int main()
{
	return 0;
}
