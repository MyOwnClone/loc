#pragma once

#include "Base.h"

namespace loc {

// Forward declarations
class Type;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LIBLOC_EXPORT Namespace
{
  public:
    Namespace();

    virtual ~Namespace();

    const std::string &getName() const { return _name; }

    typedef std::map<std::string, Namespace *> Children;

    Namespace *getParent() const { return _parent; }

    const Children &getChildren() const { return _children; }

    size_t getNumChildren() const { return _children.size(); }

    Namespace *getOrCreateChild(const char *name);

    typedef std::map<std::string, Type *> Types;

    const Types &getTypes() const { return _types; }

  private:
    std::string _name;

    Namespace *_parent;

    Children _children;

    Types _types;
};

}
