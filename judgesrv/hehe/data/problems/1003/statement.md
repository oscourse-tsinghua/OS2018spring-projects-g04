### 题目描述

输入一个长度为 `n` 的数组 `a`，保证该数组已被从小到大排序，且不含重复元素。

另外输入一个 `x`，你需要返回 `a` 中 `x` 出现的位置。保证 `x` 在 `a` 中出现过。

### 接口

`int binary_search(const unsigned *a, int n, unsigned x)`

### 数据范围

`n` 等于 100,000,000。

函数 `binary_search` 会被调用 100 次，但多次调用时，仅 `x` 发生变化。

### 注意事项

本题的 `a` 数组不计入空间限制，但你不能修改其中的内容。

交互库会占用 4 KB 的内存。
