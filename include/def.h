#pragma once
#include <string>
#include <vector>
#include <memory>
#include <any>
#include <functional>
#include <map>
using anyVec = std::vector<std::any>;
using anyVecPtr = std::shared_ptr<std::vector<std::any> >;
using int64 = unsigned long long;
using byte = char;
const int blockSpace = 4096;
const int blockHeadSpace = 4;
const int floatSpace = 4;
const int intSpace = 4;
const int charSpace = 1;
const char recordValid = 1;
const char recordInvalid = 0;
enum class Operation {//代表一个语句的操作类型
	createTable,
	dropTable,
	createIndex,
	dropIndex,
	selectRecord,
	insertRecord,
	deleteRecord,
	execFile, 
	quit
};


enum class comparison {
	low,
	lowOrEqual,
	equal,
	EqualOrHigh,
	high,
	notEqual
};
enum class catalog {//代表一个属性的类型
	INT,
	CHAR,
	FLOAT
};
struct condition {//代表一个where条件er                                                                                                                                                                                                                                                                                                                                      
	std::string attrName;//属性名
	catalog cata;//属性的类型
	comparison comp;//比较类型
	std::any value;//比较值
};

//这是一个基类，下面几个是派生类，分别代表九种语句
//这些struct用来作为interpreter的parseSql函数的返回值
struct Sentence {
	Operation op;
	virtual Operation getOp();
};
typedef struct CreateTableSentence :public Sentence{
	int attrNum;
	std::string tableName;
	std::vector<std::string> originalAttr;
	std::map<std::string,catalog> attrCata;
	std::map<std::string, int> attrLenForChar;
	std::string primaryKey;//若没有，置为空字符串
	std::vector<std::string> uniqueKeys;//若没有，size置为0
}cts;
typedef struct DropTableSentence :public Sentence {
	std::string tableName;
}dts;
typedef struct CreateIndexSentence :public Sentence {
	std::string indexName;
	std::string tableName;
	std::string attrName;
}cis;
typedef struct DropIndexSentence :public Sentence {
	std::string indexName;
	std::string tableName;
}dis;
typedef struct SelectRecordSentence :public Sentence {
	std::string tableName;
	std::vector<condition> conditions;
}srs;
typedef struct InsertRecordSentence :public Sentence {
	std::string tableName;
	std::vector<std::any> values;
}irs;
typedef struct DeleteRecordSentence :public Sentence {
	std::string tableName;
	std::vector<condition> conditions;
}drs;
typedef struct ExecFileSentence :public Sentence {
	std::string filePath;
}efs;
typedef struct QuitSentence :public Sentence {

}qs;




class judger {//用于判断一个where条件的函数对象，构造函数传入一个condition，可以直接调用。
private:
	catalog cata;
	condition c;
	std::function<bool(std::any)> func;
public:
	catalog getCata();
	judger(condition cond);
	bool operator()(std::any);
};
