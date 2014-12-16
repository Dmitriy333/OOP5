// Free open-source Grom library

#ifndef __Grom_XmlUtils_XmlUtils_h__
#define __Grom_XmlUtils_XmlUtils_h__

#include "Grom/System/Config.h"

namespace Sys
{
class PropertyTree;
}

namespace Utl
{

void LoadPropertyTreeFromXmlString(Sys::PropertyTree* props, const char* xml);
void LoadPropertyTreeFromXmlFile(Sys::PropertyTree* props, const char* xmlFilePath);
void SavePropertyTreeToXmlFile(Sys::PropertyTree* props, const char* xmlFilePath);

} // namespace Utl

#endif //__Grom_XmlUtils_XmlUtils_h__
