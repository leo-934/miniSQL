#pragma once
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <functional>
using anyVecPtr = std::shared_ptr<std::vector<std::any> >;

enum class operation {//代表一个语句的操作类型
	createTable,
	dropTable,
	createIndex,
	dropIndex,
	selectRecord,
	insertRecord,
	deleteRecord,
	quit
};
enum class comparison {//代表一个where条件的比较类型
	low,
	lowOrEqual,
	equal,
	EqualOrHigh,
	high,
};
enum class catalog {//代表一个属性的类型
	INT,
	CHAR,
	FLOAT
};
struct condition {//代表一个where条件
	std::string attrName;//属性名
	catalog cata;//属性的类型
	comparison comp;//比较类型
	std::any value;//比较值
};
class judge {//用于判断一个where条件的函数对象，构造函数传入一个condition，可以直接调用。
private:
	catalog cata;
	std::function<bool(std::any)> func;
public:
	catalog getCata();
	judge(condition cond);
	bool operator()(std::any);
};
