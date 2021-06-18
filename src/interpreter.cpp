#include "..\include\Interpreter.h"

std::string Interpreter::getword(std::string s, int &i){
	string word;
	int i1, i2;
	
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i] != 0) {
		i++;
	}
	i1 = i;
	
	if (s[i] == '(' || s[i] == ',' || s[i] == ')') {
		i++;
		i2 = i;
		word = s.substr(i1, i2-i1);
		return word;
	}
	
	else if (s[i] == 39){ //µ¥ÒýºÅ
		i++;
		while (s[i] != 39 && s[i] != 0) i++;
		if (s[i] == 39) {
			i1++;
			i2 = i;
			i++;
			word = s.substr(i1, i2-i1);
			return word;
		}
		
		else {
			word = "";
			return word;
		}	
	}
	
	else {
		while (s[i] != ' ' && s[i] != 10 && s[i] != '(' && s[i] != ')' && s[i] != ',' && s[i] != 0)
				i++;
		i2 = i;
		if (i1 != i2) word = s.substr(i1, i2-i1);
		else word = "";
		
		return word;
	}
}

std::shared_ptr<Sentence> Interpreter::parseSql(std::string s){
	string word;
	int i = 0;
	
	word = getword(s, &i);
	if (strcmp(word.c_str(), "create") == 0) {
		word = getword(s, &i);
		
		if (strcmp(word.c_str(), "table") == 0) {
			std::shared_ptr<cts> p;
			string tablename = "";
			string primarykey = "";
			word = getword(s, &i);
			if(!word.empty()) tablename = word;
			p->tableName = tablename;
			else {
				// tablename lacked 
				return 0;
			}
			
			word = getword(s, &i);
			if (word.empty() || strcmp(word.c_str(), "(") != 0) {
				return 0;
			}
			
			else {
				word = getword(s, &i);
				while (!word.empty() && strcmp(word.c_str(), "primary") != 0 && strcmp(word.c_str(), ")") != 0){
					string attrName = word;
					int type;
					bool ifunique = false;
					word = getword(s, &i);
					if (strcmp(word.c_str(), "int") == 0) type = catalog::INT;
					else if (strcmp(word.c_str(), "float") == 0) type = catalog::FLOAT;
					else if (strcmp(word.c_str(), "char") == 0){
						word = getword(s, &i);
						if (strcmp(word.c_str(), "(")) {
							// illeagel type
							return 0;
						}
						word = getword(s, &i);
						istringstream c(word);
						if (!(c >> type)) {
							// illegel number
							return 0;
						}
						word = getword(s, &i);
						if (strcmp(word.c_str(), ")")) {
							// illegel type
							return 0;
						}
						type = catalog::CHAR;
						p->attrLenForChar.insert(pair<string, int>(attrName, strlen(word)));
					}
					
					else {
						// no type
						return 0;
					}
					
					word = getword(s, &i);
					if (strcmp(word.c_str(), "unique") == 0) {
						ifunique = true;
						p->uniqueKeys.push_back(attrName);				
					}
					p->attrCata.insert(pair<string, catalog>(attrName, type));
					
					if(strcmp(word.c_str(), ",") != 0) {
						if(strcmp(word.c_str(), ",") != 0){
							// , error
							return 0;
						}
						else break;
					}
					
					word = getword(s, &i);
				}
				
				if (strcmp(word.c_str(), "primary") == 0) {
					word = getword(s, &i);
					if (strcmp(word.c_str(), "key") != 0) {
						// error
						return 0;
					}
					
					else {
						word = getword(s, &i);
						p->primaryKey = word;
					}
				}
				
			}
			
			return p;
		}
		
		else if (strcmp(word.c_str(), "index") == 0){
			std::shared_ptr<cis> p;
			string indexname = "";
			string tablename = "";
			string attrname = "";
			word = getword(s, &i);
			if (!word.empty()) indexname = word;
			else {
				//error
				return 0;
			}
			
			word = getword(s, &i);
			try {
				if (strcmp(word.c_str(),"on") != 0)
					throw SyntaxException();
				word = getword(s,&i);
				if (word.empty())
					throw SyntaxException();
				tablename = word;
				word = getword(s,&i);
				if (strcmp(word.c_str(),"(") != 0)
					throw SyntaxException();
				word = getword(s,&i);
				if (word.empty())
					throw SyntaxException();
				attrname = word;
				word = getword(s,&i);
				if (strcmp(word.c_str(),")") != 0)
					throw SyntaxException();
				p->indexName = indexname;
				p->tableNmae = tablename;
				p->attrName = attrname;
				return p;
			} catch(SyntaxException&) {
				//error
				return 0;
			}
		}
		
		return 0;
	}
	
	else if(strcmp(word.c_str(), "drop") == 0) {
		word = getword(s,&i);
		
		if (strcmp(word.c_str(), "table") == 0) {
			if(!word.empty()){
				std::shared_ptr<dts> p;
				word = getword(s,&i);
				p->tableName = word;
				return p;
			}
			else {
				//error
				return 0;
			}
		}
		
		else if (strcmp(word.c_str(), "index") == 0) {
			std::shared_ptr<dis> p;
			string indexname = "";
			string tablename = "";
			word = getword(s,&i);
			if (!word.empty()){
				indexname = word;
			}
			else {
				//error
				return 0;
			}
			word = getword(s,&i);
			if (strcmp(word.c_str(), "on") != 0){
				//error
				return 0;
			}
			word = getword(s,&i);
			if(!word.empty()) tablename = word;
			p->tableName = tablename;
			p->indexNmae = indexname;
			return p;
		}
		
		else {
			return 0;
		}
		return 0;
	}
	
		
	else if(strcmp(word.c_str(), "select") == 0) {
		std::shared_ptr<srs> p;
		string tablename = "";
		condition c;
		word = getword(s,&i);
		if (strcmp(word.c_str(), "*") != 0) {
			while (strcmp(word.c_str(), "from") != 0) {
				c->attrName = word;
				c->comp = NULL;
				c->value = NULL;
				p->conditions.push_back(c)
				word = getword(s,&i);
			}
		}
		else word = getword(s,&i);
		if (strcmp(word.c_str(), "from") != 0) {
			//error
			return 0;
		}
		
		word = getword(s,&i);
		if(!word.empty()) tablename = word;
		else {
			//error
			return 0;
		}
		word = getword(s,&i);
		if (word.empty()) {
			if (p->conditions.size == 0) {
				p->tableName = tablename;
				p->conditions.resize(0);
			}
			else {
				p->tableName = tablename;
				return p;	
			}
		}
		else if (strcmp(word.c_str(), "where") == 0) {
			string attrname = "";
			string value = "";
			comparison comp;
			word = getword(s,&i);
			while(1) {
				try {
					if(word.empty()) throw SyntaxException();
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
					else throw SyntaxException();
					word = getword(s,&i);
					if(word.empty()) throw SyntaxException();
					value = word;
					word = getword(s,&i);
					condition c(attrname, comp, value);
					p->tableName = tablename;
					p->conditions.push_back(c); 
					if(word.empty()) break;
					if (strcmp(word.c_str(),"and") != 0)
						throw SyntaxException();
					word = getWord(s,&tmp);		
				} catch (SyntaxException&) {
					//error
					return 0;
				}
			}
			return p;	
		}
		return 0;
	}
	
	else if(strcmp(word.c_str(), "delete") == 0) {
		std::shared_ptr<drs> p;
		string tablename = "";
		word = getword(s,&i);
		if (strcmp(word.c_str(), "from") != 0) {
			//error
			return 0;
		}
		word = getword(s,&i);
		if (!word.empty()) tablename = word;
		else {
			//error
			return 0;
		}
		
		word = getword(s,&i);
		if (word.empty()) {
			// no condition
			p->tableName = tablename;
			p->conditions.resize(0);
			return p;
		}
		
		else if (strcmp(word.c_str(), "where") == 0) {
			string attrname = "";
			string value = "";
			comparison comp;
			word = getword(s,&i);
			while(1) {
				try {
					if (word.empty()) throw SyntaxException();
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
					else throw SyntaxException();
					word = getword(s,&i);
					if (word.empty()) throw SyntaxException();
					value = word;
					word = getword(s,&i);
					condition c(attrname, comp, value);
					p->tableName = tablename;
					p->conditions.push_back(c);
					if(word.empty()) break;
					if (strcmp(word.c_str(),"and") != 0)
						throw SyntaxException();
					word = getWord(s,&tmp);		
				} catch (SyntaxException&) {
					//error
					return 0;
				}	
			}
			return p;
		}
		return 0;
	}
	
	else if (strcmp(word.c_str(), "insert") == 0) {
		std::shared_ptr<irs> p;
		string tablename = "";
		word = getWord(s,&tmp);
		try {
			if (strcmp(word.c_str(), "into") != 0) throw SyntaxException();
			word = getWord(s,&tmp);
			if (word.empty()) throw SyntaxException();
			tablename = word;
			word = getword(s,&i);
			if (strcmp(word.c_str(), "values") != 0) throw SyntaxException();
			word = getword(s,&i);
			if (strcmp(word.c_str(), "(") != 0) throw SyntaxException();
			word = getword(s,&i);
			while (!word.empty() && strcmp(word.c_str(), ")") != 0){
				p->values.push_back(word);
				word = getword(s,&i);
				if (strcmp(word.c_str(), ",") == 0) word = getword(s,&i);
			}
			if (strcmp(word.c_str(), ")") != 0) throw SyntaxException();
		} catch (SyntaxException&){
			//error
			return 0;
		}
		p->tableName = tablename;
		return p;
	}
	
	else if (strcmp(word.c_str(), "quit") == 0) {
		return 0;
	}
	
	else if (strcmp(word.c_str(), "execfile") == 0) {
		std::shared_ptr<efs> p;
		p->filePath = getWord(s,&i);
		return p;
	}
}
