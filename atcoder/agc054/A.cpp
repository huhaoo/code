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
const int N=100010;
int n;
char s[N];
int main()
{
	n=read();
	scanf("%s",s+1);
	if(s[1]!=s[n]){ printf("1\n"); return 0; }
	fr(i,1,n-1) if(s[i]!=s[1]&&s[i+1]!=s[1]){ printf("2\n"); return 0; }
	printf("-1\n");
	return 0;
}