/***************************************************************
	File name: curiosity.cpp
	Author: huhao
	Create time: Tue 27 Oct 2020 09:03:16 PM CST
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
#include<map>
#include<vector>
#include<iostream>
#define i64 long long
const int N=2020,sed=10007,mod=998244353;
char s[N],c[N];
i64 h1[N],h2[N];
i64 p[N];
int n,m;
i64 query(i64 *h,int l,int r){ return (h[r]-h[l-1]+mod)*p[N-10-r]%mod; }
int f[N];
std::map<i64,int> lst;
std::vector<int> F[N];
int main()
{
	freopen("curiosity.in","r",stdin); freopen("curiosity.out","w",stdout);
	p[0]=1;
	fr(i,1,N-10) p[i]=p[i-1]*sed%mod;
	std::cin.getline(s+1,N-10); std::cin.getline(c+1,N-10);
	n=strlen(s+1); m=strlen(c+1);
	fr(i,1,n) h1[i]=(h1[i-1]+s[i]*p[i])%mod;
	fr(i,1,m) h2[i]=(h2[i-1]+c[i]*p[i])%mod;
	fr(i,1,n)
	{
		fr(j,1,n-i+1) F[j].clear();
		lst.clear();
		fr(j,1,n-i+1)
		{
			if(lst.count(query(h1,j,j+i-1)))
			{
				f[j]=lst[query(h1,j,j+i-1)];
				if(j-f[j]<i) continue;
				f[j]=f[f[j]];
			}
			else f[j]=j;
			F[f[j]].push_back(j); lst[query(h1,j,j+i-1)]=j;
		}
		fr(j,1,n-i+1) if(f[j]==j)
		{
			if(std::abs(m-n)%F[j].size()!=0) continue;
			int c=F[j].size(),d=(m-(n-c*i))/c,flag=1; F[j].push_back(n+1);
			if(d<0) continue;
//			printf("%d %d   %d %d\n ",i,j,c,d);
//			fr(k,0,F[j].size()-1) printf("%d%c",F[j][k],k==end_k?'\n':' ');
			int Lst=1,_lst=1;
			fr(k,0,c)
			{
				int l=F[j][k]-Lst-1;
//				printf("%d %d  %d %d\n",Lst,F[j][k]-1,_lst,_lst+l);
				if(query(h1,Lst,F[j][k]-1)!=query(h2,_lst,_lst+l)) flag=0;
				Lst=F[j][k]+i; _lst=_lst+l+d+1;
			}
//			printf("  %d\n",flag);
			fr(k,1,c-1) if(query(h2,F[j][0],F[j][0]+d-1)!=query(h2,F[j][k]+(d-i)*k,F[j][k]+(d-i)*k+d-1)) flag=0;
//			printf("  %d\n",flag);
			if(flag)
			{
				printf("s/");
				fr(k,0,i-1) putchar(s[j+k]);
				putchar('/');
				fr(k,0,d-1) putchar(::c[j+k]);
				printf("/g\n");
				return 0;
			}
		}
	}
	return 0;
}
