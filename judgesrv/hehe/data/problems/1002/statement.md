### 题目描述

输入两个一元多项式，输出它们的乘积。

### 接口

`void poly_multiply(unsigned *a, int n, unsigned *b, int m, unsigned *c)`

* 输入的第一个多项式为 `n` 次，各项系数存在 `a[0]` 至 `a[n]` 中
* 输入的第二个多项式为 `m` 次，各项系数存在 `b[0]` 至 `b[m]` 中
* 你需要将结果（乘积）输出到 `c` 数组中，各项系数为 `c[0]` 至 `c[n + m]`

### 数据范围

* `n` 和 `m` 均等于 1,000,000
* 输入的所有多项式的系数均小于 10
