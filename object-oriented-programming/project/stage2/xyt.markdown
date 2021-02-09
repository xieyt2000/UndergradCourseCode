##附加功能：Date Time##

实现附加功能时间变量类型。支持三种类型的变量：DATE TIME DATETIME。DATE格式为a-xx-xx（年-月-日），TIME格式为a:xx:xx（时-分-秒），DATETIME格式为a-xx-xx|xx:xx:xx（年-月-日|时-分-秒），其中a表示任何合理数字（不能超过int范围），x表示一位合理数字。三种类型的有效范围和平时使用的习惯符合，月必须是01-12，日需按照月确定（支持闰年判定），分和秒为0-59，DATETIME的时为0-23。接受到不合规的数据类型时会提示错误，设为默认“零值”，DATE为2000-01-01，TIME为00:00:00。支持第一阶段各语句和whereclause，操作方法与INT等常规变量类型相同。接受ADDDATE（d，n）和ADDTIME（t，n）函数，d为DATE，n为DATETIME，t为TIME，输入格式与上文相同。

Date和Time类的实现方式类似。私有成员年月日（时分秒）数据，并存储一个书写形式的字符串方便输出。公有成员方面重载了比较运算符以支持whereclause，有addDate(addTime)函数支持日期时间相加，genstr函数生成书写形式字符串，友元有输出用流运算符和DATETIME类。DATETIME和这两类之间是组合的关系，也有与它们类似的公有函数，不再赘述。

对原程序的修改主要是在Attribute中增加了对应变量类型，在Value中增加了三种新类型的构造接口，在sql语句分析中使其能够识别新类型关键字。因为原代码的架构较好，所以未作过多修改也未删除原来任何一条语句，保证第一阶段内容不受任何影响。

-------------

##附加功能：数字函数##
实现的数字函数有ABS, CEIL, FLOOR, PI, POW, MOD, SIGN, SQRT, RADIANS, LOG10十种，均支持助教提供的reference中的样例。操作方法为SELECT MATHFUNCTION，其中MATHFUNCTION表示数字函数。

实现方法为新编写数学函数，令sql包含它们的声明。修改sqlSelect，增加判断数学函数的步骤，如果判断为数学函数则进入新函数处理，不进行Table构建等常规Select步骤。判断条件为输入语句中没有"from"，保证不会对其他语句有任何影响。