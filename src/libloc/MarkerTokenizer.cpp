#include "MarkerTokenizer.h"

namespace loc {

enum class ParseState
{
  Normal,
  Text,
  Operator,
  Number,
  WhiteSpace
};

bool MarkerTokenizer::isTextCharacter(char ch)
{
  static const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$";
  return strchr(chars, ch) != 0;
}

bool MarkerTokenizer::isTextCharacterAny(char ch)
{
  static const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$0123456789";
  return strchr(chars, ch) != 0;
}

bool MarkerTokenizer::isNumberCharacter(char ch)
{
  return (ch >= '0') && (ch <= '9');
}

bool MarkerTokenizer::isWhiteSpace(char ch)
{
  static const char *chars = " \t";
  return strchr(chars, ch) != 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MarkerTokenizer::MarkerTokenizer()
{

}

MarkerTokenizer::~MarkerTokenizer()
{

}

bool MarkerTokenizer::tokenize(const char *text)
{
  ParseState state = ParseState::Normal;
  int cursor = 0;
  Token token;

  size_t textLen = (size_t)strlen(text);

  while (cursor <= textLen)
  {
    char ch = cursor < textLen ? text[cursor] : '\0';

    switch (state)
    {
      case ParseState::Normal:
        if (isTextCharacter(ch))
        {
          state = ParseState::Text;
          token.text = "";
          token.tokenType = Token::Type::Identifier;
        }
        else if (isNumberCharacter(ch))
        {
          state = ParseState::Number;
          token.text = "";
          token.tokenType = Token::Type::Integer;
        }
        else if (isOperator("" + ch))
        {
          state = ParseState.Operator;
          token.text = "";
          token.tokenType = Token::Type::Unknown;
        }
        else if (isWhiteSpace(ch))
          state = ParseState::WhiteSpace;
        else
          ++cursor;
        break;

      case ParseState::Text:
        if (isTextCharacterAny(ch))
        {
          token.text += ch;
          ++cursor;
        }
        else
        {
          Tokens.Add(token);
          state = ParseState::Normal;
        }
        break;

      case ParseState::Number:
        if (isNumberCharacter(ch))
        {
          token.text += ch;
          ++cursor;
        }
        else
        {
          if (!int.TryParse(token.Text, out token.Number))
            token.tokenType = Token::Type::Unknown;

          Tokens.Add(token);
          state = ParseState::Normal;
        }
        break;

      case ParseState::Operator:
        if (IsOperator(token.text + ch))
        {
          token.text += ch;
          ++cursor;
        }
        else
        {
          token.tokenType = GetTokenType(token.text.c_str());

          Tokens.Add(token);
          state = ParseState::Normal;
        }
        break;

      case ParseState::WhiteSpace:
        if (isWhiteSpace(ch))
          ++cursor;
        else
          state = ParseState::Normal;
        break;
    }
  }

  return true;
}

}
