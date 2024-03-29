#pragma once

#include "Token.h"

namespace loc {

class AttributeTokenizer
{
  public:
    AttributeTokenizer();

    virtual ~AttributeTokenizer();
    
    bool tokenize(const char *text);

    typedef std::vector<Token> Tokens;

    const Tokens &getTokens() const { return _tokens; }

  protected:
    static bool isTextCharacter(char ch);

    static bool isTextCharacterAny(char ch);

    static bool isNumberCharacter(char ch);

    static bool isWhiteSpace(char ch);
    
  private:
    Tokens _tokens;
};

}
