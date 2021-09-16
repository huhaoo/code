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
const int W=30;
void ls(int u,int v,int l)
{
	printf("+ 4 %d %d\n",u,v);
	while(l--) printf("+ %d %d %d\n",v,v,v);
}
void And(int x,int y,int z){ printf("+ %d %d %d\n< 100 %d %d\n",x,y,z,z,z); }
void split(int u,int d)
{
	printf("+ %d 100 5\n+ 4 4 6\n",u);
	fd(i,W,0)
	{
		printf("+ %d 6 7\n< 7 5 7\n+ 7 4 %d\n",100+i,d+i);
		ls(7,7,i); printf("+ 6 7 6\n");
	}
}
int main()
{
//	freopen("out","w",stdout);
	printf(R"(33953
+ 0 1 2
+ 2 2 2
< 0 2 3
+ 100 3 100
)");
	fr(i,1,30) printf("+ %d %d %d\n",100+i-1,100+i-1,100+i);
	// 100+i: 2^i
	split(0,200); split(1,300);
	printf("+ 4 4 2\n");
//	fr(i,0,5) printf("Q 0 0 %d\n",100+i);
	fr(i,0,W) fr(j,0,W){ And(200+i,300+j,5); ls(5,5,i+j); printf("+ 2 5 2\n"); }
	return 0;
}