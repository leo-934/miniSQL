#include "interpreter.h"

#include <cstring>

std::string Interpreter::getlowerword(std::string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] > 'A ' && s[i] < 'Z')
		{
			s[i] = s[i] + 32;
		}
	}
	return s;
}

std::string Interpreter::getword(std::string s, int *i)
{
	std::string word;
	int i1, i2;

	while ((s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n') && s[*i] != 0)
	{
		(*i)++;
	}
	i1 = *i;

	if (s[*i] == '(' || s[*i] == ',' || s[*i] == ')')
	{
		(*i)++;
		i2 = *i;
		word = s.substr(i1, i2 - i1);
		return word;
	}

	else if (s[*i] == 39)
	{ // 单引号
		(*i)++;
		while (s[*i] != 39 && s[*i] != 0)
			(*i)++;
		if (s[*i] == 39)
		{
			i1++;
			i2 = *i;
			(*i)++;
			word = s.substr(i1, i2 - i1);
			return word;
		}

		else
		{
			word = "";
			return word;
		}
	}

	else
	{
		while (s[*i] != ' ' && s[*i] != 10 && s[*i] != '(' && s[*i] != ')' && s[*i] != ',' && s[*i] != 0)
			(*i)++;
		i2 = *i;
		if (i1 != i2)
			word = s.substr(i1, i2 - i1);
		else
			word = "";

		return word;
	}
}

Interpreter::Interpreter(std::shared_ptr<CatalogManager> ptr)
{
	catalogManager = ptr;
}

std::shared_ptr<struct Sentence> Interpreter::parseSql(std::string s)
{
	std::string word;
	int i = 0;
	s = getlowerword(s);
	word = getword(s, &i);
	if (strcmp(word.c_str(), "create") == 0)
	{
		word = getword(s, &i);

		if (strcmp(word.c_str(), "table") == 0)
		{
			std::shared_ptr<cts> p = std::make_shared<cts>();
			p->op = Operation::createTable;
			std::string tablename = "";
			std::string primarykey = "";
			word = getword(s, &i);
			if (!word.empty())
			{
				tablename = word;
				p->tableName = tablename;
			}
			else
			{
				// tablename lacked
				throw std::runtime_error("Error");
			}

			word = getword(s, &i);
			if (word.empty() || strcmp(word.c_str(), "(") != 0)
			{
				throw std::runtime_error("Error");
			}

			else
			{
				word = getword(s, &i);
				while (!word.empty() && strcmp(word.c_str(), "primary") != 0 && strcmp(word.c_str(), ")") != 0)
				{
					std::string attrName = word;
					catalog type;
					bool ifunique = false;
					word = getword(s, &i);
					if (strcmp(word.c_str(), "int") == 0)
						type = catalog::INT;
					else if (strcmp(word.c_str(), "float") == 0)
						type = catalog::FLOAT;
					else if (strcmp(word.c_str(), "char") == 0)
					{
						word = getword(s, &i);
						if (strcmp(word.c_str(), "("))
						{
							// illeagel type
							throw std::runtime_error("Error");
						}
						int len = std::stoi(getword(s, &i));
						word = getword(s, &i);
						if (strcmp(word.c_str(), ")"))
						{
							// illegel type
							throw std::runtime_error("Error");
						}
						type = catalog::CHAR;
						p->attrLenForChar.insert(std::pair<std::string, int>(attrName, len));
					}

					else
					{
						// no type
						throw std::runtime_error("Error");
					}

					word = getword(s, &i);
					if (strcmp(word.c_str(), "unique") == 0)
					{
						ifunique = true;
						p->uniqueKeys.push_back(attrName);
						word = getword(s, &i);
					}
					if (strcmp(word.c_str(), "primary") == 0)
					{
						p->primaryKey = attrName;
						getword(s, &i);
						word = getword(s, &i);
					}
					p->attrCata.insert(std::pair<std::string, catalog>(attrName, type));
					p->originalAttr.push_back(attrName);

					if (strcmp(word.c_str(), ",") != 0)
					{
						if (strcmp(word.c_str(), ")") != 0)
						{
							// , error
							throw std::runtime_error("Error");
						}
						else
							break;
					}

					word = getword(s, &i);
				}

				if (strcmp(word.c_str(), "primary") == 0)
				{
					word = getword(s, &i);
					if (strcmp(word.c_str(), "key") != 0)
					{
						// error
						throw std::runtime_error("Error");
					}

					else
					{
						getword(s, &i);
						word = getword(s, &i);
						p->primaryKey = word;
						getword(s, &i);
					}
				}
			}

			return std::dynamic_pointer_cast<struct Sentence>(p);
		}

		else if (strcmp(word.c_str(), "index") == 0)
		{
			std::shared_ptr<cis> p = std::make_shared<cis>();
			p->op = Operation::createIndex;
			std::string indexname = "";
			std::string tablename = "";
			std::string attrname = "";
			word = getword(s, &i);
			if (!word.empty())
				indexname = word;
			else
			{
				// error
				throw std::runtime_error("Error");
			}

			word = getword(s, &i);
			if (strcmp(word.c_str(), "on") != 0)
				throw std::runtime_error("Error");
			word = getword(s, &i);
			if (word.empty())
				throw std::runtime_error("Error");
			tablename = word;
			word = getword(s, &i);
			if (strcmp(word.c_str(), "(") != 0)
				throw std::runtime_error("Error");
			word = getword(s, &i);
			if (word.empty())
				throw std::runtime_error("Error");
			attrname = word;
			word = getword(s, &i);
			if (strcmp(word.c_str(), ")") != 0)
				throw std::runtime_error("Error");
			p->indexName = indexname;
			p->tableName = tablename;
			p->attrName = attrname;
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}

		throw std::runtime_error("Error");
	}

	else if (strcmp(word.c_str(), "drop") == 0)
	{
		word = getword(s, &i);

		if (strcmp(word.c_str(), "table") == 0)
		{
			if (!word.empty())
			{
				std::shared_ptr<dts> p = std::make_shared<dts>();
				p->op = Operation::dropTable;
				word = getword(s, &i);
				p->tableName = word;
				return std::dynamic_pointer_cast<struct Sentence>(p);
			}
			else
			{
				// error
				throw std::runtime_error("Error");
			}
		}

		else if (strcmp(word.c_str(), "index") == 0)
		{
			std::shared_ptr<dis> p = std::make_shared<dis>();
			;
			p->op = Operation::dropIndex;
			std::string indexname = "";
			std::string tablename = "";
			word = getword(s, &i);
			if (!word.empty())
			{
				indexname = word;
			}
			else
			{
				// error
				throw std::runtime_error("Error");
			}
			word = getword(s, &i);
			// if (strcmp(word.c_str(), "on") != 0){
			//	//error
			//	throw std::runtime_error("Error");
			// }
			/*word = getword(s,&i);
			if(!word.empty()) tablename = word;*/
			/*p->tableName = tablename;*/
			p->indexName = indexname;
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}

		else
		{
			throw std::runtime_error("Error");
		}
		throw std::runtime_error("Error");
	}

	else if (strcmp(word.c_str(), "select") == 0)
	{
		std::shared_ptr<srs> p = std::make_shared<srs>();
		p->op = Operation::selectRecord;
		std::string tablename = "";
		struct condition *c = new condition;
		word = getword(s, &i);
		if (strcmp(word.c_str(), "*") != 0)
		{
			while (strcmp(word.c_str(), "from") != 0)
			{
				c->attrName = word;
				c->value = NULL;
				p->conditions.push_back(*c);
				word = getword(s, &i);
			}
		}
		else
			word = getword(s, &i);
		if (strcmp(word.c_str(), "from") != 0)
		{
			// error
			throw std::runtime_error("Error");
		}

		word = getword(s, &i);
		if (!word.empty())
			tablename = word;
		else
		{
			// error
			throw std::runtime_error("Error");
		}
		word = getword(s, &i);
		if (word.empty())
		{
			if (p->conditions.size() == 0)
			{
				p->tableName = tablename;
				p->conditions.resize(0);

				return std::dynamic_pointer_cast<struct Sentence>(p);
			}
			else
			{
				p->tableName = tablename;
				return std::dynamic_pointer_cast<struct Sentence>(p);
			}
		}
		else if (strcmp(word.c_str(), "where") == 0)
		{
			std::string attrname = "";
			std::any value = "";
			comparison comp;
			word = getword(s, &i);
			while (1)
			{
				if (word.empty())
					throw std::runtime_error("Error");
				attrname = word;
				word = getword(s, &i);
				if (strcmp(word.c_str(), "<") == 0)
					comp = comparison::low;
				else if (strcmp(word.c_str(), "<=") == 0)
					comp = comparison::lowOrEqual;
				else if (strcmp(word.c_str(), "=") == 0)
					comp = comparison::equal;
				else if (strcmp(word.c_str(), ">=") == 0)
					comp = comparison::EqualOrHigh;
				else if (strcmp(word.c_str(), ">") == 0)
					comp = comparison::high;
				else if (strcmp(word.c_str(), "<>") == 0)
					comp = comparison::notEqual;
				else
					throw std::runtime_error("Error");
				word = getword(s, &i);
				auto cata = catalogManager->getCataByAttrName(tablename, attrname);
				if (cata == catalog::INT)
				{
					value = std::stoi(word);
				}
				else if (cata == catalog::FLOAT)
				{
					value = std::stof(word);
				}
				else
				{
					value = word;
				}
				if (word.empty())
					throw std::runtime_error("Error");
				word = getword(s, &i);
				struct condition *c = new condition;
				c->attrName = attrname;
				c->comp = comp;
				c->cata = cata;
				c->value = value;
				p->tableName = tablename;
				p->conditions.push_back(*c);
				if (word.empty())
					break;
				if (strcmp(word.c_str(), "and") != 0)
					throw std::runtime_error("Error");
				word = getword(s, &i);
			}
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
	}

	else if (strcmp(word.c_str(), "delete") == 0)
	{
		std::shared_ptr<drs> p = std::make_shared<drs>();
		p->op = Operation::deleteRecord;
		std::string tablename = "";
		word = getword(s, &i);
		if (strcmp(word.c_str(), "from") != 0)
		{
			// error
			throw std::runtime_error("Error");
		}
		word = getword(s, &i);
		if (!word.empty())
			tablename = word;
		else
		{
			// error
			throw std::runtime_error("Error");
		}

		word = getword(s, &i);
		if (word.empty())
		{
			// no condition
			p->tableName = tablename;
			p->conditions.resize(0);
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}

		else if (strcmp(word.c_str(), "where") == 0)
		{
			std::string attrname = "";
			std::any value = "";
			comparison comp;
			word = getword(s, &i);
			while (1)
			{
				if (word.empty())
					throw std::runtime_error("Error");
				attrname = word;
				word = getword(s, &i);
				if (strcmp(word.c_str(), "<") == 0)
					comp = comparison::low;
				else if (strcmp(word.c_str(), "<=") == 0)
					comp = comparison::lowOrEqual;
				else if (strcmp(word.c_str(), "=") == 0)
					comp = comparison::equal;
				else if (strcmp(word.c_str(), ">=") == 0)
					comp = comparison::EqualOrHigh;
				else if (strcmp(word.c_str(), ">") == 0)
					comp = comparison::high;
				else if (strcmp(word.c_str(), "<>") == 0)
					comp = comparison::notEqual;
				else
					throw std::runtime_error("Error");

				word = getword(s, &i);
				if (word.empty())
					throw std::runtime_error("Error");
				auto cata = catalogManager->getCataByAttrName(tablename, attrname);
				if (cata == catalog::INT)
				{
					value = std::stoi(word);
				}
				else if (cata == catalog::FLOAT)
				{
					value = std::stof(word);
				}
				else
				{
					value = word;
				}
				word = getword(s, &i);
				struct condition *c = new condition;
				c->attrName = attrname;
				c->comp = comp;
				c->cata = cata;
				c->value = value;
				p->tableName = tablename;
				p->conditions.push_back(*c);
				if (word.empty())
					break;
				if (strcmp(word.c_str(), "and") != 0)
					throw std::runtime_error("Error");
				word = getword(s, &i);
			}
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		throw std::runtime_error("Error");
	}

	else if (strcmp(word.c_str(), "insert") == 0)
	{
		std::shared_ptr<irs> p = std::make_shared<irs>();
		p->op = Operation::insertRecord;
		std::string tablename = "";
		word = getword(s, &i);
		if (strcmp(word.c_str(), "into") != 0)
			throw std::runtime_error("Error");
		word = getword(s, &i);
		if (word.empty())
			throw std::runtime_error("Error");
		tablename = word;
		word = getword(s, &i);
		if (strcmp(word.c_str(), "values") != 0)
			throw std::runtime_error("Error");
		word = getword(s, &i);
		if (strcmp(word.c_str(), "(") != 0)
			throw std::runtime_error("Error");
		word = getword(s, &i);
		int j = 0;
		while (!word.empty() && strcmp(word.c_str(), ")") != 0)
		{
			auto attrs = catalogManager->getOriginalAttrNames(tablename);
			auto cata = catalogManager->getCataByAttrName(tablename, attrs[j]);
			j++;
			if (cata == catalog::INT)
			{
				p->values.push_back(std::stoi(word));
			}
			else if (cata == catalog::FLOAT)
			{
				p->values.push_back(std::stof(word));
			}
			else
			{
				p->values.push_back(word);
			}
			word = getword(s, &i);
			if (strcmp(word.c_str(), ",") == 0)
				word = getword(s, &i);
		}
		if (strcmp(word.c_str(), ")") != 0)
			throw std::runtime_error("Error");
		p->tableName = tablename;
		return std::dynamic_pointer_cast<struct Sentence>(p);
	}

	else if (strcmp(word.c_str(), "quit") == 0)
	{
		auto p = std::make_shared<QuitSentence>();
		p->op = Operation::quit;
		return p;
	}

	else if (strcmp(word.c_str(), "execfile") == 0)
	{
		std::shared_ptr<efs> p = std::make_shared<efs>();
		p->op = Operation::execFile;
		p->filePath = getword(s, &i);
		return std::dynamic_pointer_cast<struct Sentence>(p);
	}
}
