#pragma once

#include "RefString.h"

namespace loc {

struct Token
{
  enum class Type
  {
    Unknown = 0,
    Whitespace,
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

  Type type;
  
  RefString text;

  RefString fileName;

  int lineNumber;

  int columnNumber;

  int integer;

  double real;

  Token();

};

}
