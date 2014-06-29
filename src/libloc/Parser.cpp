#include "Parser.h"
#include "Preprocessor.h"
#include "Namespace.h"

namespace loc {

Parser::Context::Context()
  : globalNamespace(new Namespace())
  , currentScopeDepth(0)
{

}

Parser::Context::~Context()
{
  delete globalNamespace;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Parser::Parser()
{
  _preprocessor = new Preprocessor();
}

Parser::~Parser()
{
  delete _preprocessor;
}

bool Parser::processFile(const char *name)
{
  Context ctx;
  ctx.currentFile = name;

  if (!_preprocessor->processFile(name, &ctx.tokens, &ctx.finalOutput))
  {
    return false;
  }

  for (const auto &token: ctx.tokens)
  {
    switch (token.tokenType)
    {
      case Token::Type::DirectiveLine:
      {
        
      }
      break;

      case Token::Type::BraceLeft:
      {
        ++ctx.currentScopeDepth;      
      }
      break;

      case Token::Type::BraceRight:
      {
        --ctx.currentScopeDepth;

        while (ctx.currentScopeDepth == ctx.scopeStack.back().scopeDepth && ctx.scopeStack.size() > 1)
          ctx.scopeStack.pop_back();
      }
      break;

      case Token::Type::Comment:
      {
        std::string line = token.text.stl_str();

        // Cut block comment marks
        if (StringUtils::startsWith(line, "/*"))
          line = StringUtils::between(line, "/*", "*/");

        line = StringUtils::between(line, "[", "]");
        if (line.length() > 0)
        {
          if (!processMarker(ctx, line.c_str()))
          {
            return false;
          }
        }
      }
      break;
    }
  }

  return true;
}

bool Parser::processMarker(Context &ctx, const char *text)
{


  return true;
}

}
