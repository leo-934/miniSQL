#pragma once
#include <vector>
#include <fstream>
#include "Def.h"
class DataBlock {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="DataBlock"/> class.
	/// </summary>
	/// <param name="_catalog">传入一个vector代表记录的类型</param>
	DataBlock(anyVec _cata);
	
	/// <summary>
	/// 把块读出文件
	/// </summary>
	/// <param name="fp">c语言文件指针</param>
	void fromFile(std::fstream & fs);

	/// <summary>
	/// 把块写入文件
	/// </summary>
	/// <param name="fp">c语言文件指针</param>
	void toFile(std::fstream & fs);


	/// <summary>
	/// 通过在块中的序号得到数据的引用，从0开始数.
	/// </summary>
	/// <param name="num">The number.</param>
	/// <returns></returns>
	anyVec& at(int num);

	/// <summary>
	/// Removes the record.
	/// </summary>
	/// <param name="num">下标，从0开始</param>
	void removeRecord(int num);

	/// <summary>
	/// Adds the record.
	/// </summary>
	/// <param name="recToAdd">The record to add.</param>
	void addRecord(anyVec& recToAdd);
private:
	int recordMax;
	int recordSpace;
	anyVec cata;
	std::vector<anyVec> records;
};
