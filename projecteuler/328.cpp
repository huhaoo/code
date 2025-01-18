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
#define pii std::pair<int,int>
const int N=500010;
std::vector<pii> f[N];
int query(int l,int r){ return l<=r?std::upper_bound(f[r].begin(),f[r].end(),pii{l+1,0},std::greater<pii>() )->second:0; }
void reshape(std::vector<pii> &f)
{
	std::vector<pii> F(f.size());
	std::copy(f.begin(),f.end(),F.begin());
	F.swap(f);
}
void clear(std::vector<pii> &f){ std::vector<pii>().swap(f); }
int n;
int main()
{
	n=500000;
	i64 ans=0;
	fr(i,1,n)
	{
		f[i].push_back({i,0});
		int j=i-1,s,p=0; std::vector<pii> h={{i,0}};
		while(j)
		{
			s=i+query(j,i-1); p=i;
			auto l=h.begin(),r=--h.end();
			while(r-l>6)
			{
				int d=(r-l)/3; auto p1=l+d,p2=r-d;
#define calc(p) ((p).first-1+std::max((p).second,query(j,(p).first-2)))
				if(calc(*p1)<calc(*p2)) r=p2;
				else l=p1;
			}
			for(auto k=l;k<=r;k++) if(calc(*k)<=calc(*l)) l=k;
			s=calc(*l); p=l->first-1;
//			for(auto t:f[i]) if(calc(t)<=s){ s=calc(t); p=t.first-1; }
#undef calc
			j=p-1;
			if(!f[p-1].empty()&&f[p-1].begin()->second+p<=s)
				j=(--std::lower_bound(f[p-1].begin(),f[p-1].end(),pii{0,s-p+1},
				[&](pii a,pii b){ return a.second<b.second; }))->first-1;
//			for(auto t:f[p-1]) if(p+t.second<=s) j=t.first-1; else break;
			f[i].push_back({j+1,s});
			while(!h.empty()&&h.back().first-1+h.back().second>=j+s) h.pop_back();
			h.push_back({j+1,s});
		}
		reshape(f[i]);
		if(i%1000==0){ static auto t=clock(); printf("%d %d %d\n",i,(int)f[i].size(),(int)(clock()-t)); t=clock(); fflush(stdout); }
		if(i%10000==0){ static int lst=0; while(lst<i-(i/6.5)) clear(f[++lst]); }
		ans+=query(1,i);
//		fr(j,1,i) printf("%d%c",query(j,i),i==j?'\n':' '); fflush(stdout);
	}
	printf("%lld\n",ans);
	return 0;
}