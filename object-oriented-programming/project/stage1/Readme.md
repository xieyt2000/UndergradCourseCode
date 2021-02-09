# 数据库 #

----------

## 开发环境 ##

在Windows 10下使用VisualStudio 2019编写和测试。

需要说明：VS 2019支持的最低C++标准为C++14，但本项目只使用了C++11标准的功能，可以用C++11标准编译和运行。

由于设备所限，未在iOS或Linux系统下测试。

## 功能说明 ##

### 1. 结构 ###

从底层向上分别为*Column*, *Table*, *Database*, *ourSQL*四级，均为组合(Has-a)关系。

### 2. *Column*类 ###

*Column*类是本项目中存储数据的最小单元。所有数据均用`string`类型存储在`vector<string> val`中。为了标识数据类型，定义枚举`TYPE`，并在每个`Column`对象中用该枚举类型的成员变量`type`来表示这一列的数据类型。此外，用一个`string`类的成员对象`name`表示这一列的名称，用一个`bool`类型的成员变量`notNull`表示非空属性，用一个`unsigned int`类型的成员变量`width`表示显示宽度。

有若干成员函数作为接口实现数据的插入、修改和取出（与*Table*的功能相对应），以及类型的查询等。请自行查阅代码和注释，在此不赘述。

在*Column.h*和*Column.cpp*中还定义了几个需用的函数，以及表示空值的`string _NULL`。

### 3. *Table*类 ###

*Table*类实现数据表的功能。通过`map<string, Column> col`实现列名到列对象的映射；通过`vector<string> colName`存储列名，以确保列的顺序与创建顺序一致；用`int primaryIndex`表示主键所在的列在`colName`中的下标。

构造函数接受一个`string`参数，为列的参数列表。通过`istringstream`解析各列的名称、类型、属性，构造合适的列加入`col`，并把名称加入`colName`中。

按需求，*Table*类有若干接口，实现数据的插入、修改、删除和查询及列的查询，其中调用*Column*的对应接口。需要处理`WHERE`子句的，通过`doClasue`、`doClauseNoOR`、`doClauseSIMPLE`、`simpleClause`四个函数依次进行，前三个实现子句的拆分解析，第四个实现简单比较句的拆分；对应逻辑运算符和比较运算符的优先级，即 比较运算符 > AND > OR 。

这里如果需要新增其他运算符，可以写成相似的函数，按优先级顺序加入处理队列中。

### 4. *Database*类 ###

*Database*是本项目中的数据库类，其中的成员变量有`name`（数据库名，类型为`string` ）、`tabName`（表格名数组，类型为`vector<string>`）、`tab` (表格容器，类型为`map<string, Table>`），均为私有成员。私有成员函数有`showTab`（列出表名）、`create`（创建表）、 `drop`（删除表）等。接口只有`work`（接受一行针对数据库内成员的命令）。

`work`函数的基本思想是使用`istringstream`对命令语句进行分割处理，得到多个`string`类型变量，将在下面一一解释。`cmd1`存储的是命令类型（如"CREATE"），`cmd2`与`whr`存储的是可能存在的命令修饰语（如TABLE、FROM)。因为这些单词是大小写不敏感的，所以一律转成大写进行判断。`tmpName`是表名，通过`tab`访问特定的表格。`tmpClause`、`tmpAttr`与`tmpVal`则是一串语句，是传入`Table`类成员函数的字符串参数，通常内容为条件语句、属性类型与各列赋值，在不同命令下的含义稍有不同，基本与名称一致。本过程中若出现非法操作则会抛出一个`runtime_error`并且标明错误类型。修改表格的具体操作均在`Table`类中实现。

其余函数均只为实现一个相对简单的功能，请自行查阅代码和注释，在此不赘述。

### 5. *ourSQL*类和*main.cpp* ###

*ourSQL*是本项目中负责输入输出的最外层的类，所有对*Database* 的操作都在这一级完成。其成员变量有`db`（数据库容器，类型为`map<string, Database>`，建立数据库名到数据库对象的映射）、`dbName`（数据库名数组，类型为`vector<string>`，用于数据库名的排序）、`activeDB`（标示正在作用的数据库，类型为`string`），均为私有成员。私有成员函数有`showDB()`(用来列出数据库名)。接口只有`work()`，调用后即接管输入和输出，故*main.cpp*中不含其他任何代码。

`work()`函数的基本思想是使用`istringstream`对命令语句进行分割处理，得到多个`string`类型变量。`cmd1`、`cmd2`依次用于存储命令的两个部分，因为这些关键词是大小写不敏感的，所以一律转成大写进行判断。`tmpName`存储的是可能存在的要操作的数据库名，然后通过`db`访问特定的数据库。若读取到的不是这里能够处理的命令，若`activeDB`存在，则将这条命令用`activeDB.work()`（见上一部分）处理；若`activeDB`不存在，抛出`runtime_error`。具体的操作请自行参阅代码和注释，在此不做赘述。

----------
祝接盘的同学们码运昌隆！

最后修改时间
5/5/2019 7:03:55 PM 