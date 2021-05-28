#pragma once
#include "def.h"
class Interpreter {
private:

public:
	/// <summary>
	/// Parses the specified sentence.
	/// </summary>
	/// <param name="sentence">The sentence.</param>
	/// <returns>
	/// 返回一个vector指针，vector中类型为any。
	/// 若为create table语句，则格式为
	/// enum operation+属性个数(int)+多个[属性名(string)+enum catalog+n(int)(若为CHAR)]+primarykey(string)(如果有)+unique
	/// 若为drop table语句，则格式为
	/// enum operatin+表名(string)
	/// 若为create index语句，则格式为
	/// enum operation+索引名(string)+表名(string)+列名(string)
	/// 若为drop index语句，则格式为
	/// enum operation+索引名(string)
	/// 若为select record语句，则格式为
	/// enum operation+表名+条件个数+多个struct condition
	/// 若为insert record语句，则格式为
	/// enum operation+表名(string)+多个[值（类型与对应属性相同）]
	/// 若为delete record语句，则格式为
	/// enum operation+表名(string)条件个数+多个struct condition
	/// 若为quit，则只有一个enum operation
	/// </returns>
	anyVecPtr parse(std::string sentence);
};