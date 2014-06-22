#include <iostream>
#include <fstream>

#include "Preprocessor.h"

int main(int argc, char *argv[])
{
  Preprocessor p;

  Preprocessor::Tokens tokens;
  std::string output;

  p.process("test.h", &tokens, &output);

  RefString currentFile;

  FILE *fw = fopen("output.tok", "wb");
  if (fw)
  {
    for (const auto &t: tokens)
    {
      if (t.fileName != currentFile)
      {
        currentFile = t.fileName;
        fprintf(fw, "FILE: %s\n", t.fileName.c_str());
      }

      fprintf(fw, "%d:%d: %s (%d)\n", t.lineNumber, t.columnNumber, t.text.c_str(), (int)t.type);
    }

    fclose(fw);
  }

  //printf("\nFinished. Press any key... "); getchar();
  return 0;
}
