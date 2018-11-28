#include <iostream>
#include <fstream>
#include <string.h>

#include "./include/TinyLexicalAnalyzer.h"

int main(int argc, char **argv)
{
  // Arg Check
  bool astFlag = false;
  bool lexFlag = false;
  char *fileName;

  if (argc == 3)
  {
    if (strcmp(argv[1], "-ast") == 0)
    {
      astFlag = true;
    }

    if (strcmp(argv[1], "-lex") == 0)
    {
      lexFlag = true;
    }

    fileName = argv[2];
  }

  if (argc != 3 || (!astFlag && !lexFlag))
  {
    std::cout << std::endl;
    std::cout << "ERROR: incorrect arguments given." << std::endl;
    std::cout << "HELP:" << std::endl;
    std::cout << "\t subc <-ast | -lex> PATH_TO_TINY_PROGRAM" << std::endl;
    std::cout << std::endl;
  }

  // Read the given file
  std::ifstream programFile(fileName);

  if (!programFile.is_open())
  {
    std::cout << "ERROR: error opening file " << argv[2] << std::endl;
    return -1;
  }

  // Lexical Analysis
  TinyLexicalAnalyzer programAnalyzer = TinyLexicalAnalyzer();

  programAnalyzer.analyzeProgram(programFile);
  programFile.close();

  auto lexTokens = programAnalyzer.getTokens();
  auto tokenValues = programAnalyzer.getValues();

  if (lexFlag)
  {
    for (size_t i = 0; i < lexTokens.size(); i++)
    {
      TinyLexicalAnalyzer::Token token = lexTokens.at(i);

      std::cout << programAnalyzer.convertTokenToString(token);

      if (token == TinyLexicalAnalyzer::Character ||
          token == TinyLexicalAnalyzer::String ||
          token == TinyLexicalAnalyzer::Number ||
          token == TinyLexicalAnalyzer::Identifier)
      {
        std::cout << " | " << tokenValues.at(i) << std::endl;
      }
      else
      {
        std::cout << std::endl;
      }
    }
  }

  // Parsing

  return 0;
}