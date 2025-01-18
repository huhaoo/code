from math import gcd
import sys
n=10**9
mx=29000
ans=0
C=2.125224026569094
vis=set()
cnt=0
def hash(a):
	return a[0]*10**18+a[1]*10**9+a[2]
def calc(p,q):
	global ans,vis,cnt
	x=(5*p-11*q)*(21*p-43*q)
	y=16*(p-3*q)*(2*p-5*q)
	z=(5*p-3*q)*(3*p-5*q)
	if x>n*64 or y>n*64 or z>n*64: return 1
	if x<=0 or y<=0 or z<=0 or gcd(p,q)!=1: return 0
	g=gcd(x,y,z)
	x//=g
	y//=g
	z//=g
	if x<=n and y<=n and z<=n:
		a=[x,y,z]
		a.sort()
		if not hash(a) in vis:
#			print(a)
			ans+=x+y+z
			cnt+=1
			vis.add(hash(a))
for q in range(1,mx):
	p=int(C*q)
	while not calc(p,q): p=p-1
	x=p
	p=int(C*q)+1
	while not calc(p,q): p=p+1
	if q<100 or q%1000==0:
		print(q,x,p,cnt,ans)
		sys.stdout.flush()
print(ans)
#print(gcd(10**10,10**12))