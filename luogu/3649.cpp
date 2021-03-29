/**************************************************************
	File name: 3649.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/12/2019, 4:52:28 PM
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
#define N 300010
long long n,t[N][30],w[N],l[N],f[N],c,ans;
char s[N];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	c=2;
	f[1]=f[2]=1;
	l[1]=-1;
	long long j=2;
	s[0]='#';
	fr(i,1,n)
	{
		while(s[i-l[j]-1]!=s[i])
			j=f[j];
		if(!t[j][s[i]-'a'])
		{
			c++;
			long long k=j;
			l[c]=l[k]+2;
			k=f[k];
			while(s[i-l[k]-1]!=s[i])
				k=f[k];
			f[c]=t[k][s[i]-'a'];
			if(!f[c])
				f[c]=2;
			t[j][s[i]-'a']=c;
		}
		j=t[j][s[i]-'a'];
		w[j]++;
	}
	fd(i,c,1)
		w[f[i]]+=w[i];
	fr(i,1,c)
		ans=max(ans,l[i]*w[i]);
	printf("%lld\n",ans);
	return 0;
}