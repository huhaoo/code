/**************************************************************
    File name: 3936.cpp
    Author: huhao
    Email: 826538400@qq.com
    Create time: 7/13/2018, 1:15:26 PM
**************************************************************/
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
#define N 110
#include<stdlib.h>
int n,m,c,p[N],a[N][N],lst,mx[4]={0,0,-1,1},my[4]={1,-1,0,0},ans[N][N],w;
double T=1,k=0.9999,eps=1e-25;
int calc(int i,int j)
{
    int sum=0;
    fr(k,0,3)
    {
        int x=i+mx[k],y=j+my[k];
        if(x<1||x>n||y<1||y>m)continue;
        sum+=a[i][j]!=a[x][y];
    }
    return sum;
}
int calc()
{
    int sum=0;
    fr(i,1,n)
        fr(j,1,m)
            sum+=calc(i,j);
    return sum/2;
}
int main()
{
    srand(19260817);
    n=read();
    m=read();
    c=read();
    fr(i,1,c)p[i]=read();
    c=1;
    fr(i,1,n)
        fr(j,1,m)
        {
            while(!p[c])c++;
            ans[i][j]=a[i][j]=c;
            p[c]--;
        }
    fr(_,1,1000)
    {
        w=lst=calc();
        while(T>eps)
        {
            int x=rand()%n+1,y=rand()%m+1,xx=rand()%n+1,yy=rand()%m+1;
            int d=0;
            d-=calc(x,y)+calc(xx,yy);
            swap(a[x][y],a[xx][yy]);
            d+=calc(x,y)+calc(xx,yy);
            int c=lst+d;
            if(exp(-d/T)*RAND_MAX>rand())
            {
                if(c<w)
                {
                    w=c;
                    fr(i,1,n)
                        fr(j,1,m)
                            ans[i][j]=a[i][j];
                }
                lst=c;
            }
            else
                swap(a[x][y],a[xx][yy]);
            T*=k;
        }
    }
    fr(i,1,n)
        fr(j,1,m)
            printf("%d%c",ans[i][j],j==m?'\n':' ');
    return 0;
}