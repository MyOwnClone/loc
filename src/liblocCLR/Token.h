#pragma once

#include <liblocCLR/Base.h>

#include <libloc/Token.h>

namespace liblocCLR {

public ref struct Token
{
  public:
    enum class Type
    {
      Unknown = (int)loc::Token::Type::Unknown,
      Whitespace = (int)loc::Token::Type::Whitespace,
      NewLine = (int)loc::Token::Type::NewLine,
      DirectiveLine = (int)loc::Token::Type::DirectiveLine,
      Comment = (int)loc::Token::Type::Comment,
      Identifier = (int)loc::Token::Type::Identifier,
      Integer = (int)loc::Token::Type::Integer,
      Real = (int)loc::Token::Type::Real,
      String = (int)loc::Token::Type::String,
      BraceLeft = (int)loc::Token::Type::BraceLeft,
      BraceRight = (int)loc::Token::Type::BraceRight,
      ParenthesisLeft = (int)loc::Token::Type::ParenthesisLeft,
      ParenthesisRight = (int)loc::Token::Type::ParenthesisRight,
      Semicolon = (int)loc::Token::Type::Semicolon,
      Colon = (int)loc::Token::Type::Colon,
      Comma = (int)loc::Token::Type::Comma,
      Ampersand = (int)loc::Token::Type::Ampersand,
      Asterisk = (int)loc::Token::Type::Asterisk,
      Dot = (int)loc::Token::Type::Dot,
      Class = (int)loc::Token::Type::Class,
      Namespace = (int)loc::Token::Type::Namespace,
      Const = (int)loc::Token::Type::Const,
      Bool = (int)loc::Token::Type::Bool,
      Char = (int)loc::Token::Type::Char,
      Short = (int)loc::Token::Type::Short,
      Int = (int)loc::Token::Type::Int,
      Long = (int)loc::Token::Type::Long,
      Float = (int)loc::Token::Type::Float,
      Double = (int)loc::Token::Type::Double,
      End = (int)loc::Token::Type::End
    };

    Type TokenType;

    String ^Text;
    
    String ^FileName;

    int LineNumber;

    int ColumnNumber;

    int Integer;

    double Real;

    Token();

  internal:
    static Token ^Create(const loc::Token &t);
};

}
