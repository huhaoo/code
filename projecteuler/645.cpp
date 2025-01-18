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
const int N=100010;
int n;
long double ln[N],ans,P;
int main()
{
//	n=read();
	n=100000;
	ln[0]=0; fr(i,1,n) ln[i]=ln[i-1]+log(i);
	ans=1;
	fr(i,0,n-2)
	{
		P=1;
		if(i+i+2>=n) P-=exp((ln[i+1]-ln[n-i-1]-ln[i+i+2-n])-(ln[n-1]-ln[i]-ln[n-1-i]));
		ans+=P*(n*1./(n-i-1));
//		printf("%.10lf %.10lf\n",exp((ln[n-1]-ln[i]-ln[n-1-i])),exp((ln[i+1]-ln[n-i-1]-ln[i+i+2-n])));
	}
	printf("%.10lf\n",(double)ans);
	return 0;
}