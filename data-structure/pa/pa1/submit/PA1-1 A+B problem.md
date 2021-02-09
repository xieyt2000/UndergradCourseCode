# PA1-1 A+B problem

## 数据结构与算法

本题仅使用数组，未使用特殊的数据结构，算法为压位算法+竖式乘法。压位压八位，为方便计算，将压位的数字倒置（即高位放在后面，低位放在前面）。竖式乘法即和竖式计算方式相同，每一位之间均互相相乘，然后相加，如有必要则进行进位。

## 复杂度分析

显然，算法仅使用一位数组，空间复杂度为$ O(n) $。时间复杂度方面，输入、压位和输出复杂度均为$ O(n) $，乘法时间复杂度为$ O(n^2) $，总体时间复杂度为$ O(n^2) $ 。 按理来说$ O(n^2) $的算法不足以通过该题，但是此算法常数很小，鉴于此题数据规模不是很大，所以效率很高。

## 完成过程问题

最初，我参考<https://en.wikipedia.org/wiki/Karatsuba_algorithm>尝试使用Karatsuba算法，该算法时间复杂度为$ O(n^{\log_23})$ ，理论上可以通过测试。但是该算法需要进行多次大数加法，常数过大，提交后TLE，放弃该算法。

然后我参考<http://numbers.computation.free.fr/Constants/Algorithms/fft.html>使用快速傅里叶变换（FFT）。时间复杂度为$ O(n\log_{}n) $，然而和Karatsuba类似，常数过大，放弃。

最后我询问朱书琪，使用了压位算法。第一次90% judge的worst case有512ms，很可能无法通过最后两个点。然后我咨询堵君懿进行优化，保证不会`unsigned long long`越界的情况下最后进行进位。

计算过程中保证不会越界代码如下

```c++
if (output[i + j] > MAX_UNSIGNED_LONG_LONG)
			{
				output[i + j + 1] += output[i + j] / (MAX_VALUE_PER_DIGIT + 1);
				output[i + j] %= MAX_VALUE_PER_DIGIT + 1;
			}
```

最后进位代码如下

```c++
for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (output[i] > MAX_VALUE_PER_DIGIT)
		{
			output[i + 1] += output[i] / (MAX_VALUE_PER_DIGIT + 1);
			output[i] %= MAX_VALUE_PER_DIGIT + 1;
		}
	}
```
