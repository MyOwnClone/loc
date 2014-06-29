#include "Token.h"

namespace loc {

Token::Token()
  : tokenType(Type::Unknown)
  , lineNumber(0)
  , columnNumber(0)
  , integer(0)
  , real(0.0)
{

}

}
