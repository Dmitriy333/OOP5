// Free open-source Grom library

#include "Grom/XmlUtils/PrecompiledHeader.h"

#include <stdio.h>
#include "expat.h"

#include "Grom/System/PropertyTree.h"
#include "Grom/XmlUtils/XmlUtils.h"

namespace Utl
{

// Forward

void XMLCALL LoadPropertyTreeFromXml_OnStartElement(
  void *userData, const XML_Char *name, const XML_Char **props);
void XMLCALL LoadPropertyTreeFromXml_OnEndElement(
  void *userData, const XML_Char *name);

void CopyAllProps(Sys::PropertyTree* result, const XML_Char **props)
{
  for (size_t i = 0; props[i] != NULL; i += 2)
    result->SetItem(props[i], props[i + 1]); // (!) performance warning
}

void XMLCALL LoadPropertyTreeFromXml_OnStartRootElement(
  void *userData, const XML_Char *name, const XML_Char **props)
{
  XML_Parser parser = (XML_Parser)userData;
  Sys::PropertyTree* result = (Sys::PropertyTree*)XML_GetUserData(parser);
  result->SetName(name);
  CopyAllProps(result, props);
  XML_SetElementHandler(parser,
    LoadPropertyTreeFromXml_OnStartElement,
    LoadPropertyTreeFromXml_OnEndElement);
}

// LoadPropertyTreeFromXml_OnEndRootElement

void XMLCALL LoadPropertyTreeFromXml_OnEndRootElement(
  void *userData, const XML_Char *name)
{
  XML_Parser parser = (XML_Parser)userData;
  Sys::PropertyTree* result = (Sys::PropertyTree*)XML_GetUserData(parser);
  std::string s = Sys::TrimSpaces(result->Text());
  result->SetText(s.c_str());
}

void XMLCALL LoadPropertyTreeFromXml_OnStartElement(
  void *userData, const XML_Char *name, const XML_Char **props)
{
  XML_Parser parser = (XML_Parser)userData;
  Sys::PropertyTree* result = (Sys::PropertyTree*)XML_GetUserData(parser);
  result = result->CreateChild(name);
  CopyAllProps(result, props);
  XML_SetUserData(parser, result);
}

void XMLCALL LoadPropertyTreeFromXml_OnEndElement(
  void *userData, const XML_Char *name)
{
  XML_Parser parser = (XML_Parser)userData;
  Sys::PropertyTree* result = (Sys::PropertyTree*)XML_GetUserData(parser);
  std::string s = Sys::TrimSpaces(result->Text());
  result->SetText(s.c_str());
  result = result->Parent();
  XML_SetUserData(parser, result);
  if (result == NULL)
  {
    // Expat reads first root tag only, so we do not need
    // protection from multiple root tags.
  }
}

// LoadPropertyTreeFromXml_OnCharacterData

void XMLCALL LoadPropertyTreeFromXml_OnCharacterData(
  void *userData, const XML_Char *text, int textLength)
{
  XML_Parser parser = (XML_Parser)userData;
  Sys::PropertyTree* result = (Sys::PropertyTree*)XML_GetUserData(parser);
  std::string s = result->Text(); // (!) performance warning
  s.append(text, textLength);
  result->SetText(s.data(), (int)s.length());
}

void LoadPropertyTreeFromXmlString(Sys::PropertyTree* props, const char* xml)
{
  if (xml != NULL)
  {
    XML_Parser parser = XML_ParserCreate("UTF-8");
    if (parser != NULL)
    {
      try
      {
        // Prepare parser
        XML_SetElementHandler(parser,
          LoadPropertyTreeFromXml_OnStartRootElement,
          LoadPropertyTreeFromXml_OnEndRootElement);
        XML_SetCharacterDataHandler(parser, LoadPropertyTreeFromXml_OnCharacterData);
        XML_UseParserAsHandlerArg(parser);
        XML_SetUserData(parser, props);

        // Parse
        int n = (int)strlen(xml);
        if (XML_Parse(parser, xml, (int)n, true) == XML_STATUS_ERROR)
          throw new Sys::Exception("cannot parse XML string");
      }
      catch (...)
      {
        // Protect from possible exceptions in callbacks (e.g. XML_SetElementHandler)
        XML_ParserFree(parser);
        throw;
      }
      XML_ParserFree(parser);
    }
    else
      throw new Sys::Exception("cannot create XML parser");
  }
  else
    throw Sys::CreateArgumentNullException();
}

void LoadPropertyTreeFromXmlFile(Sys::PropertyTree* props, const char* xmlFilePath)
{
  if (xmlFilePath != NULL)
  {
    FILE* f = fopen(xmlFilePath, "r");
    if (f != NULL)
    {
      try
      {
        XML_Parser parser = XML_ParserCreate("UTF-8");
        if (parser != NULL)
        {
          char *buf = NULL;
          try
          {
            // Prepare parser
            XML_SetElementHandler(parser,
              LoadPropertyTreeFromXml_OnStartRootElement,
              LoadPropertyTreeFromXml_OnEndRootElement);
            XML_SetCharacterDataHandler(parser, LoadPropertyTreeFromXml_OnCharacterData);
            XML_UseParserAsHandlerArg(parser);
            XML_SetUserData(parser, props);

            // Prepare buffer
            const size_t BUF_SIZE = 16 * 1024;
            buf = new char[BUF_SIZE];
            if (buf != NULL)
            {
              props->Clear();
              // Read & parse
              size_t n = fread(buf, 1, BUF_SIZE, f);
              while (n != 0)
              {
                if (XML_Parse(parser, buf, (int)n, n != BUF_SIZE) == XML_STATUS_ERROR)
                  throw new Sys::Exception(Sys::FormattedString(
                    "cannot parse XML file '%s'", xmlFilePath));
                n = fread(buf, 1, BUF_SIZE, f);
              }
            }
            else
              throw new Sys::SystemException("out of memory");
          }
          catch (...)
          {
            // Protect from possible exceptions in callbacks (e.g. XML_SetElementHandler)
            delete[] buf;
            XML_ParserFree(parser);
            throw;
          }
          delete[] buf;
          XML_ParserFree(parser);
        }
        else
          throw new Sys::Exception("cannot create XML parser");
      }
      catch (...)
      {
        // Protect from possible exceptions in callbacks (e.g. XML_SetElementHandler)
        fclose(f);
        throw;
      }
      fclose(f);
    }
    else
      throw new Sys::IOException(Sys::FormattedString(
        "cannot open file '%s' for reading", xmlFilePath));
  }
  else
    throw Sys::CreateArgumentNullException();
}

void XmlQuote(const char* s, std::string* result)
{
  result->clear();
  if (s != NULL)
  {
    while (*s != 0)
    {
      switch (*s)
      {
        case '&':
          result->append("&amp;");
          break;
        case '<':
          result->append("&lt;");
          break;
        case '"':
          result->append("&quot;");
          break;
        case '>':
          result->append("&gt;");
          break;
        case 9:
          result->append("&#9;");
          break;
        case 10:
          result->append("&#10;");
          break;
        case 13:
          result->append("&#13;");
          break;
        default:
          result->append(s, 1);
          break;
      }
      ++s;
    }
  }
}

#pragma message(__WARNING__ "strings with quotes and special symblos are not implemented!")
void SerializePropertyTreeToFile(Sys::PropertyTree* props, FILE* file, const char* tab)
{
  std::string buf;
  fprintf(file, "%s<%s", tab, props->Name());
  std::string t = tab;
  t += "  ";
  if (props->ItemCount() > 0)
  {
    for (int i = 0; i < props->ItemCount(); ++i)
    {
      XmlQuote(props->ItemValue(i), &buf);
      fprintf(file, "\n%s%s=\"%s\"", t.c_str(),
        props->ItemName(i), buf.c_str());
    }
  }
  size_t tl = strlen(props->Text());
  if (props->ChildCount() > 0 || tl > 0)
  {
    fprintf(file, ">\n");
    for (int i = 0; i < props->ChildCount(); ++i)
      SerializePropertyTreeToFile(props->Child(i), file, t.c_str());
    if (tl > 0)
    {
      XmlQuote(props->Text(), &buf);
      fprintf(file, "  %s%s\n", tab, buf.c_str());
    }
    fprintf(file, "%s</%s>\n", tab, props->Name());
  }
  else
    fprintf(file, "/>\n");
}

void SavePropertyTreeToXmlFile(Sys::PropertyTree* props, const char* xmlFilePath)
{
  if (xmlFilePath != NULL)
  {
    FILE* f = fopen(xmlFilePath, "w");
    if (f != 0)
    {
      try
      {
        SerializePropertyTreeToFile(props, f, "");
      }
      catch (...)
      {
        fclose(f);
        throw;
      }
      fclose(f);
    }
    else
      throw new Sys::IOException(Sys::FormattedString(
        "cannot open file '%s' for writing", xmlFilePath));
  }
  else
    throw Sys::CreateArgumentNullException();
}

} // namespace Utl
