/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Fri 22 Jan 2021 03:33:34 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=2000010;
int n,p[N],v[N],V[N],d[N],mi;
char s[N],t[N];
std::vector<int> c[N];
int ans,Ans,x,y,T;
int main()
{
	n=read(); scanf("%s%s",s+1,t+1);
	if(!strcmp(s+1,t+1)){ printf("0\n"); return 0; }
	fr(i,1,n) c[s[i]].push_back(i);
	mi=n;
	fd(i,n,1)
	{
		mi=std::min(mi,i);
		if(t[i]!=t[i-1])
		{
			while(!c[t[i]].empty()&&*--c[t[i]].end()>mi) c[t[i]].pop_back();
			if(c[t[i]].empty()){ printf("-1\n"); return 0; }
			p[i]=*--c[t[i]].end(); c[t[i]].pop_back(); mi=std::min(mi,p[i]);
		}
	}
	fr(i,1,n) if(p[i]&&i!=p[i]) v[i]=V[p[i]]=1;
	int P=0;
	fd(i,n,1)
	{
		T++;
		if(V[i]){ if(P) printf("- %d\n",T+n-y); d[T+n-y]--; y++; }
		if(P) printf("< %d\n",T+n-x);
		Ans+=d[T+n-x]; d[T+n-x]=0; ans=std::max(ans,Ans);
		if(v[i]){ if(P) printf("+\n"); Ans++; x++; }
//		printf("%d  %d %d  %d\n",i,v[i],V[i],Ans);
	}
	printf("%d\n",ans+1);
	return 0;
}
