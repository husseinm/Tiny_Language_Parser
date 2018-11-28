#include <algorithm>
#include <istream>
#include <exception>

#include "./include/TinyLexicalAnalyzer.h"

#define MaxLookupSize 10

TinyLexicalAnalyzer::TinyLexicalAnalyzer()
{
  tokenRepresentationMap = std::map<TinyLexicalAnalyzer::Token, std::string>();
  tokenRepresentationMap[Token::Program] = "program";
  tokenRepresentationMap[Token::Variable] = "var";
  tokenRepresentationMap[Token::Constant] = "const";
  tokenRepresentationMap[Token::Type] = "type";
  tokenRepresentationMap[Token::Function] = "function";
  tokenRepresentationMap[Token::Return] = "return";
  tokenRepresentationMap[Token::Begin] = "begin";
  tokenRepresentationMap[Token::End] = "end";
  tokenRepresentationMap[Token::Swap] = ":=:";
  tokenRepresentationMap[Token::Assignment] = ":=";
  tokenRepresentationMap[Token::Integer] = "integer";
  tokenRepresentationMap[Token::Output] = "output";
  tokenRepresentationMap[Token::If] = "if";
  tokenRepresentationMap[Token::Then] = "then";
  tokenRepresentationMap[Token::Else] = "else";
  tokenRepresentationMap[Token::While] = "while";
  tokenRepresentationMap[Token::Do] = "do";
  tokenRepresentationMap[Token::Case] = "case";
  tokenRepresentationMap[Token::Of] = "of";
  tokenRepresentationMap[Token::Elipses] = "..";
  tokenRepresentationMap[Token::Otherwise] = "otherwise";
  tokenRepresentationMap[Token::Repeat] = "repeat";
  tokenRepresentationMap[Token::For] = "for";
  tokenRepresentationMap[Token::Until] = "until";
  tokenRepresentationMap[Token::Loop] = "loop";
  tokenRepresentationMap[Token::Pool] = "pool";
  tokenRepresentationMap[Token::Exit] = "exit";
  tokenRepresentationMap[Token::LE] = "<=";
  tokenRepresentationMap[Token::NE] = "<>";
  tokenRepresentationMap[Token::LT] = "<";
  tokenRepresentationMap[Token::GE] = ">=";
  tokenRepresentationMap[Token::GT] = ">";
  tokenRepresentationMap[Token::Eq] = "=";
  tokenRepresentationMap[Token::Mod] = "mod";
  tokenRepresentationMap[Token::And] = "and";
  tokenRepresentationMap[Token::Or] = "or";
  tokenRepresentationMap[Token::Not] = "not";
  tokenRepresentationMap[Token::Read] = "read";
  tokenRepresentationMap[Token::Successor] = "succ";
  tokenRepresentationMap[Token::Predecessor] = "pred";
  tokenRepresentationMap[Token::CharFun] = "chr";
  tokenRepresentationMap[Token::OrdFun] = "ord";
  tokenRepresentationMap[Token::Eof] = "eof";
  tokenRepresentationMap[Token::Colon] = ":";
  tokenRepresentationMap[Token::Semicolon] = ";";
  tokenRepresentationMap[Token::Dot] = ".";
  tokenRepresentationMap[Token::Comma] = ",";
  tokenRepresentationMap[Token::OpenBracket] = "(";
  tokenRepresentationMap[Token::CloseBracket] = ")";
  tokenRepresentationMap[Token::Plus] = "+";
  tokenRepresentationMap[Token::Minus] = "-";
  tokenRepresentationMap[Token::Multiply] = "*";
  tokenRepresentationMap[Token::Divide] = "/";
}

TinyLexicalAnalyzer::~TinyLexicalAnalyzer()
{
}

std::string TinyLexicalAnalyzer::convertTokenToString(TinyLexicalAnalyzer::Token token)
{
  return tokenRepresentationMap.at(token);
}

TinyLexicalAnalyzer::Token TinyLexicalAnalyzer::convertStringToToken(std::string string)
{
  // Abusing the standards, yay...
  // https://tinyurl.com/y7m4c9mf -> Shortened SO Link
  for (auto it = this->tokenRepresentationMap.rbegin(); it != this->tokenRepresentationMap.rend(); ++it)
  {
    if (it->second == string)
    {
      return it->first;
    }
  }

  throw std::out_of_range("Not Found");
}

