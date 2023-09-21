#include "def.h"
catalog judger::getCata()
{
	return cata;
}
judger::judger(condition cond)
{
	cata = cond.cata;
	c = cond;
	if (cond.cata == catalog::INT)
	{
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) < std::any_cast<int>(cond.value); };
		else if (cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) <= std::any_cast<int>(cond.value); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) == std::any_cast<int>(cond.value); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) >= std::any_cast<int>(cond.value); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) > std::any_cast<int>(cond.value); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<int>(attrValue) != std::any_cast<int>(cond.value); };
	}
	else if (cond.cata == catalog::CHAR)
	{
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) < std::any_cast<std::string>(cond.value); };
		else if (cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) <= std::any_cast<std::string>(cond.value); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) == std::any_cast<std::string>(cond.value); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) >= std::any_cast<std::string>(cond.value); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) > std::any_cast<std::string>(cond.value); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<std::string>(attrValue) != std::any_cast<std::string>(cond.value); };
	}
	else
	{
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) < std::any_cast<float>(cond.value); };
		else if (cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) <= std::any_cast<float>(cond.value); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) == std::any_cast<float>(cond.value); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) >= std::any_cast<float>(cond.value); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) > std::any_cast<float>(cond.value); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue) -> bool
			{ return std::any_cast<float>(attrValue) != std::any_cast<float>(cond.value); };
	}
}

bool judger::operator()(std::any attrValue)
{
	if (attrValue.type() == typeid(int))
	{
		int a = std::any_cast<int>(attrValue);
		int b = std::any_cast<int>(c.value);
	}
	return func(attrValue);
}

Operation Sentence::getOp()
{
	return op;
}
