import imp
from math import log
n=800800
mx=log(n)*n
p=[]
vis=[0]*(int(mx*2)+1)
for i in range(2,int(mx*2)+1):
	if not vis[i]:
		p.append(i)
		for j in range(2,int(mx*2)//i+1):
			vis[i*j]=1
x,y=0,len(p)-1
ans=0
while x<y:
	if log(p[x])*p[y]+log(p[y])*p[x]>mx: y-=1
	else:
		ans+=y-x
		x+=1
print(ans)