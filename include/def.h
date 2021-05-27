#pragma once
#include <string>
#include <vector>
#include <memory>
#include <any>
using anyVectorPtr = std::shared_ptr<std::vector<std::any> >;
enum class operation {
	createTable,
	deleteTable,
	createIndex,
	deleteIndex,
	selectRecord,
	insertRecord,
	deleteRecord,
	quit
};
enum class comparison {
	low,
	lowOrEqual,
	equal,
	EqualOrHigh,
	high,
};