/***************************************************************
	File name: iceberg.cpp
	Author: huhao
	Create time: Thu 14 Jan 2021 02:37:41 PM CST
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
#include<set>
i64 gp;
i64 q;
std::set<std::vector<i64> > s,b;
// p    pr    id    v    tv    cv
int main()
{
	freopen("iceberg.in","r",stdin); freopen("iceberg.out","w",stdout);
	q=read();
	while(q--)
	{
		i64 id=read(),op=read(),p=read(),v=read(),tv=read();
		std::vector<std::vector<i64> > ans;
		if(op==2)
		{
			while(v)
			{
				std::vector<std::vector<i64> > B;
				while(v&&!b.empty()&&-(*b.begin())[0]>=p&&(B.empty()||B[0][0]==-(*b.begin())[0]))
				{
					auto i=*b.begin(); i[0]=-i[0]; b.erase(b.begin());
					i64 vt=std::min(i[5],v);
					ans.push_back({i[2],id,i[0],vt}); i[3]-=vt; i[5]-=vt; v-=vt;
					if(i[3]&&!i[5]){ i[5]=std::min(i[3],i[4]); i[1]=++gp; }
					if(i[3]) B.push_back({i[0],i[1],i[2],i[3],i[4],i[5]});
				}
				if(B.empty()) break;
				if(v)
				{
					i64 l=1,r=1000000001;
					while(l<r)
					{
						i64 mid=(l+r)>>1; i64 u=0;
						for(auto i:B) u+=std::min(i[3],i[4]*mid);
						if(u<=v) l=mid+1;
						else r=mid;
					}
					l--;
					for(auto i:B)
					{
						i64 vt=std::min(i[3],i[4]*l);
						ans.push_back({i[2],id,i[0],vt}); i[3]-=vt; i[5]=std::min(i[3],i[4]); v-=vt;
						if(i[3]) b.insert({-i[0],i[1],i[2],i[3],i[4],i[5]});
					}
				}
				else for(auto i:B) b.insert({-i[0],i[1],i[2],i[3],i[4],i[5]});
			}
			if(v) s.insert({p,++gp,id,v,tv,std::min(v,tv)});
		}
		else
		{
			while(v)
			{
				std::vector<std::vector<i64> > S;
				while(v&&!s.empty()&&(*s.begin())[0]<=p&&(S.empty()||S[0][0]==(*s.begin())[0]))
				{
					auto i=*s.begin(); s.erase(s.begin());
					i64 vt=std::min(i[5],v);
					ans.push_back({id,i[2],i[0],vt}); i[3]-=vt; i[5]-=vt; v-=vt;
					if(i[3]&&!i[5]){ i[5]=std::min(i[3],i[4]); i[1]=++gp; }
					if(i[3]) S.push_back({i[0],i[1],i[2],i[3],i[4],i[5]});
				}
				if(S.empty()) break;
				if(v)
				{
					i64 l=1,r=1000000001;
					while(l<r)
					{
						i64 mid=(l+r)>>1; i64 u=0;
						for(auto i:S) u+=std::min(i[3],i[4]*mid);
						if(u<=v) l=mid+1;
						else r=mid;
					}
					l--;
					for(auto i:S)
					{
						i64 vt=std::min(i[3],i[4]*l);
						ans.push_back({id,i[2],i[0],vt}); i[3]-=vt; i[5]=std::min(i[3],i[4]); v-=vt;
						if(i[3]) s.insert({i[0],i[1],i[2],i[3],i[4],i[5]});
					}
				}
				else for(auto i:S) s.insert(i);
			}
			if(v) b.insert({-p,++gp,id,v,tv,std::min(v,tv)});
		}
		if(ans.empty()) continue;
		std::sort(ans.begin(),ans.end()); auto lst=*ans.begin(); lst[3]=0;
		for(auto i:ans)
			if(i[0]==lst[0]&&i[1]==lst[1]) lst[3]+=i[3];
			else
			{
				printf("%lld %lld %lld %lld\n",lst[0],lst[1],lst[2],lst[3]);
				lst=i;
			}
		printf("%lld %lld %lld %lld\n",lst[0],lst[1],lst[2],lst[3]);
	}
	putchar(10);
	std::vector<std::vector<i64> > ans;
	for(auto i:b) ans.push_back({-i[0],i[1],i[2],i[3],i[4],i[5],1ll});
	for(auto i:s) ans.push_back({i[0],i[1],i[2],i[3],i[4],i[5],2ll});
	std::sort(ans.begin(),ans.end());
	for(auto i:ans) printf("%lld %lld %lld %lld %lld %lld\n",i[2],i[6],i[0],i[3],i[4],i[5]);
	return 0;
}
