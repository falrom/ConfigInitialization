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
	template <typename varType> bool read(const string & key, varType *var, bool require = NECESSARY, const size_t size = 1);

};

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