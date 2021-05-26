#include <iostream>
#include <memory>
#include <string>

#include "BufferManager.h"

int main()
{
    auto test = std::make_shared<BufferManager>();
    std::cout << "Hello Sql!\n";
    std::cout << test->test();
    return 0;
}