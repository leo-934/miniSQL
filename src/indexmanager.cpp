#include "IndexManager.h"

int IndexManager::test()
{
	return 1;
}

IndexManager::IndexManager()
{
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++) {
		createIndex(iter->second->indexName, iter->second->tableName, 
					iter->second->attrName, iter->second->type);
	}
}

void IndexManager::close()
{
	 writeintoBuffer();
	 map<int, IndexInfo*>::iterator iter = indexmap.begin();
	 for (; iter != indexmap.end(); it++) {
	 	if (iter->second->type == INT) {
	 		BPT<int>* sptr = (BPT<int>*)iter->second->Tree;
	 	}
	 	
	 	else if (iter->second->type == FLOAT) {
	 		BPT<float>* sptr = (BPT<float>*)iter->second->Tree;
	 	}
	 	
	 	else (iter->second->type == INT) {
	 		BPT<string>* sptr = (BPT<string>*)iter->second->Tree;
	 	}
	 	
	 	free (iter->second)
	 }
}

int IndexManager::writeintoBuffer(){
	
}

void IndexManager::setkey(int type, string key){
	stringstream ss;
	ss << key;
	if (type == this->INT) ss >> this->tmp.inttmp;
	else if (type == this->FLOAT) ss >> this->tmp.floattmp;
	else if (type > 0) ss >> this->tmp.stringtmp;
	else return;
}

int getkeysize(int type){
	if (type == INT) return sizeof(int);
	else if (type == FLOAT) return sizeof(float);
	else if (type > 0) return type + 1;
	else return -1; 
}

void* getindex(string indexName){
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++) {
		string name;
		name = (*iter->second).indexname;
		if (name == indexname) {
			return (*iter->second).Tree;
		}
	}
	return NULL; 
}

void IndexManager::createIndex(std::string indexName, std::string tableName, std::string attrName, int type)
{
	IndexInfo *i = new IndexInfo;
	void *Tree;
	i->indexName = indexName;
	i->tableName = tableName;
	i->attrName = attrName;
	i->type = type;
	
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++) {
		string name;
		name = (*iter->second).tablename;
		if (name == i->table){
			i->ifclustered = false;
		}
	}
	
	int keysize = getkeysize(i->type);
	
	if (i->type == INT) {
		BPT<int>* tree = new BPT<int>(indexName, keysize);
		i->Tree = tree;
		indexmap.insert(pair<int, IndexInfo*>(indexmap.size()+1, i));
		return tree;
	}
	
	else if (i->type == FLOAT) {
		BPT<float>* tree = new BPT<float>(indexName, keysize);
		i->Tree = tree;
		indexmap.insert(pair<int, IndexInfo*>(indexmap.size()+1, i));
		return tree;
	}
	
	else {
		BPT<string>* tree = new BPT<string>(indexName, keysize);
		i->Tree = tree;
		indexmap.insert(pair<int, IndexInfo*>(indexmap.size()+1, i));
		return tree;
	}
}

void IndexManager::dropIndex(std::string indexName)
{
	map<int, IndexInfo*>::iterator iter;
	void *tmp = NULL;
	for (iter = indexmap.begin(); iter != indexmap.end(); iter++) {
		string name;
		name = (*iter->second).indexName;
		if (name == indexName) {
			tmp = (*iter->second).Tree;
			if ((*iter->second).type == INT) {
				BPT<int>* t = (BPT<int>*)tmp;
				t->drop_tree(b->root);
			}
			
			else if ((*iter->second).type == FLOAT) {
				BPT<float>* t = (BPT<float>*)tmp;
				t->drop_tree(b->root);
			}
			
			else {
				BPT<string>* t = (BPT<string>*)tmp;
				t->drop_tree(b->root);
			}
			indexmap.erase(iter);
		}
	}
}

