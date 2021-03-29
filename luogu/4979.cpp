/**************************************************************
	File name: 4979.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 4/1/2019, 12:55:55 PM
**************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
struct _odt
{
	int l,r;
	mutable int v;
	_odt(int _l=0,int _r=0,int _v=0)
	{
		l=_l;
		r=_r;
		v=_v;
	}
};
bool operator<(_odt a,_odt b)
{
	return a.l<b.l;
}
#include<set>
set<_odt>odt;
const int N=500010;
int n,q;
char c[N];
#define odtit set<_odt>::iterator
odtit pos(int p)
{
	return --odt.upper_bound(_odt(p,0,0));
}
odtit split(int p)
{
//	fprintf(stderr,"%d\n",p);
	if(p==n+1)
		return odt.end();
	odtit it=pos(p);
	if(it->l==p)
		return it;
	int v=it->v,l=it->l,r=it->r;
	odt.erase(it);
	odt.insert(_odt(l,p-1,v));
	return odt.insert(_odt(p,r,v)).first;
}
void merge(odtit it)
{
	while(it->l!=1)
	{
		odtit _it=it;
		_it--;
		if(_it->v==it->v)
		{
			int l=_it->l,r=it->r,v=it->v;
			odt.erase(it);
			odt.erase(_it);
			it=odt.insert(_odt(l,r,v)).first;
		}
		else 
			break;
	}
	while(it->r!=n)
	{
		odtit _it=it;
		_it++;
		if(it->v==_it->v)
		{
			int l=it->l,r=_it->r,v=it->v;
			odt.erase(it);
			odt.erase(_it);
			it=odt.insert(_odt(l,r,v)).first;
		}
		else 
			break;
	}
}
void modfiy(int l,int r,int v)
{
	odtit _r=split(r+1),_l=split(l);
//	fprintf(stderr,"233\n");
//	fprintf(stderr," %d %d %d\n",_l->l,_l->r,_l->v);
//	fprintf(stderr," %d %d %d\n",_r->l,_r->r,_r->v);
	while(_l!=_r)
		odt.erase(_l++);
	odtit it=odt.insert(_odt(l,r,v)).first;
	merge(it);
}
int main()
{
	n=read();
	scanf("%s",c+1);
	fr(i,1,n)
		c[i]-='A';
	for(int i=1,j;i<=n;i=j+1)
	{
		j=i;
		while(c[j+1]==c[i]&&j<n)
			j++;
		odt.insert(_odt(i,j,c[i]));
	}
	q=read();
//	for(auto i:odt)
//		fprintf(stderr,"%d %d %d\n",i.l,i.r,i.v);
//	fprintf(stderr,"\n");
	while(q--)
	{
		scanf("%s",c);
		if(*c=='A')
		{
			int l=read(),r=read();
			scanf("%s",c);
			modfiy(l,r,*c-'A');
		}
		else
		{
			int l=read(),r=read();
			odtit _l=pos(l),_r=pos(r);
			if(_l==_r)
			{
				if(l==1||r==n)
				{
					printf("Yes\n");
				}
				else
				{
					if(pos(l-1)->v==pos(r+1)->v)
						printf("No\n");
					else
						printf("Yes\n");
				}
			}
			else 
			{
				printf("No\n");
			}
		}
	}
//	for(auto i:odt)
//		fprintf(stderr,"%d %d %d\n",i.l,i.r,i.v);
//	fprintf(stderr,"\n");
	return 0;
}