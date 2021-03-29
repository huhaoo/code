/***************************************************************
	File name: easy.cpp
	Author: huhao
	Create time: Fri 20 Nov 2020 09:26:23 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#define i64 long long
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
const int D=500000000;
struct hash
{
	i64 a,b,p;
	i64 s;
	hash(i64 A=0,i64 B=0,i64 P=0){ a=A; b=B; p=P; s=0; }
	void add(i64 x,i64 y,int op=1){ x+=D; y+=D; s=(s+op*power(a,x,p)*power(b,y,p)%p+p)%p; }
	i64 query(i64 x,i64 y){ x+=D; y+=D; return s*power(a,p-1-x,p)%p*power(b,p-1-y,p)%p; }
} h1(17,107,998244353),h2(10007,233,1000000007);
i64 s1,s2;
const int N=1000010;
#include<map>
#include<set>
int n,m,l,C;
int X,Y;
char c[N],s[N];
int x[N],y[N];
std::map<std::pair<int,int>,int> t;
std::multiset<int> _x,_y;
int main()
{
	freopen("easy.in","r",stdin); freopen("easy.out","w",stdout);
	scanf("%d\n",&l);
	fr(i,0,l-1) c[i]=getchar();
	n=read(); m=read();
	fr(i,0,n-1) scanf("%s",s+i*m);
	X=n-1; Y=m-1;
	fr(i,0,n-1) fr(j,0,m-1) if(s[i*m+j]=='X'){ h1.add(i,j); h2.add(i,j); X=std::min(X,i); Y=std::min(Y,j); C++; }
	s1=h1.query(X,Y); s2=h2.query(X,Y); h1.s=h2.s=0;
	x[0]=y[0]=0;
	fr(i,0,l-1)
	{
		x[i+1]=x[i]; y[i+1]=y[i];
		switch(c[i])
		{
			case 'u': x[i+1]--; break;
			case 'd': x[i+1]++; break;
			case 'l': y[i+1]--; break;
			case 'r': y[i+1]++; break;
		}
	}
//	printf(" %lld %lld\n",s1,s2);
//	fr(i,0,l) printf("%d %d\n",x[i],y[i]);
	for(int i=0,j=-1;i<=l;i++)
	{
		while(j<l&&_x.size()<C)
		{
			j++; t[{x[j],y[j]}]++;
//			fprintf(stderr,"%d %d\n",i,j);
			if(t[{x[j],y[j]}]==1){ _x.insert(x[j]); _y.insert(y[j]); h1.add(x[j],y[j]); h2.add(x[j],y[j]); }
//			fprintf(stderr,"%d %d\n",i,j);
		}
//		fprintf(stderr,"%d %d\n",i,j);
		if(_x.size()<C) break;
//		printf("%d %d  %lld %lld\n",i,j,h1.query(*_x.begin(),*_y.begin()),h2.query(*_x.begin(),*_y.begin()));
		if(s1==h1.query(*_x.begin(),*_y.begin())&&s2==h2.query(*_x.begin(),*_y.begin()))
		{
			printf("YES\n%d %d\n",i+1,j);
			return 0;
		}
		t[{x[i],y[i]}]--;
		if(!t[{x[i],y[i]}]){ _x.erase(_x.find(x[i])); _y.erase(_y.find(y[i])); h1.add(x[i],y[i],-1); h2.add(x[i],y[i],-1); }
	}
	printf("NO\n");
	return 0;
}
