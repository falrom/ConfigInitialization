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

//template <typename VarType>
//struct ConfItem
//{
//	string key;				// 键值
//	size_t size = 1;		// 数组长度
//	VarType &var;
//};

class Config
{
private:

	string filePath;
	map<string, string> configs;
	string & removeComment(string & item);
	string doRC(string tail);

public:

	Config() = default;
	Config(const string & path) :filePath(path) {};
	~Config();

	bool loadConfigFile(const string & path);
	bool loadConfigFile();
	template <typename varType> bool read(const string & key, varType & var, bool require = NECESSARY, const size_t size = 1);


};




#endif // !_CONFIG_H_