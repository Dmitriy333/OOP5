#include "stdafx.h"
#include "XmlNode.h"

using namespace std;

//XmlNode

XmlNode::XmlNode() : Sys::PropertyTree() {}// унаследованный класс от нашего PropertyTree (от класса Суркова)

XmlNode::~XmlNode() {
}

void XmlNode::ReadFromFile(const char* filePath)//считываем xml файл по пути, указанному в filePath
{
	Utl::LoadPropertyTreeFromXmlFile(this, filePath);
}

void XmlNode::WriteToFile(const char* filePath)//записываем переделанный xml файл по пути, указанному в filePath
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
		XmlNode *attr = this->CreateChild("attributes"); //создаем дочерний элемент, в котором будут храниться все аттрибуты с именем "attributes"
		int itemCount = this->ItemCount();
		for (int i = itemCount - 1; i >= 0; i--)//пробегаемся по всем аттрибутам элемента
		{
			new XmlAttribute(attr, this->ItemName(i), this->ItemValue(i));// создание элемента, который будет вложен в тег attributes (у него будет имя, которое было именем аттрибута рассматриваемого элемента, а значение - значение этого аттрибута)
			this->RemoveItemAt(i);
		}
	}
}

void XmlNode::Process()
{
	this->SetAttributes(); //устанавливаем аттрибуты текущему элементу (оборачиваем все атрибуты информацию в элемент "attributes")
	this->SetChildText();//устанавливаем текст текущему элементу xml-файла (оборачиваем текстовую информацию в элемент "text")
	if (this != NULL)
	{
		for (int i = 0; i < this->ChildCount(); i++) //цикл, который проходит по всем дочерним эдементам ткущего элемента
		{
			XmlNode *node = reinterpret_cast<XmlNode*>(this->Child(i)); 
			node->SetAttributes();
			node->SetChildText();
			node->Process();// рекурсивно запускаем наш метод process уже для дочернего элемента
		}
	}
}

void XmlNode::SetChildText()
{
	const char* text1 = this->Text();//берем текстовую информацию элемента
	if (strcmp(this->Text(), "") && strcmp(this->Name(), "text") && this->ChildCount() > 0)//если строка с текстовой информцией не нулевая
	{
		const char* text = this->Text();
		new XmlText(this, text);// то создаем элемент с именем "text", в который будет вложен весь текст
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
	XmlNode *textNode = node->CreateChild("text");//создаем дочерний элемент с именем "text", в котором будет храниться вся текстовая информация
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
	textNode->SetText(res.c_str());//заносим всю текстовую информацию
	node->SetText("");//удаляем тест из текущего элемента
}

XmlText::~XmlText() {
}