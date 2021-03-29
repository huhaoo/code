/***************************************************************
	File name: sam.cpp
	Author: huhao
	Create time: Thu 14 Nov 2019 02:42:09 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=4000010;
int n,lst,cnt,w[N],l[N],t[N][26],f[N],S[N],T,d[N];
i64 ans;
char s[N];
void attend(int c)
{
	int p=lst,np=++cnt,q,nq;
	l[np]=l[lst]+1; lst=np; w[np]=1;
	while(p&&!t[p][c]){ t[p][c]=np; p=f[p]; }
	if(!p){ f[np]=1; return; }
	q=t[p][c];
	if(l[p]+1==l[q]){ f[np]=q; return; }
	nq=++cnt; l[nq]=l[p]+1; f[nq]=f[q]; f[q]=f[np]=nq;
	memcpy(t[nq],t[q],sizeof(t[nq]));
	while(p&&t[p][c]==q){ t[p][c]=nq; p=f[p]; }
}
int main()
{
	lst=cnt=1;
	scanf("%s",s+1); n=strlen(s+1);
	fr(i,1,n) attend(s[i]-'a');
	fr(i,2,cnt) d[f[i]]++;
	fr(i,1,cnt) if(!d[i]) S[++T]=i;
	while(T)
	{
		int u=S[T--];
		if(f[u])
		{
			w[f[u]]+=w[u]; d[f[u]]--;
			if(!d[f[u]]) S[++T]=f[u];
		}
	}
	fr(i,1,cnt) if(w[i]>1) ans=max(ans,(i64)w[i]*l[i]);
	printf("%lld\n",ans);
	return 0;
}
