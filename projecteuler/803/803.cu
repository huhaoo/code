#include<stdio.h>
#include<cuda.h>
#define i64 long long
#define u64 unsigned long long
#define f(x) ((x)*25214903917ull+11)&281474976710655ull
#define f20(x) ((x)*280364631195649ull+215216710221824ull)&281474976710655ull
#define st 144933752257087ull
__global__ void init(u64 *v)
{
	v[0]=st; for(int i=1;i<(1<<20)+10;i++) v[i]=f(v[i-1]);
//	printf("%llu %llu\n",v[0],v[123456]);
}
__global__ void search(u64 _id)
{
	u64 x=threadIdx.x+(blockIdx.x<<10)+(_id<<20),y=x;
//	printf("%llu\n",x);
	static const int l=9;
	static const int val[l]={41,20,25,25,11,4,40,13,4};
	for(int i=0;;i++)
	{
		if((x>>16)%52!=val[i]) break;
		if(i==l-1){ printf("%llu\n",y); break; }
		x=f(x);
	}
}
__global__ void update(u64 *v)
{
	u64 x=threadIdx.x+(blockIdx.x<<10);
	if(x<(1<<20)+10) v[x]=f20(v[x]);
}
__global__ void check(u64 _id,u64 *v)
{
	static const int l=9;
	static const int val[l]={37,20,2,10,24,45,4,23,19};
//	static const int val[l]={3,16,32,27,34,15,42,46,49};
	int x=threadIdx.x+(blockIdx.x<<10);
	for(int i=0;i<l;i++)
		if((v[i+x]>>16)%52!=val[i]) break;
		else if(i==l-1){ printf("%llu\n",x+(_id<<20)); }
}
int main()
{
/*	for(u64 i=0;i<(1<<28);i++)
	{
		search<<< (1<<10),(1<<10) >>>(i);
		cudaDeviceSynchronize();
//		if(i%(1<<8)==0) printf("%llu\n",i);
	}*/
/*	u64 a=st;
	for(int i=0;i<12345678;i++) a=f(a);
	for(int i=0;i<9;i++){ printf("%d,",int((a>>16)%52)); a=f(a); }*/
	u64 *val; cudaMalloc(&val,sizeof(u64)*(1<<20)+10);
	init<<<1,1>>>(val);
//	cudaError_t error = cudaGetLastError();
//	printf("CUDA error: %s\n", cudaGetErrorString(error));
	for(u64 i=0;i<(1<<28);i++)
	{
		check<<<(1<<10),(1<<10)>>>(i,val);
		cudaDeviceSynchronize();
		update<<<(1<<10)+1,(1<<10)>>>(val);
		cudaDeviceSynchronize();
//		if(i%(1<<8)==0) printf("%llu\n",i);
	}
	cudaFree(val);
	printf("finished.\n");
	return 0;
}