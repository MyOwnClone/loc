#pragma once

#include "Base.h"

namespace loc {

class Namespace: public Base<Namespace>
{
  public:
    Namespace(const std::string &name);

    virtual ~Namespace();

    const std::string &getName() const { return _name; }

    typedef std::map<std::string, Namespace::Ptr> Children;

    virtual bool setParent(const Namespace::Ptr &parent);

    Namespace::Ptr getParent() const { return _parent.lock(); }

    const Children &getChildren() const { return _children; }

  private:
    std::string _name;

    Namespace::WeakPtr _parent;

    Children _children;
};

}
