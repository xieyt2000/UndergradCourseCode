# report



实验所用数据流分析算法如下：

|                   | Null Check              |
| ----------------- | ----------------------- |
| Domain            | Sets of variables       |
| Direction         | Forward                 |
| Transfer function | $(x-def_b)\cup check_b$ |
| Boundary          | OUT[Entry] = {}         |
| Meet              | $\cap$                  |
| Initialize        | OUT[B] = U              |

$def_b$ 为新定义/赋值的变量，$check_b$为本块进行 `NULL_CHECK` 的变量

数据流分析算法的实现与第一次实验类似，注意需要额外检查本 `Quad` 的 `NULL_CHECK` 是否冗余

新加入清楚冗余的操作，`postprocess` 时对冗余块调用 `QuadIterator.remove()` 即可

