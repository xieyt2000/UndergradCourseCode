# PA1-2 Graphics

## 数据结构与算法

本题仅使用数组，未使用特殊的数据结构，算法为ToLeftTest+二分查找。读入X、Y轴上的点后先进行排序，因为需保证线段不相交，所以测试线段一定按照该顺序连接。之后进行二分查找，选取当前查找区间的中间线段，用ToLeft测试判断点在直线的哪一侧。ToLeft测试参考<https://blog.csdn.net/qq_27161673/article/details/80024564>，将测试点与测试线段任意一端点连接，逆时针方向叉乘，若结果为正，则代表点在左侧，为负说明在右侧，为0说明在线段上。

## 复杂度分析

显然，算法仅使用一位数组，空间复杂度为$ O(n) $。时间复杂度方面，ToLeft测试复杂度$ O(1) $，m次询问的二分查找复杂度$ O(m\log_{}n) $，排序复杂度$ O(n\log_{}n) $，总体复杂度为$ max(O(n\log_{}n), O(m\log_{}n)) $。

## 完成过程问题

本题我在查询提示中提到的ToLeft测试后，并未遇到什么问题。二分查找时最终选择的是左闭右开区间，若测试点在测试线段右侧，则下界更新为测试线段的下一个，若在左侧则上界更新为测试线段，最后返回下界。代码如下

```c++
int binarySearchTest(long long t_queryX, long long t_queryY)
{
	//interval left close right open
	int low = 0, high = n;
	while (high - low > 0)
	{
		int middle = (high + low) / 2;
		side queryToThisLine = toLeftTest(t_queryX, t_queryY, pointsX[middle], 0, 0, pointsY[middle]);
		if (queryToThisLine == on)
		{
			return (middle + 1);
		}
		else if (queryToThisLine == left)
		{
			high = middle;
		}
		else
		{
			low = middle + 1;
		}
	}
	return low;
}
```

