#include "stdafx.h"
#include "Preprocessor.h"

namespace liblocCLR {

Preprocessor::Preprocessor()
{
  _preprocessor = new loc::Preprocessor();

  Defines = gcnew List<String ^>();
  IncludeDirs = gcnew List<String ^>();
}

Preprocessor::~Preprocessor()
{
  delete _preprocessor;
}

void Preprocessor::PrepareIncludesAndDefines()
{
  _preprocessor->getDefines().clear();
  _preprocessor->getIncludeDirs().clear();

  for each (String ^define in Defines)
    _preprocessor->getIncludeDirs().push_back(MarshalString(define).stl_str());

  for each (String ^include in IncludeDirs)
    _preprocessor->getIncludeDirs().push_back(MarshalString(include).stl_str());
}

bool Preprocessor::ProcessFile(String ^fileName)
{
  PrepareIncludesAndDefines();

  return _preprocessor->processFile(MarshalString(fileName), nullptr, nullptr);
}

bool Preprocessor::ProcessFile(String ^fileName, Tokens ^tokens)
{
  PrepareIncludesAndDefines();

  loc::Preprocessor::Tokens locTokens;
  bool result = _preprocessor->processFile(MarshalString(fileName), &locTokens, nullptr);

  for (const auto &t: locTokens)
    tokens->Add(Token::Create(t));

  return result;
}

String ^Preprocessor::ProcessFileWithOutput(String ^fileName)
{
  PrepareIncludesAndDefines();

  std::string locFinalOutput;

  bool result = _preprocessor->processFile(MarshalString(fileName), nullptr, &locFinalOutput);
  
  return gcnew String(locFinalOutput.c_str());
}

String ^Preprocessor::ProcessFileWithOutput(String ^fileName, Tokens ^tokens)
{
  PrepareIncludesAndDefines();

  std::string locFinalOutput;
  loc::Preprocessor::Tokens locTokens;
  bool result = _preprocessor->processFile(MarshalString(fileName), &locTokens, &locFinalOutput);

  for (const auto &t: locTokens)
    tokens->Add(Token::Create(t));

  return gcnew String(locFinalOutput.c_str());
}

}
