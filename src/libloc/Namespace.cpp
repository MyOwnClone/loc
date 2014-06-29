#include "Namespace.h"

namespace loc {

Namespace::Namespace()
{

}

Namespace::~Namespace()
{
  for (auto &kvp: _children)
    delete kvp.second;
}

Namespace *Namespace::getOrCreateChild(const char *name)
{
  Children::iterator iter = _children.find(name);
  if (iter != _children.end())
    return iter->second;

  Namespace *child = new Namespace();
  child->_name = name;
  child->_parent = this;
  _children[name] = child;

  return child;
}

}
