#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>

namespace loc {

template <typename T>
class Base: public std::enable_shared_from_this<T>
{
  public:
    typedef std::shared_ptr<T> Ptr;
    typedef std::shared_ptr<const T> ConstPtr;
    typedef std::weak_ptr<T> WeakPtr;
    typedef std::weak_ptr<const T> ConstWeakPtr;

    virtual ~Base()
    {
    
    }

  protected:
    Base()
    {
    
    }
};

}
