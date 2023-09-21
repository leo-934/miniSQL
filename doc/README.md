# **MiniSQL**

## **1. MiniSQL系统概述**

### **1.1 背景**

#### **1.1.1 编写目的**

设计并实现一个精简型单用户SQL引擎（DBMS）MiniSQL，允许用户通过字符界面输入SQL语句实现表的建立/删除；索引的建立/删除以及表记录的插入/删除/查找。
通过对MiniSQL的设计与实现，提高系统编程能力，加深对数据库系统原理的理解。

#### **1.1.2 项目背景**

随着数据库系统课程的推进，在学习一定数据库系统知识的基础上，需要一次基于数据库系统的项目实践来加深知识的理解与掌握。精简型单用户SQL引擎MiniSQL正满足了这一需求，符合本科学生知识储备的同时包含了SQL引擎的基本功能。

### **1.2 功能描述**

1. **数据类型**

支持三种基本数据类型：`int`，`char(n)`，`float`，其中`char(n)`满足 1<=n<=255。

2. **表定义**

一个表最多可以定义32个属性，各属性可以指定是否为 unique ；支持单属性的主键定义。

创建表语法如下：

```sql
create table 表名 (
	列名 类型 ,
	列名 类型 ,
	
	列名 类型 ,
	primary key ( 列名 )
);
```

删除表语法如下：

```sql
drop table 表名 ;
```

3. **索引的建立和删除**

对于表的主属性自动建立B+树索引，对于声明为`unique`的属性可以通过SQL语句由用户指定建立/删除B+树索引（因此，所有的B+树索引都是单属性单值的）。
创建索引语法如下：

```sql
create index 索引名 on 表名 ( 列名 );
```

删除索引语法如下：

```sql
drop index stunameidx;
```

4. **查找记录**

可以通过指定用`and`连接的多个条件进行查询，支持等值查询和区间查询。

选择语法如下：

```sql
select * from 表名 ;
```

或：

```sql
select * from 表名 where 条件 ;
```

其中“条件”具有以下格式：

`列 op 值 and 列 op 值 … and 列 op 值`。

op是算术比较符：

`=`,`<>`,`<`,`>`,`<=`,`>=`;

5. **插入和删除记录**

支持每次一条记录的插入操作；支持每次一条或多条记录的删除操作。

插入记录语法如下：

```sql
insert into 表名 values ( 值1 , 值2 , … , 值n );
```

删除记录语法如下：

```sql
delete from 表名 ;
```

或：

```sql
delete from 表名 where 条件 ;
```

6. **退出MiniSQL系统**

退出语法如下：

```sql
quit;
```

### **1.3 运行环境和配置**

集成开发环境：Windows10 Visual Studio 2019

### **1.4 参考资料**

《数据库系统概念》第六版 机械工业出版社

《C++ Primer》第五版 电子工业出版社

## **2. MiniSQL系统结构设计**

<hr>

### **2.1 总体设计**

<p><img src="D:\ZJU\2021spr_sum\DBS\report\pic1.png"/></p>

### **2.2	Interpreter 模块**

#### **2.2.1 概述**

Interpreter模块直接与用户交互，主要实现以下功能：

1.	程序流程控制，即“启动并初始化 -> ‘接收命令、处理命令、显示命令结果’ -> 循环 退出”流程。

2.	接收并解释用户输入的命令，生成命令的内部数据结构表示，同时检查命令的语法正确性和语义正确性，对正确的命令调用API层提供的函数执行并显示执行结果，对不正确的命令显示错误信息。

#### **2.2.2 结构与接口**

```Cpp
// 获得需要处理的字符串
+private std::string getword(std::string s, int *i);
// 将字符串中所有大写字母转化为小写字母
+private std::string getlowerword(std::string s);
// 处理字符串后返回一个指向Sentence类的智能指针
+public std::shared_ptr<Sentence> parseSql(std::string s);
```

### **2.3	API模块**

