#include "AttributeTokenizer.h"

namespace loc {

enum class ParseState
{
  Normal,
  Text,
  Operator,
  Number,
  WhiteSpace
};

bool AttributeTokenizer::isTextCharacter(char ch)
{
  static const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$";
  return strchr(chars, ch) != 0;
}

bool AttributeTokenizer::isTextCharacterAny(char ch)
{
  static const char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_$0123456789";
  return strchr(chars, ch) != 0;
}

bool AttributeTokenizer::isNumberCharacter(char ch)
{
  return (ch >= '0') && (ch <= '9');
}

bool AttributeTokenizer::isWhiteSpace(char ch)
{
  static const char *chars = " \t";
  return strchr(chars, ch) != 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AttributeTokenizer::AttributeTokenizer()
{

}

AttributeTokenizer::~AttributeTokenizer()
{

}

bool AttributeTokenizer::tokenize(const char *text)
{
  ParseState state = ParseState::Normal;
  size_t cursor = 0;
  Token token;

  _tokens.clear();
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
        else if (Token::getTokenType(ch) != Token::Type::Unknown)
        {
          state = ParseState::Operator;
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
          _tokens.push_back(token);
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
          token.integer = atoi(token.text.c_str());
          _tokens.push_back(token);
          state = ParseState::Normal;
        }
        break;

      case ParseState::Operator:
        if (Token::getTokenType(token.text.c_str(), ch) != Token::Type::Unknown)
        {
          token.text += ch;
          ++cursor;
        }
        else
        {
          token.tokenType = Token::getTokenType(token.text.c_str());
          _tokens.push_back(token);
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
