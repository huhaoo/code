from sympy import bernoulli, binomial, exp, factorial, isprime

mod=10**9+7
n=10**18
# n=10
# n=3

def sump(m, n):
    # return sum(i**n for i in range(1, m+1))
    total = 0
    for j in range(n + 1):
        Bj = bernoulli(j)
        if j == 1: Bj = -Bj
        total += (-1)**(n - j) * binomial(n + 1, j) * Bj * m**(n + 1 - j)
    return total // (n + 1)

# The expression of H(n)
# def H(n):
#     res=0
#     for i in range(1,n+1): res+=(-1)**(n-i)*exp(i)*i**(n-i)/factorial(n-i)
#     return float(res)
# print(H(1),H(2),H(3))

n-=1
ans=0
p=1
for i in range(0,101):
    if isprime(i):
        p*=i
    m=(n-i+1)//p
    if m<=0: break
    s=sump(m,i)*(p**i)
    assert s%(factorial(i))==0
    ans+=s//factorial(i)
    # print(i,m,p,s,s//factorial(i))
print(ans%mod)