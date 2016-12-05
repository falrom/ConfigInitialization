#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

#define		NECESSARY			true
#define		NOT_NECESSARY		false

class Config
{
private:
	// 存储配置文件路径
	string filePath;
	// 存储配置文件中所有理条目
	map<string, string> configs;

	// 去除条目中的注释部分
	string & removeComment(string & item);
	// 递归：依次寻找条目中的'#'并做处理
	string doRC(string tail);

public:
	// 默认无参构造函数
	Config() = default;
	/** 构造函数
	* param path: 配置文件路径。
	*/
	Config(const string & path) :filePath(path) {};

	~Config();

	/** 加载配置文件
	* param path: 配置文件路径。
	*/
	bool loadConfigFile(const string & path);
	/** 加载配置文件	*/
	bool loadConfigFile();

	/** 读取参数赋值变量
	* param key: 变量在配置文件中的键值。
	* param var: 变量指针（或数组名）。
	* param require: 是否是必需的（默认NECESSARY）。
	* param size: 数组大小（默认为1，即默认不是数组）。
	*/
	template <typename varType> bool read(const string & key, varType *var, bool require = NECESSARY, const size_t size = 1);

};

/** 读取参数赋值变量
* param key: 变量在配置文件中的键值。
* param var: 变量指针（或数组名）。
* param require: 是否是必需的（默认NECESSARY）。
* param size: 数组大小（默认为1，即默认不是数组）。
*/
template<typename varType>
inline bool Config::read(const string & key, varType *var, bool require, const size_t size)
{
	if (configs.find(key) == configs.end())
	{
		if (require)
			throw runtime_error("Error: Can not find " + key + " in configuration file.");
		else
			return false;
	}

	string tmp = configs[key];

	istringstream item(configs[key]);
	if (size == 1)
	{
		item >> *var;
	}
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			item >> var[i];
		}
	}

	return true;
}


#endif // !_CONFIG_H_