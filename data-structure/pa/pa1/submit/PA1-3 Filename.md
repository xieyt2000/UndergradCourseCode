# PA1-3 Filename

## 数据结构与算法

本题仅使用数组，未使用特殊的数据结构，算法为优化过的LCS。LCS运用动态规划的方法减而治之。优化方法参考https://www.cs.helsinki.fi/u/ukkonen/InfCont85.PDF这篇论文，有了K的约束条件后，可以仅计算动态规划矩阵每行在对角线两边的K个元素，因为其他元素修改代价元素的一定大于K，空间方面因为仅需存储本行和上一行的数据，于是使用了两个滚动数组进行优化。

## 复杂度分析

显然，算法仅使用一维数组，空间复杂度为$ O(N) $。时间复杂度方面，需要计算$ N \times N $矩阵每行的K个元素，复杂度为$ O(KN) $，特别的，如果 $ 2 \times K<N-1 $，则矩阵无需压缩，复杂度为$ O(N^2) $。

## 完成过程问题

本题我在计算数据规模后发现原LCS算法时间效率不足，便在维基百科上搜索了编辑距离的优化算法最终参考了上文中提到的那篇文章。而在空间复杂度方面，开始我并没有使用滚动数组，而是选择使用一个$ N\times 2K $的矩阵，虽然不会MLE，但是坐标转换等各种写法复杂，我放弃了这种写法，最终使用了如下代码所示的滚动数组。

```c++
int oprCountLine1[MAX_LENGTH], oprCountLine2[MAX_LENGTH];	//opr short for operation
...
nowAtLine1 = !nowAtLine1;	//switch line
int* curLine, *prevLine;
curLine = nowAtLine1 ? oprCountLine1 : oprCountLine2;
prevLine = !nowAtLine1 ? oprCountLine1 : oprCountLine2;
```

