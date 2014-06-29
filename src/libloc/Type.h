#pragma once

#include "Base.h"

namespace loc {

// Forward declarations
class Namespace;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LIBLOC_EXPORT Type
{
  public:
    Type();

    virtual ~Type();
    
    Namespace *getNamespace() const { return _namespace; }

  protected:

  private:
    Namespace *_namespace;
};

}
