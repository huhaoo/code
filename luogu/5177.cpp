/****************************************************************
    File name: 5177.cpp
    Author: huhao
    Email: 826538400@qq.com
    Create time: 1/4/2019, 7:28:20 PM
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
#define mod 1000000007
long long n,ans;
long long pow(long long a,long long b,long long m)
{
    long long r=1;
    a%=m;
    while(b)
    {
        if(b&1)
            r=r*a%m;
        a=a*a%m;
        b>>=1;
    }
    return r;
}
long long f[70],s[30],t;
void print(long long v)
{
    if(!v)
        return;
    t=0;
    while(v)
    {
        s[++t]=v%10;
        v/=10;
    }
    while(t)
    {
        putchar(s[t]+48);
        t--;
    }
    putchar(10);
}
long long p2=pow(2,mod-2,mod);
int main()
{
    fr(i,1,60)
        f[i]=(f[i-1]-(1ll<<i)%mod*(((1ll<<(i+1))-(1ll<<i))%mod)%mod+mod)%mod;
    fr(T,1,read())
    {
        scanf("%lld",&n);
        ans=(n%mod*((n+1)%mod)%mod*p2%mod-1+mod)%mod;
        if(n!=1)
        {
            int i=int(log2(n));
            if(i)
                ans=(ans+f[i-1])%mod;
            ans=(ans-(1ll<<i)%mod*((n-(1ll<<i)+1)%mod)%mod+mod)%mod;
        }
        print(ans*2%mod);
    }
    return 0;
}