#include "Config.h"

int exampleMain()
{
	// ���������ȡ�ı�����������
	int varInt1 = 0;
	int varInt2 = 0;
	double varDouble1 = 0.0;
	double varDouble2 = 0.0;
	string varString;
	int arrInt[3];
	double arrDouble[4];

	// ʵ����һ��Config��Ķ���
	Config conf("example.cfg");
	// ���������ļ�
	if (!conf.loadConfigFile())
	{
		cerr << "Error: Can not open configuration file." << endl;
		return 1;
	}
	// ������ȡ���ñ��������顣ͨ���쳣�ķ�ʽ����
	try
	{
		//			key					var/arr				requirement			size
		conf.read(	"varInt1",			&varInt1,			NECESSARY					);
		conf.read(	"varInt2",			&varInt2										);
		conf.read(	"varDouble1",		&varDouble1										);
		conf.read(	"varDouble2",		&varDouble2,		NOT_NECESSARY				);
		conf.read(	"varString",		&varString										);
		conf.read(	"arrInt",			arrInt,				NECESSARY,			  3		);
		conf.read(	"arrDouble",		arrDouble,			NECESSARY,			  4		);
	}
	catch (const runtime_error error)
	{
		cerr << error.what() << endl;
		return 1;
	}

	// ��֤���
	cout << "The value of " << "varInt1"	<< " is " << varInt1	<< endl;
	cout << "The value of " << "varInt2"	<< " is " << varInt2	<< endl;
	cout << "The value of " << "varDouble1" << " is " << varDouble1 << endl;
	cout << "The value of " << "varDouble2" << " is " << varDouble2 << endl;
	cout << "The value of " << "varString"	<< " is " << varString	<< endl;

	cout << "The value of " << "arrInt"		<< " is";
	for (size_t i = 0; i < 3; i++)
	{
		cout << " " << arrInt[i];
	}
	cout << endl;

	cout << "The value of " << "arrDouble"	<< " is";
	for (size_t i = 0; i < 4; i++)
	{
		cout << " " << arrDouble[i];
	}
	cout << endl;

	return 0;
}