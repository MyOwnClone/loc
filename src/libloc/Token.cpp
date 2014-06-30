#include "Token.h"

namespace loc {

struct TokenTableItem
{
  Token::Type tokenType;
  const char *text;
};

static TokenTableItem g_TokenTable[] =
{
  { Token::Type::DirectiveLine, "#line" },
  { Token::Type::BraceLeft, "{" },
  { Token::Type::BraceRight, "}" },
  { Token::Type::ParenthesisLeft, "(" },
  { Token::Type::ParenthesisRight, ")" },
  { Token::Type::Semicolon, ";" },
  { Token::Type::Colon, ":" },
  { Token::Type::Comma, "," },
  { Token::Type::Ampersand, "&" },
  { Token::Type::Asterisk, "*" },
  { Token::Type::Dot, "." },
  { Token::Type::Class, "class" },
  { Token::Type::Namespace, "namespace" },
  { Token::Type::Const, "const" },
  { Token::Type::Bool, "bool" },
  { Token::Type::Char, "char" },
  { Token::Type::Short, "short" },
  { Token::Type::Int, "int" },
  { Token::Type::Long, "long" },
  { Token::Type::Float, "float" },
  { Token::Type::Double, "double" },

  { Token::Type::End, nullptr }
};

Token::Type Token::getTokenType(const char *text)
{
  TokenTableItem *item = g_TokenTable;

  while (item->text)
  {
    if (!strcmp(text, item->text))
      return item->tokenType;

    ++item;
  }

  return Token::Type::Unknown;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Token::Token()
  : tokenType(Type::Unknown)
  , lineNumber(0)
  , columnNumber(0)
  , integer(0)
  , real(0.0)
{

}

}
