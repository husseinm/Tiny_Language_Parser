#include <iostream>
#include <fstream>
#include <string.h>

#include "./include/TinyLexicalAnalyzer.h"

int main(int argc, char **argv)
{
  // Error Check
  if (argc != 3 || (strcmp(argv[1], "-ast") != 0))
  {
    std::cout << std::endl;
    std::cout << "ERROR: incorrect arguments given." << std::endl;
    std::cout << "HELP:" << std::endl;
    std::cout << "\t subc -ast PATH_TO_TINY_PROGRAM" << std::endl;
    std::cout << std::endl;
  }

  std::ifstream programFile(argv[2]);

  if (!programFile.is_open())
  {
    std::cout << "ERROR: error opening file " << argv[2] << std::endl;
    return -1;
  }

  // Lexical Analysis
  TinyLexicalAnalyzer programAnalyzer = TinyLexicalAnalyzer();
  auto lexTokens = programAnalyzer.analyzeProgram(programFile);

  for (auto token : lexTokens)
  {
    std::cout << programAnalyzer.convertTokenToString(token) << std::endl;
  }

  programFile.close();

  // Parsing

  return 0;
}