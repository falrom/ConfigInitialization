#include "Config.h"

Config::~Config()
{
}

bool Config::loadConfigFile(const string & path)
{
	return false;
}

bool Config::loadConfigFile()
{
	return loadConfigFile(filePath);
}
