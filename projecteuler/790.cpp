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
//const int M=100,N=100;
const int M=50515093,N=1<<20;
class tree
{
public:
	tree *s[2];
	int c;
	tree(){ c=0; s[0]=s[1]=nullptr; }
	~tree()
	{
		if(s[0]!=nullptr) delete s[0];
		if(s[1]!=nullptr) delete s[1];
	}
	void update(){ c=s[0]->c+s[1]->c; }
} *t[14];
std::map<int,std::vector<std::pair<int,int> > > p1,p2;
tree *build(int l,int r,int v)
{
	tree *k=new tree; int mid=(l+r)>>1;
	if(l!=r){ k->s[0]=build(l,mid,v); k->s[1]=build(mid+1,r,v); k->c=k->s[0]->c+k->s[1]->c; }
	else k->c=v;
	return k;
}
void swap(tree *&x,tree *&y,int l,int r,int L,int R)
{
//	if(l==0&&r==N-1) printf("%d %d\n",l,r);
	if(l>R||L>r) return ;
	if(L<=l&&r<=R){ std::swap(x,y); return ; }
	int mid=(l+r)>>1; swap(x->s[0],y->s[0],l,mid,L,R); swap(x->s[1],y->s[1],mid+1,r,L,R);
	x->update(); y->update();
}
int Rand(){ static int S=290797; int k=S%M; S=(i64)S*S%M; return k; }
i64 ans;
int main()
{
	fr(i,1,read())
	{
		int x=Rand(),X=Rand(),y=Rand(),Y=Rand();
		if(x>X) std::swap(x,X); if(y>Y) std::swap(y,Y);
//		printf("%d %d  %d %d\n",x,X,y,Y);
		p1[x].push_back({y,Y}); p2[X].push_back({y,Y});
	}
	fr(o,0,(M-1)/N)
	{
		int l=o*N,r=std::min(M-1,(o+1)*N-1);
		tree *NUL=build(l,r,1);
		fr(i,1,12) t[i]=build(l,r,i==12);
		fr(i,0,M-1)
		{
			if(p1.count(i)) for(auto j:p1[i]) fr(k,1,13){ swap(t[k==13?1:k],NUL,l,r,std::max(l,j.first),std::min(r,j.second)); }
			fr(j,1,12) ans+=j*t[j]->c;
//			fr(j,1,12) printf("%d%c",t[j]->c,j==12?'\n':' ');
			if(p2.count(i)) for(auto j:p2[i]) fd(k,13,1){ swap(t[k==13?1:k],NUL,l,r,std::max(l,j.first),std::min(r,j.second)); }
		}
		fr(i,1,12) delete t[i];; delete NUL;
		printf("Done %d/%d\n",o+1,(M-1)/N+1); fflush(stdout);
	}
	printf("%lld\n",ans);
	return 0;
}