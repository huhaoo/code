#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
int main()
{
    static int vis[100010];
    int n=read(),m=1;
    while(n--)
    {
        int x;
        x=6*m; if(x<=10000&&!vis[x]){ printf("%d ",x); vis[x]=1; continue; }
        x=10*m; if(x<=10000&&!vis[x]){ printf("%d ",x); vis[x]=1; continue; }
        x=15*m; if(x<=10000&&!vis[x]){ printf("%d ",x); vis[x]=1; continue; }
        m++; n++;
    }
	return 0;
}