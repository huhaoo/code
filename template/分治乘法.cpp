/***************************************************************
	File name: 分治乘法.cpp
	Author: huhao
	Create time: Fri 30 Oct 2020 05:20:02 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#include<vector>
#define i64 long long
#define poly std::vector<i64>
i64 n;
poly operator+(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]+=b[i]; return a; }
poly operator-(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]-=b[i]; return a; }
poly operator<<(poly a,int b){ a.resize(a.size()+b); fd(i,a.size()-1,b) a[i]=a[i-b]; fr(i,0,b-1) a[i]=0; return a; }
poly operator*(poly a,poly b) // |a|=|b|=2^k
{
	int n=a.size(),m=n/2;
	if(n<=300)
	{
		poly c(n+n-1);
		fr(i,0,n-1) fr(j,0,n-1) c[i+j]+=a[i]*b[j];
		return c;
	}
	poly B(a.begin(),a.begin()+n-m),A(a.begin()+n-m,a.begin()+n);
	poly D(b.begin(),b.begin()+n-m),C(b.begin()+n-m,b.begin()+n);
	poly r1=(A+B)*(C+D),r2=A*C,r3=B*D;
	return (r1<<m)+(r2<<(m+m))-(r2<<m)+r3-(r3<<m);
}
int main()
{
	return 0;
}
