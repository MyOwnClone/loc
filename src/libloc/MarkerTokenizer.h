#pragma once

#include "Token.h"

namespace loc {

class MarkerTokenizer
{
  public:
    MarkerTokenizer();

    virtual ~MarkerTokenizer();
    
    bool tokenize(const char *text);

    typedef std::vector<Token> Tokens;

    const Tokens &getTokens() const { return _tokens; }

  private:
    Tokens _tokens;
};

}
