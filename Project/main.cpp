#include <iostream>
#include <memory>
#include <string>
#include <any>

#include "BufferManager.h"
#include "def.h"
int main()
{
    operation a = operation::selectRecord;
    std::any b;
    b = operation::selectRecord;
    std::cout << (operation::selectRecord ==(*b._Cast<operation>()));
    return 0;
}