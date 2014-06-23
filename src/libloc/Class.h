#pragma once

#include "Type.h"

namespace loc {

class Class: public Type, public Base<Class>
{
  public:
    Class();

    virtual ~Class();
};

}
