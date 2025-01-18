#include<bits/stdc++.h>
#include<thread>
#include<mutex>
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
const int N=100000010;
int n,lst;
i64 a[N];
int mx;
void search(int i)
{
	int k=i-1,c=0;
	fr(j,1,i-1)
	{
		while(k>=j&&a[j]+a[k]>a[i]) k--;
		if(k<j) break;
		if(a[j]+a[k]==a[i]){ printf("%d %d   %lld %lld\n",j,k,a[j],a[k]); c++; }
	}
	printf("%d %lld  %d\n",i,a[i],c);
}
int main()
{
	n=100000000; lst=1;
	fr(i,1,n) a[i]=(i64)i*(3*i-1)/2;
	search(15431918);
	return 0;
}