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
	// �洢�����ļ�·��
	string filePath;
	// �洢�����ļ�����������Ŀ
	map<string, string> configs;

	// ȥ����Ŀ�е�ע�Ͳ���
	string & removeComment(string & item);
	// �ݹ飺����Ѱ����Ŀ�е�'#'��������
	string doRC(string tail);

public:
	// Ĭ���޲ι��캯��
	Config() = default;
	/** ���캯��
	* param path: �����ļ�·����
	*/
	Config(const string & path) :filePath(path) {};

	~Config();

	/** ���������ļ�
	* param path: �����ļ�·����
	*/
	bool loadConfigFile(const string & path);
	/** ���������ļ�	*/
	bool loadConfigFile();

	/** ��ȡ������ֵ����
	* param key: �����������ļ��еļ�ֵ��
	* param var: ����ָ�루������������
	* param require: �Ƿ��Ǳ���ģ�Ĭ��NECESSARY����
	* param size: �����С��Ĭ��Ϊ1����Ĭ�ϲ������飩��
	*/
	template <typename varType> bool read(const string & key, varType *var, bool require = NECESSARY, const size_t size = 1);

};

/** ��ȡ������ֵ����
* param key: �����������ļ��еļ�ֵ��
* param var: ����ָ�루������������
* param require: �Ƿ��Ǳ���ģ�Ĭ��NECESSARY����
* param size: �����С��Ĭ��Ϊ1����Ĭ�ϲ������飩��
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