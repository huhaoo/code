#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=5010;
i64 n,l,r,a[N];
i64 s[N][2];
i64 query(i64 l,i64 r,i64 op){ return l<=r?s[r][op]-s[l-1][op]:0; }
i64 Q(i64 x,i64 y,i64 op)
{
	return query(1,x-1,op)+query(x+1,y-1,op^1)+query(y+1,n,op);
}
int main()
{
	n=read(); l=read(); r=read();
	fr(i,1,n) a[i]=read();
	std::sort(a+1,a+n+1);
	fr(i,1,n){ s[i][0]=s[i-1][0]; s[i][1]=s[i-1][1]; s[i][i&1]+=a[i]; }
	fr(i,1,n) fr(j,1,n) if(i!=j)
	{
		if(a[i]+Q(std::min(i,j),std::max(i,j),1)<l) continue;
		if(a[i]+Q(std::min(i,j),std::max(i,j),0)>r) continue;
//		printf("%d %d  %lld %lld\n",i,j,a[i]+Q(std::min(i,j),std::max(i,j),0),a[i]+Q(std::min(i,j),std::max(i,j),1));
		printf("Alice\n"); return 0;
	}
	printf("Bob\n");
	return 0;
}