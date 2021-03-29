/****************************************************************
	File name: 3830.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/21/2018, 7:17:33 PM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
int n;
namespace run1
{
	double ans=0;
	int main()
	{
		fr(i,2,n)ans+=2./i;
		printf("%.6lf\n",ans);
		return 0;
	}
}
namespace run2
{
	#define N 210
	double f[N][N],ans;
	#undef N
	int main()
	{
		fr(i,0,n)f[i][0]=1;
		fr(i,2,n)fr(j,1,n)
			fr(k,1,i-1)f[i][j]+=(f[k][j-1]+f[i-k][j-1]-f[k][j-1]*f[i-k][j-1])/(i-1);
		fr(i,1,n)ans+=f[n][i];
		printf("%.6lf\n",ans);
		return 0;
	}
}
int main()
{
	int q=read();n=read();
	if(q==1)return run1::main();
	return run2::main();
}