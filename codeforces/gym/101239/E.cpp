/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Wed 28 Oct 2020 06:47:29 PM CST
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
const int N=4010;
int n;
char s[N][N];
int l[N];
int x,y,X[N],Y[N],p[N];
#define nosol printf("impossible\n"),exit(0)
int f(int a,int b)
{
	if(a==-1) return 1;
	if(l[a]>=l[b]) return 0;
	int j=0;
	fr(i,0,l[b]-1) if(j!=l[a]&&s[b][i]==s[a][j]) j++;
	return j==l[a];
}
int main()
{
	n=read();
	fr(i,0,n){ scanf("%s",s[i]); l[i]=strlen(s[i]); }
	fr(i,1,n) if(f(i,0)==0) nosol;
	fr(i,1,n) p[i]=i;
	std::sort(p+1,p+n+1,[&](int a,int b){ return l[a]<l[b]; });
	X[X[0]=1]=x=p[1]; y=-1;
	fr(i,2,n)
	{
		int z=p[i];
		if(f(x,z)&&f(y,z))
		{
			int j=i+1;
			while(j<=n&&f(p[j-1],p[j])) j++;
			if(f(y,p[j]))
			{
				j--;
				fr(k,i,j) X[++X[0]]=p[k];
				x=p[j]; i=j;
			}
			else if(f(x,p[j]))
			{
				j--;
				fr(k,i,j) Y[++Y[0]]=p[k];
				y=p[j]; i=j;
			}
			else nosol;
		}
		else if(f(y,z)){ y=z; Y[++Y[0]]=y; }
		else if(f(x,z)){ x=z; X[++X[0]]=x; }
		else nosol;
//		printf("%d  %s %s\n",i,s[x],s[y]);
	}
	printf("%d %d\n",X[0],Y[0]);
	fr(i,1,X[0]) printf("%s\n",s[X[i]]);
	fr(i,1,Y[0]) printf("%s\n",s[Y[i]]);
	return 0;
}