#### **概述**

API模块是整个系统的核心，其主要功能为提供执行SQL语句的接口，供Interpreter层调用。该接口以Interpreter层解释生成的命令内部表示为输入，根据Catalog Manager提供的信息确定执行规则，并调用Record Manager、Index Manager和Catalog Manager提供的相应接口进行执行，最后返回执行结果给Interpreter模块。

#### **结构与接口**

```Cpp
APP();
// 开始运行数据库，包括登录，调用interpreter解析语句，调用API模块执行语句.
void run();
/// Executes the SQL.
void execSql(std::shared_ptr<Sentence> parseResult);
```

### **2.4	CatalogManager模块**

#### **概述**

Catalog Manager负责管理数据库的所有模式信息，包括：

1.	数据库中所有表的定义信息，包括表的名称、表中字段（列）数、主键、定义在该表上的索引。

2.	表中每个字段的定义信息，包括字段类型、是否唯一等。

3.	数据库中所有索引的定义，包括所属表、索引建立在那个字段上等。

Catalog Manager还必需提供访问及操作上述信息的接口，供Interpreter和API模块使用。

#### **结构与接口**

```Cpp
+public int test();
// Initializes a new instance of the <see cref="CatalogManager"/> class.
+public CatalogManager();
// Closes this instance.
+public void close();
// Gets the attribute's cata.
+public catalog getCataByAttrName(std::string tableName, std::string attrName);
+public anyVec getCataInAnyVec(std::string tableName);
+public std::vector<std::string> getAllTableNames();
+public std::vector<std::string> getAllAttrByTableName(std::string tableName);
+public void createTable(CreateTableSentence sent);
+public void dropTable(std::string tableName);
```

### **2.5	RecordManager模块**

#### **概述**

Record Manager负责管理记录表中数据的数据文件。主要功能为实现数据文件的创建与删除（由表的定义与删除引起）、记录的插入、删除与查找操作，并对外提供相应的接口。其中记录的查找操作要求能够支持不带条件的查找和带一个条件的查找（包括等值查找、不等值查找和区间查找）。

数据文件由一个或多个数据块组成，块大小应与缓冲区块大小相同。一个块中包含一条至多条记录，为简单起见，只要求支持定长记录的存储，且不要求支持记录的跨块存储。

#### **结构与接口**

```Cpp
+public int test();
+public RecordManager(std::shared_ptr<BufferManager> ptr);
// Inserts the record to table.
+public int64 insertRecordToTable(std::string tableName, anyVec values);
// Removes the record from table.
+public std::vector<int64> removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
// Selects the records by address and condition.
+public anyVec selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
```

### **2.6	Indexmanager模块**

#### **概述**

Index Manager负责B+树索引的实现，实现B+树的创建和删除（由索引的定义与删除引起）、等值查找、插入键值、删除键值等操作，并对外提供相应的接口。

B+树中节点大小应与缓冲区的块大小相同，B+树的叉数由节点大小与索引键大小计算得到。

#### **结构与接口**

```Cpp
class IndexManager {
//初始化IndexManager模块并从文件读取数据
+public IndexManager(std::shared_ptr<CatalogManager> _catalogManager);
//关闭时将数据写入文件
+public void close();
//建立B+树并返回根节点指针
+public void* createIndex(std::string indexName, std::string tableName, std::string attrName);
//删除指定表中的指定索引
+public void dropIndex(std::string indexName, std::string tableName);
//删除指定表中的所有索引
+public void dropAllIndex(std::string tableName);
//根据指定索引和指定表向b+树中插入keyvalue对
+public insertToIndex(std::string indexName, std::string tableName, std::any key, int64 value);
//根据条件和指定的表名、索引名获得索引
+public std::vector<int64> selectIndexsByCondition(std::string tableName, std::string indexName, std::vector<condition> cond);
//在指定表中根据指定地址删除索引
+public void removeIndexByAddress(std::string tableName, std::vector<int64> addresses);
//判断指定表中是否有聚集索引
+public bool hasClusteredIndex(std::string tableName);
//返回指定表中的聚集索引
+public std::string getClusteredIndex(std::string tableName);
//判断指定表中是否有非聚集索引
+public bool hasNonClusteredIndex(std::string tableName);
//返回指定表中的非聚集索引
+public std::vector<std::string> getNonClusteredIndex(std::string tableName);
//判断指定表中是否有索引
+public bool hasAnyIndex(std::string tableName);
//返回指定表中的所有索引
+public std::vector<std::string> getAllIndex(std::string tableName);
//在指定表中根据索引名返回属性名
+public std::string getAttrNameByIndexName(std::string indexName, std::string tableName);
//在指定表中根据属性名返回索引名
+public std::string getIndexNameByAttrName(std::string attrName, std::string tableName);
```

