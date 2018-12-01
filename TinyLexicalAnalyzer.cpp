#include <algorithm>
#include <istream>
#include <exception>

#include "./include/lexical_analyzer/TinyLexicalAnalyzer.h"

std::map<TinyLexicalAnalyzer::Token, std::string> TinyLexicalAnalyzer::_tokenRepresentationMap =
    std::map<TinyLexicalAnalyzer::Token, std::string>();
std::map<TinyLexicalAnalyzer::Token, bool> TinyLexicalAnalyzer::_isTokenTerminal = std::map<TinyLexicalAnalyzer::Token, bool>();
bool TinyLexicalAnalyzer::isInitialized = false;

TinyLexicalAnalyzer::TinyLexicalAnalyzer() : _insideCommentBlockType1(false), _insideCommentBlockType2(false),
                                             _lineNumber(1)
{
  _tokens = std::queue<Token>();
  _valuesMap = std::map<size_t, std::string>();

  if (!isInitialized)
  {
    _tokenRepresentationMap[Token::Program] = "program";
    _tokenRepresentationMap[Token::Variable] = "var";
    _tokenRepresentationMap[Token::Constant] = "const";
    _tokenRepresentationMap[Token::Type] = "type";
    _tokenRepresentationMap[Token::Function] = "function";
    _tokenRepresentationMap[Token::Return] = "return";
    _tokenRepresentationMap[Token::Begin] = "begin";
    _tokenRepresentationMap[Token::End] = "end";
    _tokenRepresentationMap[Token::Swap] = ":=:";
    _tokenRepresentationMap[Token::Assignment] = ":=";
    _tokenRepresentationMap[Token::Output] = "output";
    _tokenRepresentationMap[Token::If] = "if";
    _tokenRepresentationMap[Token::Then] = "then";
    _tokenRepresentationMap[Token::Else] = "else";
    _tokenRepresentationMap[Token::While] = "while";
    _tokenRepresentationMap[Token::Do] = "do";
    _tokenRepresentationMap[Token::Case] = "case";
    _tokenRepresentationMap[Token::Of] = "of";
    _tokenRepresentationMap[Token::Elipses] = "..";
    _tokenRepresentationMap[Token::Otherwise] = "otherwise";
    _tokenRepresentationMap[Token::Repeat] = "repeat";
    _tokenRepresentationMap[Token::For] = "for";
    _tokenRepresentationMap[Token::Until] = "until";
    _tokenRepresentationMap[Token::Loop] = "loop";
    _tokenRepresentationMap[Token::Pool] = "pool";
    _tokenRepresentationMap[Token::Exit] = "exit";
    _tokenRepresentationMap[Token::LE] = "<=";
    _tokenRepresentationMap[Token::NE] = "<>";
    _tokenRepresentationMap[Token::LT] = "<";
    _tokenRepresentationMap[Token::GE] = ">=";
    _tokenRepresentationMap[Token::GT] = ">";
    _tokenRepresentationMap[Token::Eq] = "=";
    _tokenRepresentationMap[Token::Mod] = "mod";
    _tokenRepresentationMap[Token::And] = "and";
    _tokenRepresentationMap[Token::Or] = "or";
    _tokenRepresentationMap[Token::Not] = "not";
    _tokenRepresentationMap[Token::Read] = "read";
    _tokenRepresentationMap[Token::Successor] = "succ";
    _tokenRepresentationMap[Token::Predecessor] = "pred";
    _tokenRepresentationMap[Token::CharFun] = "chr";
    _tokenRepresentationMap[Token::OrdFun] = "ord";
    _tokenRepresentationMap[Token::Eof] = "eof";
    _tokenRepresentationMap[Token::Colon] = ":";
    _tokenRepresentationMap[Token::Semicolon] = ";";
    _tokenRepresentationMap[Token::Dot] = ".";
    _tokenRepresentationMap[Token::Comma] = ",";
    _tokenRepresentationMap[Token::OpenBracket] = "(";
    _tokenRepresentationMap[Token::CloseBracket] = ")";
    _tokenRepresentationMap[Token::Plus] = "+";
    _tokenRepresentationMap[Token::Minus] = "-";
    _tokenRepresentationMap[Token::Multiply] = "*";
    _tokenRepresentationMap[Token::Divide] = "/";

    _isTokenTerminal[Token::Program] = true;
    _isTokenTerminal[Token::Variable] = true;
    _isTokenTerminal[Token::Constant] = true;
    _isTokenTerminal[Token::Type] = true;
    _isTokenTerminal[Token::Function] = true;
    _isTokenTerminal[Token::Return] = true;
    _isTokenTerminal[Token::Begin] = true;
    _isTokenTerminal[Token::End] = true;
    _isTokenTerminal[Token::Output] = true;
    _isTokenTerminal[Token::If] = true;
    _isTokenTerminal[Token::Then] = true;
    _isTokenTerminal[Token::Else] = true;
    _isTokenTerminal[Token::While] = true;
    _isTokenTerminal[Token::Do] = true;
    _isTokenTerminal[Token::Case] = true;
    _isTokenTerminal[Token::Of] = true;
    _isTokenTerminal[Token::Otherwise] = true;
    _isTokenTerminal[Token::Repeat] = true;
    _isTokenTerminal[Token::For] = true;
    _isTokenTerminal[Token::Until] = true;
    _isTokenTerminal[Token::Loop] = true;
    _isTokenTerminal[Token::Pool] = true;
    _isTokenTerminal[Token::Exit] = true;
    _isTokenTerminal[Token::Mod] = true;
    _isTokenTerminal[Token::And] = true;
    _isTokenTerminal[Token::Or] = true;
    _isTokenTerminal[Token::Not] = true;
    _isTokenTerminal[Token::Read] = true;
    _isTokenTerminal[Token::Successor] = true;
    _isTokenTerminal[Token::Predecessor] = true;
    _isTokenTerminal[Token::CharFun] = true;
    _isTokenTerminal[Token::OrdFun] = true;

    isInitialized = true;
  }

  // Dynamically calculate the longest token
  auto longestToken = std::max_element(this->_tokenRepresentationMap.begin(),
                                       this->_tokenRepresentationMap.end(),
                                       [](std::pair<Token, std::string> a, std::pair<Token, std::string> b) {
                                         return a.second.length() < b.second.length();
                                       });
  this->_maxLookupSize = longestToken->second.length();
}

