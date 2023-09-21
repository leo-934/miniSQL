# Design

## 使用的c++98之后的语法和库

std::any		#include <any>

std::shared_ptr		#include <memory>

## 编码规范

- 文件名和类名使用大驼峰命名法
- 变量名和函数名使用小驼峰命名法，缩写如API视为一个单词，全小写
- 指针一律使用shared_ptr
- 一个函数只做一件事，一个类只做一件事，做的事情要和名字完全一样。（比如Interpreter类中解析结束后不在函数末尾调用API，而是返回处理好的结构，因为interpreter只负责解析）
- 禁止using namespace std;
- 包含头文件一律写在文件首，且标准库文件在前，自定义头文件在后
- 函数定义写在源文件

## Class Design

### bufferManager:

- 通过buffermanager内部实现，使得对外部而言，没有块的概念，只有记录的概念

### recordmanager：

- 在buffermanager中维护一个map，key是文件中记录的地址，value是记录的内存地址即指针。所有缓冲区中的记录都有这样的地址，对外提供getblockfromserial接口。

- 为什么不在读取时直接将文件地址转为内存指针？
- 因为这个随着缓冲区替换的进行，这个内存指针可能会失效。但是如果在buffermanager内部实现这个过程，因为文件地址不会失效，所以就可以检验内存地址有效性，如果这个块已经被替换，就再次读入并分配新的地址，存入map）

### Index manager：

- 因为索引不会被替换，且b+树的层序遍历结果只在末尾有变化，所以读入时可以直接转化内存指针。

- 因为索引不会被中途替换，所以在刚开始运行后读入索引后，内存中即存在一颗完整的b+树，控制权将转交给index manager，直到程序关闭写回时，将不会涉及到buffermanager。

### catalog manager：不使用缓冲区



