#include "..\include\Def.h"
catalog judger::getCata()
{
	return cata;
}
judger::judger(condition cond)
{
	cata = cond.cata;
	c = cond;
	if (cond.cata == catalog::INT) {
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() < *cond.value._Cast<int>(); };
		else if(cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() <= *cond.value._Cast<int>(); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() == *cond.value._Cast<int>(); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() >= *cond.value._Cast<int>(); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() > *cond.value._Cast<int>(); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<int>() != *cond.value._Cast<int>(); };
	}
	else if (cond.cata == catalog::CHAR) {
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() < *cond.value._Cast<std::string>(); };
		else if (cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() <= *cond.value._Cast<std::string>(); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() == *cond.value._Cast<std::string>(); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() >= *cond.value._Cast<std::string>(); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() > *cond.value._Cast<std::string>(); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<std::string>() != *cond.value._Cast<std::string>(); };
	}
	else {
		if (cond.comp == comparison::low)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() < *cond.value._Cast<float>(); };
		else if (cond.comp == comparison::lowOrEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() <= *cond.value._Cast<float>(); };
		else if (cond.comp == comparison::equal)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() == *cond.value._Cast<float>(); };
		else if (cond.comp == comparison::EqualOrHigh)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() >= *cond.value._Cast<float>(); };
		else if (cond.comp == comparison::high)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() > *cond.value._Cast<float>(); };
		else if (cond.comp == comparison::notEqual)
			func = [cond](std::any attrValue)->bool {return *attrValue._Cast<float>() != *cond.value._Cast<float>(); };
	}
}

bool judger::operator()(std::any attrValue)
{
	if (attrValue.type() ==typeid(int)) {
		int a = *attrValue._Cast<int>();
		int b = *c.value._Cast<int>();
	}
	return func(attrValue);
}

Operation Sentence::getOp()
{
	return op;
}