### **2.7	BufferManager模块**

#### **概述**

Buffer Manager负责缓冲区的管理，主要功能有：

1.	根据需要，读取指定的数据到系统缓冲区或将缓冲区中的数据写出到文件

2.	实现缓冲区的替换算法，当缓冲区满时选择合适的页进行替换

3.	记录缓冲区中各页的状态，如是否被修改过等

4.	提供缓冲区页的pin功能，及锁定缓冲区的页，不允许替换出去
为提高磁盘I/O操作的效率，缓冲区与文件系统交互的单位是块，块的大小应为文件系统与磁盘交互单位的整数倍，一般可定为4KB或8KB。

#### **结构与接口**

```Cpp
+private int64 getBlockNum(std::string tableName);
// 代理引用buffer,通过修改这个函数可以管理缓冲区
+private DataBlock& refBlockByLabel(std::string tableName, int64 blockSerial);
// 代理插入buffer,通过修改这个函数可以管理缓冲区
+private void insertBlock(std::string tableName, int64 blockSerial, DataBlock d);
+public int test();
// Initializes a new instance of the <see cref="BufferManager"/> class.
+public BufferManager(std::shared_ptr<CatalogManager> ptr);
// Gets the record number.
+public int64 getRecordNum(std::string tableName);
// Inserts the record to table.
+public int64 insertRecordToTable(std::string tableName, anyVec values);
// Gets the record by address.
+public anyVec getRecordByAddress(std::string tableName, int64 addresses);
// Deletes the record by address.
+public void deleteRecordByAddress(std::string tableName, int64 addresses);
// Creates the table.
+public void createTable(std::string tableName);
// Drops the table.
+public void dropTable(std::string tableName);
````

## **3. 测试方案和测试样例**

学在浙大上给出的所有test文件均可单次通过，十万组数据的运行时间约为三分钟。

下面给出1000组数据的详细截图

![1](https://github.com/JianingWang43/miniSQL/blob/main/doc/readmeImages/1.jpg)

测试结果如下

![2](https://github.com/JianingWang43/miniSQL/blob/main/doc/readmeImages/2.jpg)

试图进行查询，结果如下：

![3](https://github.com/JianingWang43/miniSQL/blob/main/doc/readmeImages/3.jpg)

重启程序，再次查询，观察是否能够保存表，结果如下

![4](https://github.com/JianingWang43/miniSQL/blob/main/doc/readmeImages/4.jpg)

总体上来讲，实验结果比较成功。


## **4. 分组与设计分工**

<hr>

### **本组成员**
|  姓名   |   学号  |
| :----: | :----: |
| 王佳宁  |  |
| 王奕天  |  |

### **本组分工**
|  姓名   |  分工  |
| :----: | :----: |
| 王佳宁  | 项目架构设计<br>Interpreter模块<br>API模块<br>CatalogManager模块<br>RecordManager模块<br>BufferManager模块<br>调试<br>报告撰写 |
| 王奕天  | IndexManager&BplusTree模块<br>报告撰写 |

