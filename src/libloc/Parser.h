#pragma once

#include "Token.h"

namespace loc {

// Forward declarations
class Namespace;
class Preprocessor;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LIBLOC_EXPORT Parser
{
  public:
    Parser();

    virtual ~Parser();

    Preprocessor *getPreprocessor() const { return _preprocessor; }

    virtual bool processFile(const char *name);

    typedef std::vector<Token> Tokens;

    struct ScopeStackItem
    {
      Namespace *ns;
      int scopeDepth;

      ScopeStackItem(Namespace *aNS, int aScopeDepth)
        : ns(aNS)
        , scopeDepth(aScopeDepth)
      {
      
      }
    };

    typedef std::vector<ScopeStackItem> ScopeStack;

    struct Context
    {
      Tokens tokens;

      std::string finalOutput;

      Namespace *globalNamespace;

      ScopeStack scopeStack;

      RefString currentFile;

      int currentScopeDepth;

      Context();

      ~Context();
    };

  protected:
    virtual bool processMarker(Context &ctx, const char *text);

  private:
    Preprocessor *_preprocessor;
};

}
