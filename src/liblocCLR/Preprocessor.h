#pragma once

#include <liblocCLR/Base.h>
#include <liblocCLR/Token.h>

#include <libloc/Preprocessor.h>

namespace liblocCLR {

public ref class Preprocessor
{
  public:
    Preprocessor();

    typedef List<Token ^> Tokens;

    property List<String ^> ^IncludeDirs;

    property List<String ^> ^Defines;

    bool ProcessFile(String ^fileName);

    bool ProcessFile(String ^fileName, Tokens ^tokens);

    String ^ProcessFileWithOutput(String ^fileName);

    String ^ProcessFileWithOutput(String ^fileName, Tokens ^tokens);

  protected:
    virtual ~Preprocessor();

  private:
    void PrepareIncludesAndDefines();

    loc::Preprocessor *_preprocessor;
};

}
