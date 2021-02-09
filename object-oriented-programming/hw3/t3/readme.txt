各处错误对应的修改均在源代码中以注释标号的方式给出
错误1   IntegerWrapper(double *size)
	
	: Shape(size) {}
冗余语句，作用不明，且Rectangle类缺少构造函数      
修改：直接删除原语句，添加构造函数Rectangle(double *size)
 : Shape(size) {}

错误2    main函数中将private继承派生类指针进行向上类型转换，操作非法，而且Square需要调用Rectangle的angles函数。同时private继承无法反应Shape和它的具体化之间的关系，不符合oop的思想，实际应用情景也很少，还会导致错误3即使修改后Square也无法访问size等许多问题。
修改：将继承关系全部改为public继承

错误3    Rectangle、Circle、Square求面积时直接使用Shape的private成员size，没有访问权限。同时基类也缺少访问size的接口，派生类无法实现求面积的功能。
修改：给shape添加public的接口double getsize(int index)，派生类求面积时通过此接口访问size的各个元素。

错误4    构造Shape的各派生类时调用了本地纯虚函数type（）。
修改：Shape类的构造函数不再调用type()，转而在各派生类的构造函数给id加入type，因此需要给shape类设定一个addtype的接口，同时考虑到Square这个派生类的派生类，还需设置一个replacetype的接口，替换掉原来的type。

错误5    Shape以及各派生类未定义析构函数导致size*泄漏
修改：为Shape添加析构函数，根据id判断类型决定使用delete[]或delete
注：这里也可以将size*变为protected成员，在派生类的析构函数释放size*的内存。这种改法可以封装基类，不允许再改动基类。两种方法的可拓展性相似，但是改为protected成员对原类的改变过大，故不采用。
