# 简单数学题

## 题目背景

ZX在学完莫比乌斯反演后，练习了许多简单的数学题，比如：

$$
\sum\limits_{i=1}^n\sum\limits_{j=1}^mij\gcd(i,j)=\sum\limits_{k=1}^nk^2\varphi(k)\sum\limits_{i=1}^{\lfloor n/k\rfloor }i^3
$$

$$
\sum\limits_{i=1}^n\sum\limits_{j=1}^m [\gcd(i,j)\in \mathbf{prime}]=\sum\limits_{T=1}^n\left\lfloor\frac{T}{n}\right\rfloor\left\lfloor\frac{T}{m}\right\rfloor\sum\limits_{\substack{p\mid T\\ p\in \mathbf{prime}}}\mu\left(\frac{T}{p}\right)
$$

## 题目描述

现在ZX要加大难度，计算

$$
f(n,m)=\sum_{i=1}^n\sum_{j=1}^m\gcd(i,j)\mathrm{lcm}(i,j)
$$

## 输入格式

一行两个整数 $n,m$ 用空格隔开。

## 输出格式

输出一行一个整数：$f(n,m)\bmod (10^9+7)$。

## 示例1

### 输入

```
1 1
```

### 输出

```
1
```

## 备注

$1\le n,m\le 10^{18}$