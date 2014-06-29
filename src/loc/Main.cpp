#include <iostream>
#include <fstream>

#include <libloc/Parser.h>

int main(int argc, char *argv[])
{
  loc::Parser p;

  p.processFile("Test.h");

  return 0;
}
