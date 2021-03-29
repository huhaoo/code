/****************************************************************
    File name: 4424.cpp
    Author: huhao
    Email: 826538400@qq.com
    Create time: 12/15/2018, 4:25:30 PM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
    long long r=0,t=1,c=getchar();
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
#define N 5010
#define mod 1000000007
long long n,m,q,a[N][N],r[N],ans,p[N],w[N];
char s[N];
long long cmp(long long x,long long y)
{
    fd(i,n,1)if(a[x][i]!=a[y][i])return a[x][i]>a[y][i];
    return 1;
}
int main()
{
    n=read();
    m=read();
    q=read();
    fr(i,1,n)
    {
        scanf("%s",s+1);
        fr(j,1,m)
            a[j][i]=s[j]-48;
    }
    fr(i,1,m+1)r[i]=i;
	w[0]=1;
	fr(i,1,n)w[0]=(w[0]<<1)%mod;
	fr(i,1,m)fd(j,n,1)w[i]=(w[i]<<1|a[i][j])%mod;
    sort(r+1,r+m+1,cmp);
    while(q--)
    {
        scanf("%s",s+1);
		s[m+1]='0';
		int k=0;
		fr(i,1,m)
			if(s[r[i]]==48)k=1;
			else if(k==1)
			{
				printf("0\n");
				k=2;
				break;
			}
		if(k==2)continue;
		fr(i,1,m+1)
			if(s[r[i]]==48)
			{
				printf("%lld\n",(w[r[i-1]]-w[r[i]]+mod)%mod);
				break;
			}
    }
    return 0;
}