// TODO: Add Declaration Tables
// TODO: Add Error Checking
// TODO: Dynamically calculate the MaxLookahead
std::vector<TinyLexicalAnalyzer::Token> TinyLexicalAnalyzer::analyzeProgram(
    std::istream &tinyProgram)
{
  std::vector<TinyLexicalAnalyzer::Token> tokens = std::vector<TinyLexicalAnalyzer::Token>();
  std::vector<char> textBuffer = std::vector<char>();
  bool insideCommentBlockType1 = false;
  bool insideCommentBlockType2 = false;
  int lineNumber = 1;

  while (!tinyProgram.eof())
  {
    // Grab the next char and check if the new buffer matches a token, if not, catch the exception
    //   and retry on next loop iteration with another char.
    char nextChar = tinyProgram.get();

    // Skip processing on New Lines OR whitespace
    if (nextChar == '\n')
    {
      insideCommentBlockType1 = false;
      lineNumber++;
    }

    // Skip everything in between comments
    if (nextChar == '{')
    {
      insideCommentBlockType2 = true;
    }
    else if (nextChar == '}')
    {
      insideCommentBlockType2 = false;
      continue;
    }
    else if (nextChar == '#')
    {
      insideCommentBlockType1 = true;
    }

    if (!isspace(nextChar) && !insideCommentBlockType1 && !insideCommentBlockType2)
    {
      textBuffer.push_back(nextChar);
      const int preTokenLocationInTinyProgram = tinyProgram.tellg();
      const char ogNextChar = nextChar;

      // Check for Char
      if (nextChar == '\'')
      {
        textBuffer.clear();
        textBuffer.push_back(tinyProgram.get());
        nextChar = tinyProgram.get();
        if (nextChar != '\'')
        {
          // TODO: Error out we have a problem
        }

        // TODO: Store this somewhere minus last char...

        textBuffer.clear();
        continue;
      }

      // Check for String
      if (nextChar == '\"')
      {
        textBuffer.clear();

        while (nextChar != '\"')
        {
          char nextChar = tinyProgram.get();
          textBuffer.push_back(nextChar);
        }

        // TODO: Store this somewhere minus last char...

        textBuffer.clear();
        tinyProgram.unget();
        continue;
      }

      for (int i = 0; i <= MaxLookupSize; i++)
      {
        try
        {
          auto token = convertStringToToken(std::string(textBuffer.begin(), textBuffer.end()));

          tokens.push_back(token);
          textBuffer.clear();
          break;
        }
        catch (const std::out_of_range &e)
        {
        }

        nextChar = tinyProgram.get();
        textBuffer.push_back(nextChar);
      }

      // Handle a lookup that is over the max char token lookahead size & fails to match any token
      if (textBuffer.size() >= MaxLookupSize)
      {
        // Reset initial seek to try again for number | identifier
        textBuffer.clear();
        textBuffer.push_back(ogNextChar);
        tinyProgram.seekg(preTokenLocationInTinyProgram);

        if (isdigit(ogNextChar))
        {
          // If starts with a number, must be a number...
          nextChar = ogNextChar;

          while (isdigit(nextChar))
          {
            nextChar = tinyProgram.get();
            textBuffer.push_back(nextChar);
          }

          // TODO: Store this minus last char...
          tinyProgram.unget();
          textBuffer.clear();
        }
        else if (isalpha(ogNextChar) || ogNextChar == '_')
        {
          // If starts with a letter or underscore, must be an identifier...
          nextChar = ogNextChar;

          while (isalnum(nextChar) || nextChar == '_')
          {
            nextChar = tinyProgram.get();
            textBuffer.push_back(nextChar);
          }

          // TODO: Store this minus last char...
          tinyProgram.unget();
          textBuffer.clear();
        }
        else if (ogNextChar == EOF)
        {
          return tokens;
        }
        else
        {
          char errorBuffer[115];

          sprintf(errorBuffer, "Lexical Analyzer failed to translate token starting with \'%c\' on line %d into a token"
                               " or identifier.",
                  ogNextChar, lineNumber);

          throw std::invalid_argument(errorBuffer);
        }
      }
    }
  }

  return tokens;
}