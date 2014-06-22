#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Preprocessor
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

    bool process(const std::string &fileName, Tokens *tokens = nullptr, std::string *finalOutput = nullptr);

  private:
    IncludeDirs _includeDirs;

    Defines _defines;
};
