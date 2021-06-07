// By Wang Jianing and Wang Yitian in ZJU
// Coded in 2021.06
#include <iostream>
#include <memory>
#include <string>
#include <any>

#include "BufferManager.h"
#include "def.h"
int main()
{
    Operation a = Operation::selectRecord;
    std::any b;
    b = Operation::selectRecord;
    std::cout << (Operation::selectRecord ==(*b._Cast<Operation>()));
    return 0;
}