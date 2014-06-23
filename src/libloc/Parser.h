#pragma once

#include "Namespace.h"

namespace loc {

class Parser
{
  public:
    Parser();

    virtual ~Parser();

  private:
    Namespace::Ptr _globalNamespace;
};

}