TinyLexicalAnalyzer::~TinyLexicalAnalyzer()
{
}

std::map<size_t, std::string> TinyLexicalAnalyzer::getValues()
{
  return this->_valuesMap;
}

std::queue<TinyLexicalAnalyzer::Token> TinyLexicalAnalyzer::getTokens()
{
  return this->_tokens;
}

std::string TinyLexicalAnalyzer::convertTokenToString(Token token)
{
  switch (token)
  {
  case Token::Character:
    return "<char>";
  case Token::String:
    return "<string>";
  case Token::Number:
    return "<number>";
  case Token::Identifier:
    return "<identifier>";
  default:
    return _tokenRepresentationMap.at(token);
  }
}

TinyLexicalAnalyzer::Token TinyLexicalAnalyzer::convertStringToToken(std::string string)
{
  // Abusing the standards, yay...
  // https://tinyurl.com/y7m4c9mf -> Shortened SO Link
  for (auto it = this->_tokenRepresentationMap.begin(); it != this->_tokenRepresentationMap.end(); ++it)
  {
    if (it->second == string)
    {
      return it->first;
    }
  }

  throw std::out_of_range("Not Found");
}

// TODO: Do this with Regexes instead for cleanness/versatility
void TinyLexicalAnalyzer::analyzeProgram(std::istream &tinyProgram)
{
  while (!tinyProgram.eof())
  {
    char nextChar = tinyProgram.get();

    // Skip processing on New Lines/whitespace OR within comments = Highest Precedence
    switch (nextChar)
    {
    case '\n':
      _insideCommentBlockType1 = false;
      _lineNumber++;
      continue;
    case '{':
      _insideCommentBlockType2 = true;
      continue;
    case '}':
      _insideCommentBlockType2 = false;
      continue;
    case '#':
      _insideCommentBlockType1 = true;
      continue;
    }

    // If not whitespace OR comment, then let's actually process with lookahead.
    if (!isspace(nextChar) && !_insideCommentBlockType1 && !_insideCommentBlockType2)
    {
      // Record current state for resets/rewinding
      const int initialLocation = tinyProgram.tellg();

      // Recognition Hierarchy = Char -> String -> Keyword -> Number -> Identifier
      if (handleCharsAndStrings(tinyProgram, nextChar)) // is Atomic, no need to unwind if no token
        continue;

      if (handleKeywords(tinyProgram, nextChar)) // Always winds forward, if no token unwind
        continue;
      else
      {
        tinyProgram.clear();
        tinyProgram.seekg(initialLocation);
      }

      if (handleNumbersAndIdentifiers(tinyProgram, nextChar)) // Non-Atomic, need to unwind
        continue;
      else
      {
        tinyProgram.clear();
        tinyProgram.seekg(initialLocation);
      }

      if (nextChar == EOF) {
        return;
      }

      char errorBuffer[115];
      sprintf(errorBuffer, "Lexical Analyzer failed to translate string starting with \'%c\'"
                           " on line %d into a token or identifier.",
              nextChar, _lineNumber);
      throw std::invalid_argument(errorBuffer);
    }
  }

  return;
}

