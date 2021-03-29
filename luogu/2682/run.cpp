#include<stdio.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
/*
int main()
{
	freopen("4.out","w",stdout);
	printf("4 2\n");
	fr(i,1,8)
	{
		printf("32\n");
		fr(j,1,16)
			printf("in\nadd tmp\n");
	}
	return 0;
}*/
int main()
{
	freopen("8.out","w",stdout);
	int a=1,b=0;
	printf("1 1\n213\nin\nswap\n");
	fr(i,1,42)
	{
		swap(a,b);
		a+=b;
		printf("add -1\nif key\ngoto %d\nset %d\ngoto %d\n",3+5*i,a,213);
	}
	printf("out\n");
	return 0;
}
