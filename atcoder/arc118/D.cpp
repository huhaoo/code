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
const int N=100010;
int n,a,b;
int vis[N];
i64 p[N],q,r[N],s;
int main()
{
	n=read(); a=read(); b=read();
	if(n==2)
	{
		printf("Yes\n1 1\n");
		return 0;
	}
	p[q=0]=1;
	while(!vis[p[q]])
	{
		vis[p[q]]=1; p[q+1]=p[q]*a%n; q++;
	}
	if(q%2==1)
	{
		std::swap(a,b); memset(vis,0,sizeof(vis));
		p[q=0]=1;
		while(!vis[p[q]])
		{
			vis[p[q]]=1; p[q+1]=p[q]*a%n; q++;
		}
	}
	q--; r[0]=1; r[s=1]=b;
	while(!vis[r[s]])
	{
		r[s+1]=r[s]*b%n; s++;
	}
	s--; 
	if((i64)(s+1)*(q+1)!=n-1){ printf("No\n"); return 0; }
	printf("Yes\n");
//	printf("%d %d\n",q,s);
//	fr(i,0,q) printf("%d%c",p[i],i==q?'\n':' ');
//	fr(i,0,s) printf("%d%c",r[i],i==s?'\n':' ');
	fr(j,0,q)
	{
		fr(i,0,s) printf("%d ",int(r[i]*p[j]%n));
		j++;
		fd(i,s,0) printf("%d ",int(r[i]*p[j]%n));
	}
	printf("1\n");
	return 0;
}