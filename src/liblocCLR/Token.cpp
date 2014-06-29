#include "Stdafx.h"
#include "Token.h"

namespace liblocCLR {

Token::Token()
  : TokenType(Type::Unknown)
  , LineNumber(0)
  , ColumnNumber(0)
  , Integer(0)
  , Real(0.0)
{

}

Token ^Token::Create(const loc::Token &t)
{
  Token ^token = gcnew Token();

  token->TokenType = (Token::Type)((int)t.tokenType);
  token->Text = gcnew String(t.text);
  token->FileName = gcnew String(t.fileName);
  token->LineNumber = t.lineNumber;
  token->ColumnNumber = t.columnNumber;
  token->Integer = t.integer;
  token->Real = t.real;

  return token;
}

}
