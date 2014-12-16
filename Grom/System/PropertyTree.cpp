// Free open-source Grom library

#include "Grom/System/PrecompiledHeader.h"

//#include <memory.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "Grom/System/Utils.h"
#include "Grom/System/PropertyTree.h"

namespace Sys
{

// PropertyTreeChildren

class PropertyTreeChildren : public Collection
{
};

// PropertyTree

void PropertyTree::Initialize(Object* owner)
{
  m_Children = Create<PropertyTreeChildren>(this);
  Object::Initialize(owner); // inherited
}

void PropertyTree::Finalize()
{
  //Clear(); // Can lead to the "object being destroyed cannot become owner" exception
  Object::Finalize(); // inherited
}

void PropertyTree::CopyFrom(PropertyTree* from)
{
  Clear();
  SetName(from->Name());
  SetText(from->Text());
  m_Items.CopyFrom(from->m_Items);
  for (int i = 0; i < from->ChildCount(); ++i)
    CreateChild("")->CopyFrom(from->Child(i));
}

const char* PropertyTree::Name()
{
  return m_Name.c_str();
}

void PropertyTree::SetName(const char* value)
{
  if (value != NULL)
    m_Name = value;
  else
    m_Name.clear();
}

const char* PropertyTree::Text()
{
  return m_Text.c_str();
}

void PropertyTree::SetText(const char* value)
{
  if (value != NULL)
    m_Text = value;
  else
    m_Text.clear();
}

void PropertyTree::SetText(const char* value, int valueLength)
{
  if (valueLength != 0)
    if (value != NULL)
      m_Text.assign(value, valueLength);
    else
      throw Sys::CreateArgumentNullException();
  else
    m_Text.clear();
}

int PropertyTree::ItemCount()
{
  return m_Items.Count();
}

const char* PropertyTree::ItemName(int index)
{
  return m_Items[index].Name.c_str();
}

const char* PropertyTree::ItemValue(int index)
{
  return m_Items[index].Value.c_str();
}

const char* PropertyTree::ItemValueByName(const char* name, const char* defaultValue)
{
  int i = FindItem(name);
  if (i >= 0)
    return ItemValue(i);
  else
    return defaultValue;
}

int PropertyTree::FindItem(const char* name)
{
  if (name != NULL)
  {
    for (int i = 0; i < m_Items.Count(); ++i)
      if (strcmp(m_Items[i].Name.c_str(), name) == 0)
        return i;
  }
  return -1;
}

int PropertyTree::SetItem(const char* name, const char* value)
{
  if (name == NULL)
    throw Sys::CreateArgumentNullException();
  else if (name[0] == '\0')
    throw Sys::CreateArgumentOutOfRangeException();
  if (value == NULL)
    value = "";
  int i = FindItem(name);
  if (i < 0)
  {
    i = m_Items.Count();
    NameValue t;
    t.Name = name;
    t.Value = value;
    m_Items.Add(t);
  }
  else
  {
    m_Items[i].Name = name;
    m_Items[i].Value = value;
  }
  return i;
}

void PropertyTree::RemoveItem(const char* name)
{
  int i = FindItem(name);
  if (i >= 0)
    RemoveItemAt(i);
}

void PropertyTree::RemoveItemAt(int index)
{
  m_Items.RemoveAt(index);
}

void PropertyTree::Clear()
{
  if (m_Children->Count() > 0)
  {
    DestroyAndNull(m_Children);
    m_Children = Create<PropertyTreeChildren>(this);
  }
  m_Items.Clear();
}

PropertyTree* PropertyTree::Parent()
{
  PropertyTreeChildren* collection = as<PropertyTreeChildren*>(Owner());
  if (collection != NULL)
    return cast<PropertyTree*>(collection->Owner());
  else
    return NULL;
}

void PropertyTree::SetParent(PropertyTree* value)
{
  if (value == NULL)
    throw Sys::CreateArgumentNullException();
  SetOwner(value->m_Children);
}

int PropertyTree::ChildCount()
{
  return m_Children->Count();
}

PropertyTree* PropertyTree::Child(int index)
{
  return cast<PropertyTree*>(m_Children->Item(index));
}

PropertyTree* PropertyTree::FindChild(
  const char* path, const char* itemName, const char* itemValue)
{
  PropertyTree* result = this;
  if (path != NULL && path[0] != '\0')
  {
    MultiString names(path, "/", NULL);
    if (names.word_count() > 0)
    {
      // Go through hierarchy
      int k = 0;
      int m = names.word_count() - 1;
      while (k < m && result != NULL)
      {
        const char* name = names.word(k);
        int i = 0;
        int n = result->ChildCount();
        while (i < n && strcmp(result->Child(i)->Name(), name) != 0)
          ++i; // next child
        if (i < n)
          result = result->Child(i);
        else
          result = NULL; // not found
        ++k; // next level
      }
      // Search for given name, property name and property value
      if (result != NULL)
      {
        const char* name = names.word(m);
        int i = 0;
        int n = result->ChildCount();
        PropertyTree* p = NULL;
        while (i < n)
        {
          p = result->Child(i);
          if (strcmp(p->Name(), name) == 0)
          {
            if (itemName != NULL && itemValue != NULL)
            {
              const char* t = p->ItemValueByName(itemName, NULL);
              if (t != NULL && strcmp(t, itemValue) == 0)
                break;
            }
            else
                break;
          }
          ++i;
        }
        if (i < n)
          result = p;
        else
          result = NULL; // not found
      }
    }
  }
  return result;
}

const char* PropertyTree::ChildItemValueByName(const char* path,
    const char* itemName, const char* defaultValue)
{
  PropertyTree* p = FindChild(path, NULL, NULL);
  if (p != NULL)
    return p->ItemValueByName(itemName, defaultValue);
  else
    return defaultValue;
}

PropertyTree* PropertyTree::CreateChild(const char* name)
{
  PropertyTree* p = Create<PropertyTree>(m_Children);
  if (name != NULL)
  {
    try
    {
      p->SetName(name);
    }
    catch (...)
    {
      p->Destroy();
      throw;
    }
  }
  return p;
}

// NonRecursivePropertyTreeEnumerator

class NonRecursivePropertyTreeEnumerator
{
public:
  NonRecursivePropertyTreeEnumerator(
    NonRecursivePropertyTreeEnumerator* previousEnumerator, PropertyTree* parent);
  ~NonRecursivePropertyTreeEnumerator();

