/**********************************************************
    File:4139.cpp
    Author:huhao
    Email:826538400@qq.com
    Created time:2018-4-5 08:51:18
**********************************************************/
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
#define M 10000000
int phi[M+10];
long long power(long long x,long long y,long long m)
{
    long long r=1;
    while(y)
    {
        if(y&1)r=r*x%m;
        x=x*x%m;
        y>>=1;
    }
    return r;
}
long long run(long long m)
{
    if(m==1)return 0;
    return power(2,run(phi[m])+phi[m],m);
}
int p[M],t;
int main()
{
    fr(i,2,M)
    {
        if(!phi[i])
        {
            phi[i]=i-1;
            p[++t]=i;
        }
        fr(j,1,t)
            if(i*p[j]>M)break;
            else
                if(i%p[j])
                    phi[i*p[j]]=phi[i]*(p[j]-1);
                else
                {
                    phi[i*p[j]]=phi[i]*p[j];
                    break;
                }
    }
    fr(i,1,read())
        printf("%lld\n",run(read()));
    return 0;
}
