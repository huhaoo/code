#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int n=100000,MX=1000000000;
int id[n+10],p[n+10],t[n+10]; int m,mx;
void init()
{
	m=1;
	fr(i,1,10000)
	{
		fr(j,1,i)
		{
			m++; id[m]=0; p[m]=i+1; t[m]=j;
			if(m==n) return ;
		}
		fr(j,1,i+1)
		{
			m++; id[m]=1; p[m]=i+1; t[m]=j;
			if(m==n) return ;
		}
	}
}
int main()
{
    freopen("dispatch.in","r",stdin); freopen("dispatch.out","w",stdout);
    if(read()==1000)
    {
        printf("1000\n");
        fr(i,1,1000) printf("%d %d\n",i,i);
        printf("999\n");
        fr(i,2,1000) printf("%d %d %d\n",(i%2==0?0:1),i,1);
    }
	else
	{
		mx=read(); if(mx>n-1) mx=n-1; init(); printf("%d\n1 1\n",n);
		int st=n-mx;
		fr(i,2,n)
			if(id[i]) printf("%d %d\n",p[i],i<=st?t[i]:MX-i);
			else printf("%d %d\n",i<=st?t[i]:MX-i,p[i]);
		printf("%d\n",mx);
		fr(i,st+1,n) printf("%d %d %d\n",id[i],MX-i,t[i]);
	}
	return 0;
}