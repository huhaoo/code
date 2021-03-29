/***************************************************************
	File name: joker.cpp
	Author: huhao
	Create time: Sun 15 Nov 2020 03:23:53 PM CST
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
#define pii std::pair<i64,i64>
#define piii std::pair<pii,i64>
#define F first
#define S second
const int W=500,N=50010;
i64 n,a[N],q;
i64 sp,sn;
pii operator+(pii a,pii b){ return pii(a.F+b.F,a.S+b.S); }
pii &operator+=(pii &a,pii b){ return a=a+b; }
pii operator-(pii a,pii b){ return pii(a.F-b.F,a.S-b.S); }
i64 operator*(pii a,pii b){ return a.F*b.S-a.S*b.F; }
i64 calc(pii f,i64 x,i64 y){ return f.F*y-f.S*x; }
struct kuai
{
	i64 a[W+10]; pii _s;
	pii S[W+10];
	i64 s[W+10],t;
	void rebuild()
	{
		fr(i,0,W-1){ S[i]=pii((a[i]>0?a[i]:0),(a[i]<0?-a[i]:0)); }
		fr(i,1,W-1) S[i]+=S[i-1];
		s[t=1]=0;
		fr(i,1,W-1)
		{
			while(t>=2&&(S[s[t]]-S[s[t-1]])*(S[i]-S[s[t-1]])<=0) t--;
			s[++t]=i;
		}
		return ;
		printf("%d\n",t);
		fr(i,0,W-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
		fr(i,0,W-1) printf("(%lld,%lld)%c",S[i].F,S[i].S,i==end_i?'\n':' ');
		fr(i,1,t) printf("%lld%c",s[i],i==t?'\n':' ');
	}
	void modify(int p,int v)
	{
		if(a[p]>0) _s.F-=a[p]; else _s.S+=a[p];
		a[p]=v;
		if(a[p]>0) _s.F+=a[p]; else _s.S-=a[p];
		rebuild();
	}
	piii query(i64 x,i64 y,int d,pii D)
	{
		int l=1,r=t;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(calc(S[s[mid]],x,y)<calc(S[s[mid+1]],x,y)) l=mid+1;
			else r=mid;
		}
//		printf("Q => %d\n",s[l]+d);
		return piii(S[s[l]]+D,s[l]+d);
	}
} A[N/W+10];
void modify(int p,int v)
{
	if(a[p]>0) sp-=a[p]; else sn+=a[p];
	a[p]=v;
	if(a[p]>0) sp+=a[p]; else sn-=a[p];
	A[p/W].modify(p%W,v);
}
i64 query()
{
	pii s; piii ans;
	fr(i,0,n/W)
	{
		piii Ans=A[i].query(sp,sn,i*W,s); s+=A[i]._s;
		if(i==0||calc(Ans.first,sp,sn)>calc(ans.first,sp,sn)) ans=Ans;
	}
	return ans.second;
}
int main()
{
	freopen("joker.in","r",stdin); freopen("joker.out","w",stdout);
	n=read(); q=read();
	fr(i,0,n-1) modify(i,read());
	printf("%lld\n",std::min(query()+1,n));
	while(q--)
	{
		int x=read(),y=read();
		modify(x-1,y); printf("%lld\n",std::min(query()+1,n));
	}
	return 0;
}
