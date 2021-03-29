/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Fri 20 Nov 2020 11:31:37 AM CST
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
#include<queue>
const int N=300010;
int n,a[N],q,l[N],r[N],f[N],t[N],s1[N],s2[N],p1[N],p2[N];
int getf(int u){ return u==f[u]?u:f[u]=getf(f[u]); }
char Q[N];
std::priority_queue<std::pair<int,int> > v1,v2,V;
int _t;
void merge(int u,int v)
{
//	fprintf(stderr,"M %d %d   %d\n",u,v,_t);
	u=getf(u); v=getf(v);
	l[u]=std::min(l[u],l[v]); r[u]=std::max(r[u],r[v]);
	f[v]=u;
}
int query(int u,int T)
{
	a[u]+=p1[u]*(s1[T]-s1[t[u]])+p2[u]*(s2[T]-s2[t[u]]); t[u]=T;
	return a[u];
}
void update(int u,int v,int T)
{
//	static int cnt=0; if((++cnt)%100000==0) fprintf(stderr,"%d\n",cnt);
	int d=query(v,T)-query(u,T);
//	printf("%d %d %d   %d\n",u,v,T,d);
	if(d<0) return ;
	if(p1[u]&&p2[u]&&!p1[v]&&!p2[v]) V.push({-(T+d),u});
	else if(p1[u]&&!p1[v]) v1.push({-(s1[T]+d),u});
	else if(p2[u]&&!p2[v]) v2.push({-(s2[T]+d),u});
}
void update(int u,int T)
{
	int v=getf(l[u]-1),w=getf(r[u]+1);
	if(v&&query(v,T)>query(u,T)) p1[u]=1; else p1[u]=0;
	if(w&&query(w,T)>query(u,T)) p2[u]=1; else p2[u]=0;
	if(v) update(u,v,T);
	if(w) update(u,w,T);
}
int main()
{
	n=read(); q=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n) l[i]=r[i]=f[i]=i;
	fr(i,1,n-1) if(a[i]==a[i+1]) merge(i,i+1);
	fr(i,1,n) if(f[i]==i) update(i,0);
	fr(i,1,n) if(f[i]==i) update(i,0);
//	fr(i,1,n) if(f[i]==i) printf("%d  %d %d    %d %d\n",i,l[i],r[i],p1[i],p2[i]);
	scanf("%s",Q+1);
	fr(i,1,q)
	{
		_t++;
		if(Q[i]=='A') Q[i]=1;
		else Q[i]=2;
/*		if(Q[i]==1) fr(j,2,n){ if(a[j]<a[j-1]) a[j]++; }
		else{ fd(j,n-1,1) if(a[j]<a[j+1]) a[j]++; }
		fr(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
		continue;*/
		s1[i]=s1[i-1]; s2[i]=s2[i-1];
		if(Q[i]==1) s1[i]++;
		else s2[i]++;
		while(1)
		{
			int u=0;
			if(!V.empty()&&-V.top().first==i){ u=V.top().second; V.pop(); }
			else if(!v1.empty()&&-v1.top().first==s1[i]){ u=v1.top().second; v1.pop(); }
			else if(!v2.empty()&&-v2.top().first==s2[i]){ u=v2.top().second; v2.pop(); }
			if(!u) break;
//			fprintf(stderr,"%d  %d(%d)  %d %d\n",i,u,f[u],s1[i],s2[i]);
			if(f[u]!=u) continue;
			int flag=0;
//			printf("%d %d %d\n",query(getf(l[u]-1),i),query(u,i),query(getf(r[u]+1),i));
			if(getf(l[u]-1)&&query(u,i)==query(getf(l[u]-1),i)){ flag=1; merge(u,getf(l[u]-1)); }
			if(getf(r[u]+1)&&query(u,i)==query(getf(r[u]+1),i)){ flag=1; merge(u,getf(r[u]+1)); }
			if(!flag) continue;
			update(u,i);
			if(getf(l[u]-1))
			{
				update(getf(l[u]-1),i);
				if(getf(l[getf(l[u]-1)]-1)) update(getf(l[getf(l[u]-1)]-1),i);
			}
			if(getf(r[u]+1))
			{
				update(getf(r[u]+1),i);
				if(getf(r[getf(r[u]+1)]+1)) update(getf(r[getf(r[u]+1)]+1),i);
			}
		}
	}
//	fr(i,1,n) if(f[i]==i) printf("%d  %d %d    %d %d\n",i,l[i],r[i],p1[i],p2[i]);
	fr(i,1,n) printf("%d%c",query(getf(i),q),i==n?'\n':' ');
	return 0;
}
