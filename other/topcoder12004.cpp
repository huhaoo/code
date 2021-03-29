/***************************************************************
	File name: topcoder12004.cpp
	Author: huhao
	Create time: Tue 14 Jan 2020 09:49:36 PM CST
***************************************************************/
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
#include<vector>
#include<stdio.h>
const int N=60,L=20;
/*
 * 考虑如果某一位有0，那么必须两个集合都有
 * 容斥哪一位只有一个集合有0，并查集维护
 */
class SetAndSet
{
public:
	int n,a1[N],a2[N],f[N],vis[N],a[N];
	int getf(int u){ return u==f[u]?u:f[u]=getf(f[u]); }
	i64 dfs(int x,int S=0)
	{
		if(x==L)
		{
			int k=0;
			fr(i,1,n) vis[i]=0;
			fr(i,1,n) if(!vis[getf(i)]){ k++; vis[getf(i)]=1;}
//			printf("%d %lld\n",S,(1ll<<k)-2);
			return (1ll<<k)-2;
		}
		i64 ans=dfs(x+1,S);
		int flag=0;
		fr(i,1,n) if(!((a[i]>>x)&1)) flag=1;
		if(!flag) return ans;
		int F[N];
		fr(i,1,n) F[i]=f[i];
		int lst=0;
		fr(i,1,n) if(!((a[i]>>x)&1))
		{
			if(lst) f[getf(i)]=getf(lst);
			lst=i;
		}
		flag=0;
		fr(i,2,n) if(getf(i)!=getf(1)) flag=1;
		if(flag) ans-=dfs(x+1,S|(1<<x));
		fr(i,1,n) f[i]=F[i];
		return ans;
	}
	i64 countandset(std::vector<int> A)
	{
		n=A.size(); if(n==1) return 0;
		fr(i,1,n){ f[i]=i; a[i]=A[i-1]; }
		return dfs(0);
	}
}call;
/*
int main()
{
	printf("%lld\n",call.countandset({13,10,4,15,4,8,4,2,4,14,0}));
	return 0;
}
*/
