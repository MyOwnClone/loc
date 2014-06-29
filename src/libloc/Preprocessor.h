#pragma once

#include <string>
#include <vector>

#include "Token.h"

namespace loc {

class LIBLOC_EXPORT Preprocessor
{
  public:
    Preprocessor();

    virtual ~Preprocessor();

    typedef std::vector<std::string> Strings;

    typedef Strings IncludeDirs;

    typedef Strings Defines;

    typedef std::vector<Token> Tokens;
    
    IncludeDirs &getIncludeDirs() { return _includeDirs; }

    const IncludeDirs &getIncludeDirs() const { return _includeDirs; }

    Defines &getDefines() { return _defines; }

    const Defines &getDefines() const { return _defines; }

    bool processString(const char *str, Tokens *tokens = nullptr, std::string *finalOutput = nullptr, const char *fileName = nullptr);

    bool processFile(const char *fileName, Tokens *tokens = nullptr, std::string *finalOutput = nullptr);

  private:
    IncludeDirs _includeDirs;

    Defines _defines;
};

}
