**此题解所有小数均为近似值。**

显然这题可以看作一个在数轴上随机游走，先向左$1\sim 3$步再向右$1\sim 3$步，要求到达$-n$的概率减到达$n$的概率。

如果不在$-n+1\sim -n+3$，那么可以认为以$\dfrac 16$概率走$\pm 2$，以$\dfrac 13$概率走$\pm 1$。

令$f_p$表示在$p$位置走到$-n$的概率，则当$-n+3<p<n$时：
$$
f_p=\dfrac 16(f_{p-2}+f_{p+2}+2f_{p-1}+2f_{p+1})
$$
则：
$$
f_{p-2}=6f_p-f_{p+2}-2f_{p-1}-2f_{p+1}
$$
则：
$$
\begin{bmatrix}&1\\&&1\\&&&1\\-1&-2&6&-2\end{bmatrix}\begin{bmatrix}f_{p+2}\\f_{p+1}\\f_{p}\\f_{p-1}\end{bmatrix}=\begin{bmatrix}f_{p+1}\\f_{p}\\f_{p-1}\\f_{p-2}\end{bmatrix}
$$
令$A$为前面的矩阵，写出Jordan型：$A=XYX^{-1}$。

然后相当于要解出$x,y$满足：
$$
\begin{bmatrix}-1&-2&7&-1\\0&-1&-1&8\end{bmatrix}XY^{2n-4}X^{-1}\begin{bmatrix}0\\0\\x\\y\end{bmatrix}=\begin{bmatrix}3\\6\end{bmatrix}
$$
即：
$$
\begin{bmatrix}3&0&-3&-3\\6&3&8.19615&-2.19615\end{bmatrix}Y^{2n-4}\begin{bmatrix}1.16667 x + 0.333333 y\\0.5 x + 0.166667 y\\- 
 1.16068 x + 0.670121 y\\- 0.00598306 x - 0.00345432 y\end{bmatrix}=\begin{bmatrix}3\\6\end{bmatrix}
$$
然后要求出的是：
$$
XY^{n-1}X^{-1}\begin{bmatrix}0\\0\\x\\y\end{bmatrix}
$$
可以想办法暴力解出（套用样例）$2\sim 1000$的答案：
$$
\sum_{i=2}^{1000} \mathrm{ans}_n=7.0160858458787947371
$$
不难发现，$n>1000$时：
$$
|\sqrt 3x-y|\approx 0
$$
且这个数量级是$(2+\sqrt 3)^{-2n}$，然后不难发现，要用到的只有$(2+\sqrt 3)^n(\sqrt 3x-y)$，所以可以粗略的认为$\sqrt 3x=y$。

在删去对答案影响极小的部分：
$$
\begin{bmatrix}3&0&-3&-3\\6&3&8.19615&-2.19615\end{bmatrix}\begin{bmatrix}1.16667 x + 0.333333 y+(2n-4)(0.5 x + 0.166667 y)\\0.5 x + 0.166667 y\\ k\\0\end{bmatrix}=\begin{bmatrix}3\\6\end{bmatrix}
$$
然后可以得到$n$较大时的一个很好的估计：
$$
\mathrm{ans}_n=\dfrac{3+\sqrt3+6n(2 +\sqrt3)}{-18-10\sqrt3 + 12n(2 + \sqrt3)}
$$
$n$较大时，则可以看作调和级数求和，可以使用$\ln n$逼近它的和。