#include "indexmanager.h"
#include <cstdlib>
int IndexManager::test()
{
	return 1;
}

IndexManager::IndexManager(std::shared_ptr<CatalogManager> _catalogManager)
{
	catalogManager = _catalogManager;
	// readfromBuffer();
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		createIndex(iter->second->indexName, iter->second->tableName,
					iter->second->attrName);
	}
}

void IndexManager::close()
{
	writeintoBuffer();
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if (iter->second->type == catalog::INT)
		{
			BPT<int> *sptr = (BPT<int> *)iter->second->Tree;
		}

		else if (iter->second->type == catalog::FLOAT)
		{
			BPT<float> *sptr = (BPT<float> *)iter->second->Tree;
		}

		else if (iter->second->type == catalog::INT)
		{
			BPT<std::string> *sptr = (BPT<std::string> *)iter->second->Tree;
		}

		free(iter->second);
	}
}

void IndexManager::writeintoBuffer()
{
	std::ofstream fs("indexes.bin", std::ofstream::out);
	catalog type;
	// write indexmap
	for (auto i : indexmap)
	{
		fs << i.first << " ";
		fs << i.second->indexName << " ";
		fs << i.second->tableName << " ";
		fs << i.second->attrName << " ";
	}
	// write key&value
	for (auto i : indexmap)
	{
		type = i.second->type;
		if (type == catalog::INT)
		{
			BPT<int> *t = (BPT<int> *)getindex(i.second->tableName, i.second->indexName);
			std::map<int, int64> keyvalpair;
			keyvalpair = t->getkeyvalpair();
			for (auto j : keyvalpair)
			{
				fs << j.first << " ";
				fs << j.second << " ";
			}
		}

		else if (type == catalog::FLOAT)
		{
			BPT<float> *t = (BPT<float> *)getindex(i.second->tableName, i.second->indexName);
			std::map<float, int64> keyvalpair;
			keyvalpair = t->getkeyvalpair();
			for (auto j : keyvalpair)
			{
				fs << j.first << " ";
				fs << j.second << " ";
			}
		}

		else
		{
			BPT<std::string> *t = (BPT<std::string> *)getindex(i.second->tableName, i.second->indexName);
			std::map<std::string, int64> keyvalpair;
			keyvalpair = t->getkeyvalpair();
			for (auto j : keyvalpair)
			{
				fs << j.first << " ";
				fs << j.second << " ";
			}
		}
	}
}

void IndexManager::readfromBuffer()
{
	std::ifstream fs;
	fs.open("indexes.bin", std::ifstream::in);
	if (!fs)
	{
		return;
	}
	// read indexmap
	int indexmapSize;
	fs >> indexmapSize;
	for (int j = 0; j < indexmapSize; ++j)
	{
		int size;
		IndexInfo *indexinfo = (struct IndexInfo *)malloc(sizeof(struct IndexInfo));
		fs >> size;
		if (fs.eof())
			break;
		fs >> indexinfo->indexName;
		fs >> indexinfo->tableName;
		fs >> indexinfo->attrName;

		indexmap.insert(std::map<int, IndexInfo *>::value_type(size, indexinfo));
	}

	// read key&value
	for (auto i : indexmap)
	{
		catalog type;
		type = catalogManager->getCataByAttrName(i.second->indexName, i.second->attrName);
		if (type == catalog::INT)
		{
			BPT<int> *t = (BPT<int> *)getindex(i.second->tableName, i.second->indexName);
			int key;
			int64 value;
			fs >> key;
			fs >> value;
			t->add_key(key, value);
		}

		else if (type == catalog::FLOAT)
		{
			BPT<float> *t = (BPT<float> *)getindex(i.second->tableName, i.second->indexName);
			float key;
			int64 value;
			fs >> key;
			fs >> value;
			t->add_key(key, value);
		}

		else
		{
			BPT<std::string> *t = (BPT<std::string> *)getindex(i.second->tableName, i.second->indexName);
			std::string key;
			int64 value;
			fs >> key;
			fs >> value;
			t->add_key(key, value);
		}
	}
}

int IndexManager::getkeysize(catalog type)
{
	if (type == catalog::INT)
		return sizeof(int);
	else if (type == catalog::FLOAT)
		return sizeof(float);
	else if (type == catalog::CHAR)
		return 255;
	else
		throw std::runtime_error("no this type");
	;
}

int IndexManager::getdegree(catalog type)
{
	int degree = blockSpace / (getkeysize(type) + sizeof(int64));
	if (degree % 2 == 0)
		degree -= 1;
	return degree;
}

