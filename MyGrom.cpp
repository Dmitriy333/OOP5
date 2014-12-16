// MyGrom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyGrom.h"

int _tmain(int argc, _TCHAR* argv[])
{
	XmlNode *xml = Sys::Create< XmlNode >(Sys::GlobalOwner());
	xml->ReadFromFile("xml/Myxml.xml");
	xml->Process();
	xml->WriteToFile("xml/MyXmlWrite.xml");
	cout << "Completed!" << endl;
	_getch();
	xml->Destroy();
	//delete xml;
	return 0;
}

