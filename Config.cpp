#include "Config.h"

string & Config::removeComment(string & item)
{
	if (item.find('=') == string::npos)
	{
		item = "";
		return item;
	}

	item = doRC(item);

	size_t position = item.find('=');
	if (position == string::npos)
	{
		item = "";
		return item;
	}
	else
	{
		item.replace(position, 1, " ");
	}

	return item;
}

string Config::doRC(string tail)
{
	size_t position = tail.find('#');
	if (position == string::npos)
		return tail;

	if (position != 0)
	{
		if (tail[position - 1] == '\\')
		{
			tail.erase(position - 1, 1);
		}
	}	
	else
	{
		tail.erase(position, tail.size() - position);
		return tail;
	}

	string subHead = tail.substr(0,		   position              );
	string subTail = tail.substr(position, tail.size() - position);

	return subHead + doRC(subTail);
}

Config::~Config()
{
}

bool Config::loadConfigFile(const string & path)
{
	ifstream confFile(path);
	if (!confFile.is_open())
		return false;

	string item, key, value;
	while (getline(confFile, item))
	{
		if (removeComment(item) == "")
			continue;

		istringstream itemStream(item);
		itemStream >> key;
		item.replace(item.find(key), key.size(), " ");

		configs[key] = item;
	}

	return true;
}

bool Config::loadConfigFile()
{
	return loadConfigFile(filePath);
}
