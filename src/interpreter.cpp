#include "..\include\Interpreter.h"

std::string Interpreter::getlowerword(std::string s) {
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] > 'A ' && s[i] < 'Z')
		{
			s[i] = s[i] + 32;
		}
	}
	return s;
}

std::string Interpreter::getword(std::string s, int *i){
	std::string word;
	int i1, i2;
	
	while ((s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n') && s[*i] != 0) {
		(*i)++;
	}
	i1 = *i;
	
	if (s[*i] == '(' || s[*i] == ',' || s[*i] == ')') {
		(*i)++;
		i2 = *i;
		word = s.substr(i1, i2-i1);
		return word;
	}
	
	else if (s[*i] == 39){ //单引号
		(*i)++;
		while (s[*i] != 39 && s[*i] != 0) (*i)++;
		if (s[*i] == 39) {
			i1++;
			i2 = *i;
			(*i)++;
			word = s.substr(i1, i2-i1);
			return word;
		}
		
		else {
			word = "";
			return word;
		}	
	}
	
	else {
		while (s[*i] != ' ' && s[*i] != 10 && s[*i] != '(' && s[*i] != ')' && s[*i] != ',' && s[*i] != 0)
				(*i)++;
		i2 = *i;
		if (i1 != i2) word = s.substr(i1, i2-i1);
		else word = "";
		
		return word;
	}
}

std::shared_ptr<struct Sentence> Interpreter::parseSql(std::string s){
	std::string word;
	int i = 0;
	s = getlowerword(s);
	word = getword(s, &i);
	if (strcmp(word.c_str(), "create") == 0) {
		word = getword(s, &i);
		
		if (strcmp(word.c_str(), "table") == 0) {
			std::shared_ptr<cts> p=std::make_shared<cts>();
			std::string tablename = "";
			std::string primarykey = "";
			word = getword(s, &i);
			if (!word.empty()) {
				tablename = word;
				p->tableName = tablename;
			}
			else {
				// tablename lacked 
				throw std::exception("Error");
			}
			
			word = getword(s, &i);
			if (word.empty() || strcmp(word.c_str(), "(") != 0) {
				throw std::exception("Error");
			}
			
			else {
				word = getword(s, &i);
				while (!word.empty() && strcmp(word.c_str(), "primary") != 0 && strcmp(word.c_str(), ")") != 0){
					std::string attrName = word;
					catalog type;
					bool ifunique = false;
					word = getword(s, &i);
					if (strcmp(word.c_str(), "int") == 0) type = catalog::INT;
					else if (strcmp(word.c_str(), "float") == 0) type = catalog::FLOAT;
					else if (strcmp(word.c_str(), "char") == 0){
						word = getword(s, &i);
						if (strcmp(word.c_str(), "(")) {
							// illeagel type
							throw std::exception("Error");
						}
						int len = std::stoi(getword(s, &i));
						word = getword(s, &i);
						if (strcmp(word.c_str(), ")")) {
							// illegel type
							throw std::exception("Error");
						}
						type = catalog::CHAR;
						p->attrLenForChar.insert(std::pair<std::string, int>(attrName, len));
					}
					
					else {
						// no type
						throw std::exception("Error");
					}
					
					word = getword(s, &i);
					if (strcmp(word.c_str(), "unique") == 0) {
						ifunique = true;
						p->uniqueKeys.push_back(attrName);
						word = getword(s, &i);
					}
					p->attrCata.insert(std::pair<std::string, catalog>(attrName, type));
					p->originalAttr.push_back(attrName);

					if(strcmp(word.c_str(), ",") != 0) {
						if(strcmp(word.c_str(), ")") != 0){
							// , error
							throw std::exception("Error");
						}
						else break;
					}
					
					word = getword(s, &i);
				}
				
				if (strcmp(word.c_str(), "primary") == 0) {
					word = getword(s, &i);
					if (strcmp(word.c_str(), "key") != 0) {
						// error
						throw std::exception("Error");
					}
					
					else {
						getword(s, &i);
						word = getword(s, &i);
						p->primaryKey = word;
						getword(s, &i);
					}
					
				}
				
			}
			
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		
		else if (strcmp(word.c_str(), "index") == 0){
			std::shared_ptr<cis> p = std::make_shared<cis>();;
			std::string indexname = "";
			std::string tablename = "";
			std::string attrname = "";
			word = getword(s, &i);
			if (!word.empty()) indexname = word;
			else {
				//error
				throw std::exception("Error");
			}
			
			word = getword(s, &i);
			if (strcmp(word.c_str(),"on") != 0)
				throw std::exception("Error");
			word = getword(s,&i);
			if (word.empty())
				throw std::exception("Error");
			tablename = word;
			word = getword(s,&i);
			if (strcmp(word.c_str(),"(") != 0)
				throw std::exception("Error");
			word = getword(s,&i);
			if (word.empty())
				throw std::exception("Error");
			attrname = word;
			word = getword(s,&i);
			if (strcmp(word.c_str(),")") != 0)
				throw std::exception("Error");
			p->indexName = indexname;
			p->tableName = tablename;
			p->attrName = attrname;
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		
		throw std::exception("Error");
	}
	
	else if(strcmp(word.c_str(), "drop") == 0) {
		word = getword(s,&i);
		
		if (strcmp(word.c_str(), "table") == 0) {
			if(!word.empty()){
				std::shared_ptr<dts> p = std::make_shared<dts>();;
				word = getword(s,&i);
				p->tableName = word;
				return std::dynamic_pointer_cast<struct Sentence>(p);
			}
			else {
				//error
				throw std::exception("Error");
			}
		}
		
		else if (strcmp(word.c_str(), "index") == 0) {
			std::shared_ptr<dis> p = std::make_shared<dis>();;
			std::string indexname = "";
			std::string tablename = "";
			word = getword(s,&i);
			if (!word.empty()){
				indexname = word;
			}
			else {
				//error
				throw std::exception("Error");
			}
			word = getword(s,&i);
			if (strcmp(word.c_str(), "on") != 0){
				//error
				throw std::exception("Error");
			}
			word = getword(s,&i);
			if(!word.empty()) tablename = word;
			p->tableName = tablename;
			p->indexName = indexname;
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		
		else {
			throw std::exception("Error");
		}
		throw std::exception("Error");
	}
	
		
	else if(strcmp(word.c_str(), "select") == 0) {
		std::shared_ptr<srs> p = std::make_shared<srs>();;
		std::string tablename = "";
		struct condition* c = (struct condition*)malloc(sizeof(struct condition));
		word = getword(s,&i);
		if (strcmp(word.c_str(), "*") != 0) {
			while (strcmp(word.c_str(), "from") != 0) {
				c->attrName = word;
				c->value = NULL;
				p->conditions.push_back(*c);
				word = getword(s,&i);
			}
		}
		else word = getword(s,&i);
		if (strcmp(word.c_str(), "from") != 0) {
			//error
			throw std::exception("Error");
		}
		
		word = getword(s,&i);
		if(!word.empty()) tablename = word;
		else {
			//error
			throw std::exception("Error");
		}
		word = getword(s,&i);
		if (word.empty()) {
			if (p->conditions.size() == 0) {
				p->tableName = tablename;
				p->conditions.resize(0);
			}
			else {
				p->tableName = tablename;
				return std::dynamic_pointer_cast<struct Sentence>(p);
			}
		}
		else if (strcmp(word.c_str(), "where") == 0) {
			std::string attrname = "";
			std::string value = "";
			comparison comp;
			word = getword(s,&i);
			while(1) {
				if(word.empty()) throw std::exception("Error");
				attrname = word;
				word = getword(s,&i);
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
				else throw std::exception("Error");
				word = getword(s,&i);
				if(word.empty()) throw std::exception("Error");
				word = getword(s,&i);
				struct condition* c = (struct condition*)malloc(sizeof(struct condition));
				c->attrName = attrname;
				c->comp = comp;
				c->value = value;
				p->tableName = tablename;
				p->conditions.push_back(*c); 
				if(word.empty()) break;
				if (strcmp(word.c_str(),"and") != 0)
					throw std::exception("Error");
				word = getword(s,&i);		
			}
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		throw std::exception("Error");
	}
	
	else if(strcmp(word.c_str(), "delete") == 0) {
		std::shared_ptr<drs> p = std::make_shared<drs>();;
		std::string tablename = "";
		word = getword(s,&i);
		if (strcmp(word.c_str(), "from") != 0) {
			//error
			throw std::exception("Error");
		}
		word = getword(s,&i);
		if (!word.empty()) tablename = word;
		else {
			//error
			throw std::exception("Error");
		}
		
		word = getword(s,&i);
		if (word.empty()) {
			// no condition
			p->tableName = tablename;
			p->conditions.resize(0);
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		
		else if (strcmp(word.c_str(), "where") == 0) {
			std::string attrname = "";
			std::string value = "";
			comparison comp;
			word = getword(s,&i);
			while(1) {
					if (word.empty()) throw std::exception("Error");
					attrname = word;
					word = getword(s,&i);
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
					else throw std::exception("Error");
					word = getword(s,&i);
					if (word.empty()) throw std::exception("Error");
					value = word;
					word = getword(s,&i);
					struct condition* c = (struct condition*)malloc(sizeof(struct condition));
					c->attrName = attrname;
					c->comp = comp;
					c->value = value;
					p->tableName = tablename;
					p->conditions.push_back(*c);
					if(word.empty()) break;
					if (strcmp(word.c_str(),"and") != 0)
						throw std::exception("Error");
					word = getword(s,&i);
			}
			return std::dynamic_pointer_cast<struct Sentence>(p);
		}
		throw std::exception("Error");
	}
	
	else if (strcmp(word.c_str(), "insert") == 0) {
		std::shared_ptr<irs> p = std::make_shared<irs>();;
		std::string tablename = "";
		word = getword(s,&i);
			if (strcmp(word.c_str(), "into") != 0) throw std::exception("Error");
			word = getword(s,&i);
			if (word.empty()) throw std::exception("Error");
			tablename = word;
			word = getword(s,&i);
			if (strcmp(word.c_str(), "values") != 0) throw std::exception("Error");
			word = getword(s,&i);
			if (strcmp(word.c_str(), "(") != 0) throw std::exception("Error");
			word = getword(s,&i);
			while (!word.empty() && strcmp(word.c_str(), ")") != 0){
				p->values.push_back(word);
				word = getword(s,&i);
				if (strcmp(word.c_str(), ",") == 0) word = getword(s,&i);
			}
			if (strcmp(word.c_str(), ")") != 0) throw std::exception("Error");
		p->tableName = tablename;
		return std::dynamic_pointer_cast<struct Sentence>(p);
	}
	
	else if (strcmp(word.c_str(), "quit") == 0) {
		throw std::exception("Error");
	}
	
	else if (strcmp(word.c_str(), "execfile") == 0) {
		std::shared_ptr<efs> p = std::make_shared<efs>();;
		p->filePath = getword(s,&i);
		return std::dynamic_pointer_cast<struct Sentence>(p);
	}
}
