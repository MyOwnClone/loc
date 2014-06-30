#pragma once

#include "Base.h"

namespace loc {

struct LIBLOC_EXPORT Token
{
  enum class Type
  {
    Unknown = 0,
    Whitespace,
    NewLine,
    DirectiveLine,
    Comment,
    Identifier,
    Integer,
    Real,
    String,
    BraceLeft,
    BraceRight,
    ParenthesisLeft,
    ParenthesisRight,
    Semicolon,
    Colon,
    Comma,
    Ampersand,
    Asterisk,
    Dot,
    Class,
    Namespace,
    Const,
    Bool,
    Char,
    Short,
    Int,
    Long,
    Float,
    Double,
    End
  };

  Type tokenType;
  
  RefString text;

  RefString fileName;

  int lineNumber;

  int columnNumber;

  int integer;

  double real;

  Token();

  static Type getTokenType(const char *text);
};

}
