记$f_{n,k}$为$n$个数$a_{1\dots n}$和为$k$的方案数（$\forall i,\exists j~a_i=b_j$）

那么答案为$\sum_{i=0}^\infty f_{\frac n2,i}^2$

可以发现：

$$
f_{i,j}=\sum_{k}f_{i-1,j-b_k}
$$

边界：$f_{0,0}=1$

可以发现$f_{a,b}$对$f_{c,d}$（$a<c$）的贡献为$f_{c-1,d-b}$

于是如果我们知道了$f_{2^i,0\dots\infty}$那么我们可以直接得到$f_{2^{i+1},0\dots\infty}$

因为由上上行可得：

$$
f_{a+b,i}=\sum_{j=0}^if_{a,j}f_{b,i-j}
$$

所以类似快速幂一样，用NTT优化乘法可以$O(n\lg n\lg nk)$做出

