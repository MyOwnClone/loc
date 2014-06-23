#include "Namespace.h"

namespace loc {

Namespace::Namespace(const std::string &name)
  : _name(name)
{

}

Namespace::~Namespace()
{

}

bool Namespace::setParent(const Namespace::Ptr &parent)
{
  Namespace::Ptr oldParent = getParent();
  if (oldParent != parent)
  {
    if (parent)
    {
      if (parent->_children.find(_name) == parent->_children.end())
        parent->_children[_name] = shared_from_this();
      else
        return false;

      _parent = parent;

      if (oldParent)
        oldParent->_children.erase(oldParent->_children.find(_name));
    }
  }

  return true;
}

}
