/***************************************************************
	File name: topcoder12083.cpp
	Author: huhao
	Create time: Wed 15 Jan 2020 07:08:01 PM CST
***************************************************************/
#include<stdio.h>
#include<string>
#include<vector>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
const int C=11,mod=10007,N=110;
int power(int a,int b,int p)
{
	int r=1; a%=p;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
int inv(int a){ return power(a,mod-2,mod); }
/*
 * 考虑l互不相同的情况，显然可以直接算为i的概率
 * 否则gcd相同的话可以按模gcd相同的组分开考虑，然而gcd不一定相同
 * 然后我们可以把它们按质因数情况拓展为12*88200,12*11,12*13,12*17,12*19,12*23,12*29,12*31,12*37,12*41,12*43,12*47
 * 这些gcd相互为12
 */
class CowsMooing
{
public:
	std::vector<int> ans;
	int n,p[C+1]={1058400,12*11,12*13,12*17,12*19,12*23,12*29,12*31,12*37,12*41,12*43,12*47};
	int *s[C+1],f[N],F[N],cnt[N],Ans;
	std::vector<int> getDistribution(std::vector<std::string> a)
	{
		n=a.size();
		fr(i,0,C) s[i]=new int[p[i]];
		fr(i,0,n-1)
		{
			int l=a[i].length();
			fr(j,0,C) if(p[j]%l==0)
			{
				fr(k,0,p[j]-1) s[j][k]+=(a[i][k%l]=='M');
//				printf("%d\n",j);
				break;
			}
//			printf(" %d\n",l);
		}
		ans.resize(n+1);
		fr(q,0,11)
		{
			fr(i,0,n) f[i]=0;
			f[0]=1;
			fr(i,0,C)
			{
				int I=inv(p[i]/12);
				fr(i,0,n){ F[i]=f[i]; f[i]=0; cnt[i]=0; }
				fr(j,0,p[i]/12-1) cnt[s[i][j*12+q]]++;
				fr(j,0,n) cnt[j]=cnt[j]%mod*I%mod;
				fr(j,0,n) fr(k,j,n) f[k]=(f[k]+F[k-j]*cnt[j])%mod;
//				fr(j,0,n) printf("%d%c",cnt[j],i==C&&j==n?'\n':' ');
			}
			int I=inv(12);
			fr(i,0,n) ans[i]=(ans[i]+f[i]*I)%mod;
		}
		Ans=1;
		fr(i,1,50) Ans=Ans*i%mod;
		fr(i,0,n) ans[i]=ans[i]*Ans%mod;
		return ans;
	}
}run;
/*
std::vector<std::string> Query=
{"MM-M---M-MM--",
 "-MM-MMM----M-M-",
 "MM-",
 "M--M-M--"};
int main()
{
	std::vector<int> ans=run.getDistribution(Query);
	for(auto i:ans) printf("%d ",i);
	putchar('\n');
	return 0;
}
*/