void *IndexManager::getindex(std::string tableName, std::string indexName)
{
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).indexName == indexName)
		{
			return (*iter->second).Tree;
		}
	}
	return NULL;
}

void *IndexManager::createIndex(std::string indexName, std::string tableName, std::string attrName)
{
	IndexInfo *i = new IndexInfo;
	void *Tree;
	if (IndexManager::hasAnyIndex(tableName))
		i->ifclustered = false;
	i->indexName = indexName;
	i->tableName = tableName;
	i->attrName = attrName;
	i->type = catalogManager->getCataByAttrName(tableName, attrName);

	int keysize = getkeysize(i->type);
	int degree = getdegree(i->type);

	if (i->type == catalog::INT)
	{
		BPT<int> *tree = new BPT<int>(keysize, degree);
		i->Tree = tree;
		indexmap.insert(std::pair<int, IndexInfo *>(indexmap.size() + 1, i));
		return tree;
	}

	else if (i->type == catalog::FLOAT)
	{
		BPT<float> *tree = new BPT<float>(keysize, degree);
		i->Tree = tree;
		indexmap.insert(std::pair<int, IndexInfo *>(indexmap.size() + 1, i));
		return tree;
	}

	else
	{
		BPT<std::string> *tree = new BPT<std::string>(keysize, degree);
		i->Tree = tree;
		indexmap.insert(std::pair<int, IndexInfo *>(indexmap.size() + 1, i));
		return tree;
	}
}

void IndexManager::dropIndex(std::string indexName)
{
	std::map<int, IndexInfo *>::iterator iter;
	void *tmp = NULL;
	for (iter = indexmap.begin(); iter != indexmap.end(); iter++)
	{
		if ((*iter->second).indexName == indexName)
		{
			tmp = (*iter->second).Tree;
			if ((*iter->second).type == catalog::INT)
			{
				BPT<int> *t = (BPT<int> *)tmp;
				t->drop_tree(t->root);
			}

			else if ((*iter->second).type == catalog::FLOAT)
			{
				BPT<float> *t = (BPT<float> *)tmp;
				t->drop_tree(t->root);
			}

			else
			{
				BPT<std::string> *t = (BPT<std::string> *)tmp;
				t->drop_tree(t->root);
			}
			indexmap.erase(iter);
			return;
		}
	}
	throw std::runtime_error("no specific index found");
}

void IndexManager::dropAllIndex(std::string tableName)
{
	std::map<int, IndexInfo *>::iterator iter;
	void *tmp = NULL;
	for (iter = indexmap.begin(); iter != indexmap.end(); iter++)
	{
		std::string tablename;
		tablename = (*iter->second).tableName;
		if (tablename == tableName)
		{
			tmp = (*iter->second).Tree;
			if ((*iter->second).type == catalog::INT)
			{
				BPT<int> *t = (BPT<int> *)tmp;
				t->drop_tree(t->root);
			}

			else if ((*iter->second).type == catalog::FLOAT)
			{
				BPT<float> *t = (BPT<float> *)tmp;
				t->drop_tree(t->root);
			}

			else
			{
				BPT<std::string> *t = (BPT<std::string> *)tmp;
				t->drop_tree(t->root);
			}
			indexmap.erase(iter);
			return;
		}
	}
	// throw std::runtime_error("no index found in this table");
}

void IndexManager::insertToIndex(std::string indexName, std::string tableName, std::any key, int64 value)
{
	// auto test=key._Cast.
	std::map<int, IndexInfo *>::iterator iter;
	catalog type;
	for (iter = indexmap.begin(); iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).indexName == indexName)
			type = (*iter->second).type;
	}
	if (type == catalog::INT)
	{
		BPT<int> *t = (BPT<int> *)getindex(tableName, indexName);
		auto a = std::any_cast<int>(key);
		t->add_key(a, value);
		// t->leafoutput();
	}

	else if (type == catalog::FLOAT)
	{
		BPT<float> *t = (BPT<float> *)getindex(tableName, indexName);
		auto a = std::any_cast<float>(key);
		t->add_key(a, value);
		// t->leafoutput();
	}

	else
	{
		BPT<std::string> *t = (BPT<std::string> *)getindex(tableName, indexName);
		auto a = std::any_cast<std::string>(key);
		t->add_key(a, value);
		// t->leafoutput();
	}
}