void IndexManager::dropAllIndex(std::string tableName)
{
	map<int, IndexInfo*>::iterator iter;
	void *tmp = NULL;
	for (iter = indexmap.begin(); iter != indexmap.end(); iter++) {
		string name;
		name = (*iter->second).tableName;
		if (name == tableName) {
			tmp = (*iter->second).Tree;
			if ((*iter->second).type == INT) {
				BPT<int>* t = (BPT<int>*)tmp;
				t->drop_tree(b->root);
			}
			
			else if ((*iter->second).type == FLOAT) {
				BPT<float>* t = (BPT<float>*)tmp;
				t->drop_tree(b->root);
			}
			
			else {
				BPT<string>* t = (BPT<string>*)tmp;
				t->drop_tree(b->root);
			}
			indexmap.erase(iter);
		}
	}
}

void IndexManager::insertToIndex(std::string indexName,std::string key, int type)
{
	setkey(type, key);
	if (type == INT) {
		BPT<int>* t = (BPT<int>*)getindex(indexname);
		int a = stoi(key);
		t->add_key(a);
	}
	
	else if (type == FLOAT) {
		BPT<float>* t = (BPT<float>*)getindex(indexname);
		int a = stof(key);
		t->add_key(a);
	}
	
	else {
		BPT<string>* t = (BPT<string>*)getindex(indexname);
		t->add_key(key);
	}
}


//std::string IndexManager::getBestIndex(std::string tableName)
//{
//	std::string indexName;
//	if (this->hasClusteredIndex(tableName)) indexName = this->getClusteredIndex(tableName);
//	else if (this->hasNonClusteredIndex(tableName)) {
//		auto tmp = this->getNonClusteredIndex(tableName);
//		indexName = tmp[0];
//	}
//	else {
//		indexName="";
//	}
//	return indexNane;
//}

std::vector<int64> IndexManager::selectIndexsByCondition(std::string TableName, std::string indexName, std::vector<condition> cond)
{
	return std::vector<int64>();
}

void IndexManager::removeAllIndexByAddress(std::string TableName, std::vector<int64> addresses)
{
	
}

bool IndexManager::hasClusteredIndex(std::string tableName)
{
	return IndexManager::hasAnyIndex(tableName);
}

std::string IndexManager::getClusteredIndex(std::string tableName)
{
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++) {
		string name;
		name = (*iter->second).tablename;
		if (name == tableName && iter->second->ifclustered == true){
			return (*iter->second).indexname;
			break;
		}
	}
}

bool IndexManager::hasNonClusteredIndex(std::string tableName)
{
	return IndexManager::hasAnyIndex(tableName);
}

std::vector<std::string> IndexManager::getNonClusteredIndex(std::string tableName)
{
	vector<string> indexvec;
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++) {
		string name;
		name = (*iter->second).tablename;
		if (name == tableName && iter->second->ifclustered == false){
			indexvec.push_back((*iter->second).indexName);
		}
	}
	return indexvec;
}

bool IndexManager::hasAnyIndex(std::string tableName)
{
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++) {
		string name;
		name = (*iter->second).tablename;
		if (name == tablename) {
			return true;
		}
	}
	return false;
}

std::vector<std::string> IndexManager::getAllIndex(std::string tableName)
{}
    vector<string> indexvec;
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++){
		string name;
		name = (*iter->second).tableName;
		if (name == tableName) {
			indexvec.push_back((*iter->second).indexName);
		}
		return indexvec;
	}
}

std::string IndexManager::getAttrNameByIndexName(std::string indexName, std::string tableName)
{
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++){
		string indxname, tabname;
		indxname = (*iter->second).indexName;
		tabname = (*iter->second).tableName;
		if (indxname == indexName && tabname == tableName) {
			return (*iter->second).attrName;
		}
	}
}

std::string IndexManager::getIndexNameByAttrName(std::string attrName, std::string tableName)
{
	map<int, IndexInfo*>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); it++){
		string attname, tabname;
		attname = (*iter->second).attrName;
		tabname = (*iter->second).tableName;
		if (attname == attrName && tabname == tableName) {
			return (*iter->second).indexName;
		}
	}
}
