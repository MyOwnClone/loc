#include "Preprocessor.h"

#include <fstream>

#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

struct CustomHooks: boost::wave::context_policies::default_preprocessing_hooks
{
  template <typename ContextT>
  bool found_include_directive(ContextT const &ctx, std::string const &filename, bool include_next)
  {
    bool isSystem = filename[0] == '<';
    std::string path = filename.substr(1, filename.length() - 2);
    std::string dirPath, nativePath;

    bool result = ctx.find_include_file(path, dirPath, isSystem, nullptr);

    return !result;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WaveID2TokenType
{
  boost::wave::token_id id;
  Token::Type type;
};

static WaveID2TokenType waveID2TokenTypeTable[] =
{
  { boost::wave::T_SPACE, Token::Type::Whitespace },
  { boost::wave::T_SPACE2, Token::Type::Whitespace },
  { boost::wave::T_NEWLINE, Token::Type::Whitespace },
  { boost::wave::T_CCOMMENT, Token::Type::Comment },
  { boost::wave::T_CPPCOMMENT, Token::Type::Comment },
  { boost::wave::T_IDENTIFIER, Token::Type::Identifier },
  { boost::wave::T_INTLIT, Token::Type::Integer },
  { boost::wave::T_FLOATLIT, Token::Type::Real },
  { boost::wave::T_STRINGLIT, Token::Type::String },
  { boost::wave::T_LEFTBRACE, Token::Type::BraceLeft },
  { boost::wave::T_RIGHTBRACE, Token::Type::BraceRight },
  { boost::wave::T_LEFTPAREN, Token::Type::ParenthesisLeft },
  { boost::wave::T_RIGHTPAREN, Token::Type::ParenthesisRight },
  { boost::wave::T_SEMICOLON, Token::Type::Semicolon },
  { boost::wave::T_COLON, Token::Type::Colon },
  { boost::wave::T_COMMA, Token::Type::Comma },
  { boost::wave::T_AND, Token::Type::Ampersand },
  { boost::wave::T_STAR, Token::Type::Asterisk },
  { boost::wave::T_DOT, Token::Type::Dot },
  { boost::wave::T_CLASS, Token::Type::Class },
  { boost::wave::T_NAMESPACE, Token::Type::Namespace },
  { boost::wave::T_CONST, Token::Type::Const },
  { boost::wave::T_EOF, Token::Type::End },
  { boost::wave::T_EOI, Token::Type::End },
  { boost::wave::T_UNKNOWN, Token::Type::Unknown }
};

boost::wave::token_id convert(Token::Type type)
{
  WaveID2TokenType *item = waveID2TokenTypeTable;
  while (item->id != boost::wave::T_UNKNOWN)
  {
    if (item->type == type)
      return item->id;

    ++item;
  }

  return boost::wave::T_UNKNOWN;
}

Token::Type convert(boost::wave::token_id id)
{
  WaveID2TokenType *item = waveID2TokenTypeTable;
  while (item->id != boost::wave::T_UNKNOWN)
  {
    if (item->id == id)
      return item->type;

    ++item;
  }

  return Token::Type::Unknown;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Preprocessor::Preprocessor()
{

}

Preprocessor::~Preprocessor()
{

}

bool Preprocessor::process(const std::string &fileName, Tokens *tokens, std::string *finalOutput)
{
  std::ifstream instream(fileName);
  if (instream.bad() || !instream.is_open() || instream.fail())
    return false;
  
  std::string input(std::istreambuf_iterator<char>(instream.rdbuf()), std::istreambuf_iterator<char>());
  
  typedef boost::wave::cpplexer::lex_iterator<boost::wave::cpplexer::lex_token<> > lex_iterator_type;
  typedef boost::wave::iteration_context_policies::load_file_to_string load_file_to_string_policy;
  typedef boost::wave::context<std::string::iterator, lex_iterator_type, load_file_to_string_policy, CustomHooks> context_type;

  context_type ctx(input.begin(), input.end(), fileName.c_str());
  ctx.set_language((boost::wave::language_support)(boost::wave::support_cpp11 | boost::wave::support_option_preserve_comments));
  ctx.add_macro_definition("LOC_RUNNING");
  ctx.add_include_path(".");
  ctx.add_sysinclude_path(".");

  for (const auto &dir: _includeDirs)
  {
    ctx.add_include_path(dir.c_str());
    ctx.add_sysinclude_path(dir.c_str());
  }

  for (const auto &def: _defines)
    ctx.add_macro_definition(def);
  
  context_type::iterator_type first = ctx.begin();
  context_type::iterator_type last = ctx.end();

  RefStringPool fileNamePool;
  RefStringPool textPool;

  while (true)
  {
    try
    {
      if (first != last)
      {
        if (finalOutput)
          (*finalOutput) += first->get_value().c_str();

        if (tokens)
        {
          using namespace boost::wave;

          Token t;

          token_id id = token_id(*first);
          t.type = convert(id);

          if (t.type != Token::Type::Whitespace)
          {
            t.fileName = fileNamePool.create(first->get_position().get_file().c_str());
            t.text = textPool.create(first->get_value().c_str());
            t.lineNumber = (int)first->get_position().get_line();
            t.columnNumber = (int)first->get_position().get_column();

            if (t.type == Token::Type::Integer)
            {
              t.integer = atoi(t.text.c_str());
              t.real = (double)t.integer;
            }
            else if (t.type == Token::Type::Real)
            {
              t.real = atof(t.text.c_str());
              t.integer = (int)t.real;
            }

            tokens->push_back(t);
          }
        }
      }
      else
        break;

      ++first;
    }
    catch (const boost::wave::preprocess_exception &e)
    {
      fprintf(stderr, "%s (%d:%d): %s\n", e.file_name(), e.line_no(), e.column_no(), e.description());

      // Can we recover? If not, return with error.
      if (!e.is_recoverable())
        return false;
    }
    catch (const boost::wave::cpp_exception &e)
    {
      fprintf(stderr, "%s (%d:%d): %s\n", e.file_name(), e.line_no(), e.column_no(), e.description());

      // Can we recover? If not, return with error.
      if (!e.is_recoverable())
        return false;
    }
    catch (const std::exception &e)
    {
      fprintf(stderr, "Exception: %s\n", e.what());

      // Can not recover from general exception
      return false;
    }
  }

  return true;
}
