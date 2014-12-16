#include "stdafx.h"
#include "XmlNode.h"

using namespace std;

//XmlNode

XmlNode::XmlNode() : Sys::PropertyTree() {}

XmlNode::~XmlNode() {
}

void XmlNode::ReadFromFile(const char* filePath)
{
	Utl::LoadPropertyTreeFromXmlFile(this, filePath);
}

void XmlNode::WriteToFile(const char* filePath)
{
	Utl::SavePropertyTreeToXmlFile(this, filePath);
}

XmlNode* XmlNode::CreateChild(const char* name)
{
	if (this == NULL)
		return NULL;
	else
		return reinterpret_cast<XmlNode*>(this->Sys::PropertyTree::CreateChild(name));
}

void XmlNode::SetAttributes()
{
	if (this->ItemCount() > 0)
	{
		XmlNode *attr = this->CreateChild("attributes");
		int itemCount = this->ItemCount();
		for (int i = itemCount - 1; i >= 0; i--)
		{
			new XmlAttribute(attr, this->ItemName(i), this->ItemValue(i));
			this->RemoveItemAt(i);
		}
	}
}

void XmlNode::Process()
{
	this->SetAttributes();
	this->SetChildText();
	if (this != NULL)
	{
		for (int i = 0; i < this->ChildCount(); i++)
		{
			XmlNode *node = reinterpret_cast<XmlNode*>(this->Child(i));
			node->SetAttributes();
			node->SetChildText();
			node->Process();
		}
	}
}

void XmlNode::SetChildText()
{
	const char* text1 = this->Text();
	if (strcmp(this->Text(), "") && strcmp(this->Name(), "text") && this->ChildCount() > 0)
	{
		const char* text = this->Text();
		new XmlText(this, text);
	}
}

//XmlAttribute

XmlAttribute::XmlAttribute(XmlNode *attr, const char* name, const char* value)
{
	XmlNode* item = attr->CreateChild(name);
	item->SetText(value);
}

XmlAttribute::~XmlAttribute() {}

//XmlText

XmlText::XmlText(XmlNode *node, const char* text)
{
	XmlNode *textNode = node->CreateChild("text");
	string str(text), res("");
	for (int i = 0; i < str.size(); i++)//
	{
		char a = str[i];
		if (str[i] == '\t' || str[i] == '\n')
		{
			str[i] = ' ';
		}
		if (str[i] == ' ')
		{
			if (i == 0 || res[res.size() - 1] == ' ')
				continue;
		}
		res += str[i];
	}
	textNode->SetText(res.c_str());
	node->SetText("");
}

XmlText::~XmlText() {
}