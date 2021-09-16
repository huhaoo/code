#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=1000010;
int n;
char s[N];
int main()
{
	n=read(); scanf("%s",s);
	int m=0;
	fr(i,0,n-1) s[i]-='1';

	m=0;
	fr(i,0,n-1) if(((n-1)&i)==i) m+=(s[i]==1);
	if(m&1){ printf("1\n"); return 0; }


	m=0;
	fr(i,0,n-1) if(s[i]==1) m=1;
	if(m){ printf("0\n"); return 0; }

	m=0;
	fr(i,0,n-1) if(((n-1)&i)==i) m+=(s[i]==2);
	if(m&1){ printf("2\n"); return 0; }

	printf("0\n");
	return 0;
}