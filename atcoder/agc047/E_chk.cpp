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
const int N=1000000;
unsigned long long a[N];
int main()
{
	freopen("out","r",stdin);
	a[0]=2; a[1]=3;
	fr(T,1,read())
	{
		char op[5]; int x,y,z;
		scanf("%s%d%d%d",op,&x,&y,&z);
		assert(x>=0&&x<N); assert(y>=0&&y<N); assert(z>=0&&z<N);
		if(op[0]=='+') a[z]=a[x]+a[y];
		else if(op[0]=='<') a[z]=a[x]<a[y];
		else if(op[0]=='Q'){ T--; printf("%I64u\n",a[z]); }
		else assert(0);
		assert(a[z]<5000000000000000000ull);
	}
	printf("%I64u %I64u %I64u\n",a[0],a[1],a[2]);
	return 0;
}