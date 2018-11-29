#include <iostream>
#include <fstream>
#include <string.h>

#include "./include/lexical_analyzer/TinyLexicalAnalyzer.h"
#include "./include/parser/TinyParser.h"

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

    return -1;
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
    size_t initialSize = lexTokens.size();

    for (size_t i = 0; i < initialSize; i++)
    {
      TinyLexicalAnalyzer::Token token = lexTokens.front();
      lexTokens.pop();

      std::cout << programAnalyzer.convertTokenToString(token);

      if (token == TinyLexicalAnalyzer::Token::Character ||
          token == TinyLexicalAnalyzer::Token::String ||
          token == TinyLexicalAnalyzer::Token::Number ||
          token == TinyLexicalAnalyzer::Token::Identifier)
      {
        std::cout << " | " << tokenValues.at(i) << std::endl;
      }
      else
      {
        std::cout << std::endl;
      }
    }

    return 0;
  }

  // Parsing
  TinyParser programParser;
  programParser.parseProgram(lexTokens, tokenValues);

  if (astFlag)
  {
    programParser.getAst().print();
  }

  return 0;
}