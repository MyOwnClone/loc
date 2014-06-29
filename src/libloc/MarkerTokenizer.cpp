#include "MarkerTokenizer.h"

namespace loc {

enum class ParserState
{
  Normal,
  Text,
  Operator,
  Number,
  WhiteSpace
};

MarkerTokenizer::MarkerTokenizer()
{

}

MarkerTokenizer::~MarkerTokenizer()
{

}

bool MarkerTokenizer::tokenize(const char *text)
{
  return true;
}

}
