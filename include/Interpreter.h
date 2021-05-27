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
	/// </returns>
	/// 若为create
	anyVectorPtr parse(std::string sentence);
};