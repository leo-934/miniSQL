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
	/// a shared pointer to a struct which derives from struct sentence.
	/// Look at Def.h to see how to generate it.
	/// </returns>
	std::shared_ptr<Sentence> parseSql(std::string sentence);
};