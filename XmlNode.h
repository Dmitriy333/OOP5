#pragma once

#pragma comment (lib, "E:\\Учеба\\5-ый семестр\\ООП\\grom\\MyGrom\\System.lib")
#pragma comment (lib, "E:\\Учеба\\5-ый семестр\\ООП\\grom\\MyGrom\\XmlUtils.lib")
#pragma comment (lib, "E:\\Учеба\\5-ый семестр\\ООП\\grom\\MyGrom\\cppunit.lib")
#pragma comment (lib, "E:\\Учеба\\5-ый семестр\\ООП\\grom\\MyGrom\\libexpat.lib")
#include "Grom\System\PropertyTree.h"
#include "Grom\XmlUtils\XmlUtils.h"
#include <string>

class XmlNode : public Sys::PropertyTree
{
private:
	void SetAttributes();
	void SetChildText();

public:
	XmlNode();
	virtual ~XmlNode();
	void ReadFromFile(const char* filePath);
	void WriteToFile(const char* filePath);
	XmlNode* CreateChild(const char* name);
	void Process();
};

class XmlAttribute : public XmlNode
{
public:
	XmlAttribute(XmlNode *attr, const char* name, const char* value);
	virtual ~XmlAttribute();
};

class XmlText : public XmlNode
{
public:
	XmlText(XmlNode *node, const char* text);
	virtual ~XmlText();
};