  NonRecursivePropertyTreeEnumerator* PreviousEnumerator();
  PropertyTree* Parent();
  bool IsBeforeFirst();
  bool IsAfterLast();
  bool MoveNext();
  PropertyTree* Current();

private:
  NonRecursivePropertyTreeEnumerator* m_PreviousEnumerator;
  PropertyTree* m_Parent;
  int m_CurrentChild;
};

NonRecursivePropertyTreeEnumerator::NonRecursivePropertyTreeEnumerator(
  NonRecursivePropertyTreeEnumerator* previousEnumerator, PropertyTree* parent) :
  m_PreviousEnumerator(previousEnumerator), m_Parent(parent), m_CurrentChild(-1)
{
}

NonRecursivePropertyTreeEnumerator::~NonRecursivePropertyTreeEnumerator()
{
}

inline
NonRecursivePropertyTreeEnumerator* NonRecursivePropertyTreeEnumerator::PreviousEnumerator()
{
  return m_PreviousEnumerator;
}

inline
PropertyTree* NonRecursivePropertyTreeEnumerator::Parent()
{
  return m_Parent;
}

inline
bool NonRecursivePropertyTreeEnumerator::IsBeforeFirst()
{
  return m_CurrentChild < 0;
}

inline
bool NonRecursivePropertyTreeEnumerator::IsAfterLast()
{
  return m_CurrentChild >= m_Parent->ChildCount();
}

bool NonRecursivePropertyTreeEnumerator::MoveNext()
{
  if (m_CurrentChild < m_Parent->ChildCount())
    ++m_CurrentChild;
  return m_CurrentChild < m_Parent->ChildCount();
}

inline
PropertyTree* NonRecursivePropertyTreeEnumerator::Current()
{
  return m_Parent->Child(m_CurrentChild);
}

// PropertyTreeEnumerator

PropertyTreeEnumerator::PropertyTreeEnumerator() :
  m_Root(NULL), m_ChildrenEnumerator(NULL)
{
}

PropertyTreeEnumerator::PropertyTreeEnumerator(PropertyTree* root) :
  m_Root(root), m_ChildrenEnumerator(NULL)
{
}

PropertyTreeEnumerator::~PropertyTreeEnumerator()
{
  Reset();
}

void PropertyTreeEnumerator::SetRoot(PropertyTree* value)
{
  if (m_Root != value)
  {
    Reset();
    m_Root = value;
  }
}

void PropertyTreeEnumerator::Reset()
{
  while (m_ChildrenEnumerator != NULL)
    DeleteNonRecursiveEnumerator();
}

bool PropertyTreeEnumerator::MoveNext()
{
  bool result = false;
  if (m_Root != NULL)
  {
    if (m_ChildrenEnumerator == NULL)
      m_ChildrenEnumerator = new NonRecursivePropertyTreeEnumerator(NULL, m_Root);
    if (!m_ChildrenEnumerator->IsBeforeFirst() && 
      !m_ChildrenEnumerator->IsAfterLast() && 
      m_ChildrenEnumerator->Current()->ChildCount() > 0)
    {
      m_ChildrenEnumerator = new NonRecursivePropertyTreeEnumerator(
        m_ChildrenEnumerator, m_ChildrenEnumerator->Current());
    }
    result = m_ChildrenEnumerator->MoveNext();
    while (!result && m_ChildrenEnumerator->PreviousEnumerator() != NULL)
    {
      DeleteNonRecursiveEnumerator();
      result = m_ChildrenEnumerator->MoveNext();
    }
  }
  return result;
}

PropertyTree* PropertyTreeEnumerator::Current()
{
  Sys::RunTimeAssert(m_ChildrenEnumerator != NULL);
  return m_ChildrenEnumerator->Current();
}

void PropertyTreeEnumerator::DeleteNonRecursiveEnumerator()
{
  NonRecursivePropertyTreeEnumerator* p = m_ChildrenEnumerator;
  m_ChildrenEnumerator = p->PreviousEnumerator();
  delete p;
}

} // namespace Sys