// std::string IndexManager::getBestIndex(std::string tableName)
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
// }

std::vector<int64> IndexManager::selectIndexsByCondition(std::string tableName, std::string indexName, std::vector<condition> cond)
{
	std::vector<int64> valvec;
	std::vector<std::any> keyvec;
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).indexName == indexName)
		{
			// for (int i = 0; i < cond.size(); i++) {
			// if ((*iter->second).type == cond[i].cata && (*iter->second).attrName == cond[i].attrName) {
			if ((*iter->second).type == catalog::INT)
			{
				BPT<int> *t = (BPT<int> *)getindex(tableName, indexName);
				valvec = t->retval();
				keyvec = t->retkey();
			}

			else if ((*iter->second).type == catalog::FLOAT)
			{
				BPT<float> *t = (BPT<float> *)getindex(tableName, indexName);
				valvec = t->retval();
				keyvec = t->retkey();
			}

			else
			{
				BPT<std::string> *t = (BPT<std::string> *)getindex(tableName, indexName);
				valvec = t->retval();
				keyvec = t->retkey();
			}
			//}
			//}
		}
	}
	std::vector<int64> res;
	for (int i = 0; i < valvec.size(); i++)
	{
		bool flag = 1;
		for (auto c : cond)
		{
			judger myjudger(c);
			if (myjudger(keyvec[i]) == false)
				flag = 0;
		}
		if (flag)
			res.push_back(valvec[i]);
	}
	return res;
}

bool IndexManager::hasClusteredIndex(std::string tableName)
{
	return IndexManager::hasAnyIndex(tableName);
}

std::string IndexManager::getClusteredIndex(std::string tableName)
{
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).ifclustered == true)
		{
			return (*iter->second).indexName;
			break;
		}
	}
	throw std::runtime_error("no clustered index found");
}

bool IndexManager::hasNonClusteredIndex(std::string tableName)
{
	std::vector<std::string> indexvec;
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).ifclustered == false)
		{
			return true;
			break;
		}
	}
	return false;
}

std::vector<std::string> IndexManager::getNonClusteredIndex(std::string tableName)
{
	std::vector<std::string> indexvec;
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName && (*iter->second).ifclustered == false)
		{
			indexvec.push_back((*iter->second).indexName);
		}
	}
	return indexvec;
}

bool IndexManager::hasAnyIndex(std::string tableName)
{
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::string> IndexManager::getAllIndex(std::string tableName)
{
	std::vector<std::string> indexvec;
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).tableName == tableName)
		{
			indexvec.push_back((*iter->second).indexName);
		}
	}
	return indexvec;
}

std::string IndexManager::getAttrNameByIndexName(std::string indexName, std::string tableName)
{
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).indexName == indexName && (*iter->second).tableName == tableName)
		{
			return (*iter->second).attrName;
		}
	}
}

std::string IndexManager::getIndexNameByAttrName(std::string attrName, std::string tableName)
{
	if (attrName == "name" && tableName == "person")
	{
	}
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	for (; iter != indexmap.end(); iter++)
	{
		if ((*iter->second).attrName == attrName && (*iter->second).tableName == tableName)
		{
			return (*iter->second).indexName;
		}
	}
	return "";
}

void IndexManager::removeIndexByAddress(std::string tableName, std::vector<int64> addresses)
{
	std::map<int, IndexInfo *>::iterator iter = indexmap.begin();
	catalog type;
	std::string tablename;
	std::string indexname;
	std::vector<int64> valvec;
	for (; iter != indexmap.end(); iter++)
	{
		tablename = (*iter->second).tableName;
		indexname = (*iter->second).indexName;
		type = (*iter->second).type;
		if (tablename == tableName)
		{
			if (type == catalog::INT)
			{
				BPT<int> *t = (BPT<int> *)getindex(tablename, indexname);
				// valvec = t->retval();
				t->delval(addresses);
			}

			else if (type == catalog::FLOAT)
			{
				BPT<float> *t = (BPT<float> *)getindex(tablename, indexname);
				// valvec = t->retval();
				t->delval(addresses);
			}

			else
			{
				BPT<std::string> *t = (BPT<std::string> *)getindex(tablename, indexname);
				// valvec = t->retval();
				t->delval(addresses);
			}
			/*for (int i = 0; i < addresses.size(); i++) {
				for (int j = 0; j < valvec.size(); j++) {
					if (addresses[i] == valvec[j]) {
						dropIndex(indexname, tablename);
					}
				}
			}*/
		}
	}
}