bool TinyLexicalAnalyzer::handleCharsAndStrings(std::istream &tinyProgram, char nextChar)
{
  std::string textBuffer;

  // Check for Character
  if (nextChar == '\'')
  {
    textBuffer.push_back(tinyProgram.get());
    nextChar = tinyProgram.get();

    _tokens.push(Token::Character);

    if (textBuffer == "\'")
    {
      this->_valuesMap[_tokens.size() - 1] = "";
      return true;
    }
    else
      this->_valuesMap[_tokens.size() - 1] = std::string(textBuffer.begin(), textBuffer.end());

    if (nextChar != '\'')
    {
      char errorBuffer[115];

      sprintf(errorBuffer, "Lexical Analyzer failed to parse character token on line %d into a token"
                           " or identifier.",
              _lineNumber);

      throw std::invalid_argument(errorBuffer);
    }

    return true;
  }

  // Check for String
  if (nextChar == '\"')
  {
    do
    {
      nextChar = tinyProgram.get();
      textBuffer.push_back(nextChar);

      if (nextChar == EOF)
      {
        char errorBuffer[115];
        sprintf(errorBuffer, "Reached EOF while reading a string starting on line %d", _lineNumber);
        throw std::invalid_argument(errorBuffer);
      }
    } while (nextChar != '\"');

    _tokens.push(Token::String);

    if (textBuffer == "\"")
      this->_valuesMap[_tokens.size() - 1] = "";
    else
      this->_valuesMap[_tokens.size() - 1] = std::string(textBuffer.begin(), textBuffer.end() - 1);

    return true;
  }

  return false;
}

bool TinyLexicalAnalyzer::handleKeywords(std::istream &tinyProgram, char nextChar)
{
  // Check for language keyword
  std::string textBuffer;
  textBuffer.push_back(nextChar);

  for (size_t i = 0; i < this->_maxLookupSize; i++)
    textBuffer.push_back(tinyProgram.get());

  while (textBuffer.length() > 0)
  {
    if (textBuffer.at(0) == EOF) {
      return false;
    }

    try
    {
      Token token = convertStringToToken(textBuffer);

      if (this->_isTokenTerminal[token]) {
        char tempCheck = tinyProgram.get();
        tinyProgram.unget();

        if (isalpha(tempCheck)) {
          throw std::out_of_range("Token is part of a larger word");
        }
      }

      _tokens.push(token);
      return true;
    }
    catch (const std::out_of_range &e)
    {
    }

    tinyProgram.unget();
    textBuffer.pop_back();
  }

  return false;
}

bool TinyLexicalAnalyzer::handleNumbersAndIdentifiers(std::istream &tinyProgram, char nextChar)
{
  std::string textBuffer;
  textBuffer.push_back(nextChar);

  if (isdigit(nextChar))
  {
    // If starts with a number, must be a number...
    while (isdigit(nextChar))
    {
      nextChar = tinyProgram.get();
      textBuffer.push_back(nextChar);
    }

    _tokens.push(Token::Number);
    this->_valuesMap[_tokens.size() - 1] = std::string(textBuffer.begin(), textBuffer.end() - 1);

    tinyProgram.unget();
    return true;
  }
  else if (isalpha(nextChar) || nextChar == '_')
  {
    // If starts with a letter or underscore, must be an identifier...
    while (isalnum(nextChar) || nextChar == '_')
    {
      nextChar = tinyProgram.get();
      textBuffer.push_back(nextChar);
    }

    _tokens.push(Token::Identifier);
    this->_valuesMap[_tokens.size() - 1] = std::string(textBuffer.begin(), textBuffer.end() - 1);

    tinyProgram.unget();
    return true;
  }

  return false;
}
