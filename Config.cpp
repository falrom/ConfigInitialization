#include "Config.h"

// 去除注释
string & Config::removeComment(string & item)
{
	if (item.find('=') == string::npos)
	{// 条目中没有'='，直接忽略
		item = "";
		return item;
	}

	// 处理所有'#'
	item = doRC(item);

	// 找到剩余部分第一个'='
	size_t position = item.find('=');
	if (position == string::npos)
	{
		item = "";
		return item;
	}
	else
	{// 去除'='
		item.replace(position, 1, " ");
	}

	return item;
}

// 递归依次处理条目中所有'#'
string Config::doRC(string tail)
{
	size_t position = tail.find('#');
	if (position == string::npos)
		return tail;

	if (position != 0)
	{// 如果句首为'#'，一定不是转义。（访问句首前位置会崩溃）
		if (tail[position - 1] == '\\')
		{// 处理转义字符'\#'
			tail.erase(position - 1, 1);
		}
	}	
	else
	{// 删除注释
		tail.erase(position, tail.size() - position);
		return tail;
	}

	// 递归处理后面的'#'
	string subHead = tail.substr(0,		   position              );
	string subTail = tail.substr(position, tail.size() - position);

	return (subHead + doRC(subTail));
}

Config::~Config()
{
}

// 加载配置文件，将配置文件内容全部读取并存贮在成员configs中
bool Config::loadConfigFile(const string & path)
{
	ifstream confFile(path);
	if (!confFile.is_open())
		return false;

	string item, key, value;
	while (getline(confFile, item))
	{
		//去除注释
		if (removeComment(item) == "")
			continue;

		// 提取键值
		istringstream itemStream(item);
		itemStream >> key;
		item.replace(item.find(key), key.size(), " ");

		// 存储
		configs[key] = item;
	}

	return true;
}

// 加载配置文件
bool Config::loadConfigFile()
{
	return loadConfigFile(filePath);
}
