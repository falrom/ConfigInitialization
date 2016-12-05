#include "Config.h"

// ȥ��ע��
string & Config::removeComment(string & item)
{
	if (item.find('=') == string::npos)
	{// ��Ŀ��û��'='��ֱ�Ӻ���
		item = "";
		return item;
	}

	// ��������'#'
	item = doRC(item);

	// �ҵ�ʣ�ಿ�ֵ�һ��'='
	size_t position = item.find('=');
	if (position == string::npos)
	{
		item = "";
		return item;
	}
	else
	{// ȥ��'='
		item.replace(position, 1, " ");
	}

	return item;
}

// �ݹ����δ�����Ŀ������'#'
string Config::doRC(string tail)
{
	size_t position = tail.find('#');
	if (position == string::npos)
		return tail;

	if (position != 0)
	{// �������Ϊ'#'��һ������ת�塣�����ʾ���ǰλ�û������
		if (tail[position - 1] == '\\')
		{// ����ת���ַ�'\#'
			tail.erase(position - 1, 1);
		}
	}	
	else
	{// ɾ��ע��
		tail.erase(position, tail.size() - position);
		return tail;
	}

	// �ݹ鴦������'#'
	string subHead = tail.substr(0,		   position              );
	string subTail = tail.substr(position, tail.size() - position);

	return (subHead + doRC(subTail));
}

Config::~Config()
{
}

// ���������ļ����������ļ�����ȫ����ȡ�������ڳ�Աconfigs��
bool Config::loadConfigFile(const string & path)
{
	ifstream confFile(path);
	if (!confFile.is_open())
		return false;

	string item, key, value;
	while (getline(confFile, item))
	{
		//ȥ��ע��
		if (removeComment(item) == "")
			continue;

		// ��ȡ��ֵ
		istringstream itemStream(item);
		itemStream >> key;
		item.replace(item.find(key), key.size(), " ");

		// �洢
		configs[key] = item;
	}

	return true;
}

// ���������ļ�
bool Config::loadConfigFile()
{
	return loadConfigFile(filePath);
}
