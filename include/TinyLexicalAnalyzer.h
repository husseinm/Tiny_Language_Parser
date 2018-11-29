#ifndef TINY_LEXICAL_ANALYZER_H
#define TINY_LEXICAL_ANALYZER_H

#include <string>
#include <map>
#include <vector>
#include <regex>

class TinyLexicalAnalyzer
{
public:
  TinyLexicalAnalyzer();
  ~TinyLexicalAnalyzer();

  // The token order listed here, not in the constructor,
  //  is what determines parsing matching order
  enum Token
  {
    Program,
    Variable,
    Constant,
    Type,
    Function,
    Return,
    Begin,
    End,
    Swap,
    Assignment,
    Integer,
    Output,
    If,
    Then,
    Else,
    While,
    Do,
    Case,
    Of,
    Elipses,
    Otherwise,
    Repeat,
    For,
    Until,
    Loop,
    Pool,
    Exit,
    LE,
    NE,
    LT,
    GE,
    GT,
    Eq,
    Mod,
    And,
    Or,
    Not,
    Read,
    Successor,
    Predecessor,
    CharFun,
    OrdFun,
    Eof,
    Colon,
    Semicolon,
    Dot,
    Comma,
    OpenBracket,
    CloseBracket,
    Plus,
    Minus,
    Multiply,
    Divide,
    Identifier,
    Number,
    Character,
    String
  };

  void analyzeProgram(std::istream &tinyProgram);

  std::vector<Token> getTokens();
  std::map<size_t, std::string> getValues();

  std::string convertTokenToString(Token token);

private:
  Token convertStringToToken(std::string string);

  bool handleCharsAndStrings(std::istream &tinyProgram, char nextChar);
  bool handleKeywords(std::istream &tinyProgram, char nextChar);
  bool handleNumbersAndIdentifiers(std::istream &tinyProgram, char nextChar);

  std::vector<Token> _tokens;
  // TODO: Replace with unordered_map
  std::map<Token, std::string> _tokenRepresentationMap;
  std::map<size_t, std::string> _valuesMap;
  size_t _maxLookupSize;
  bool _insideCommentBlockType1;
  bool _insideCommentBlockType2;
  int _lineNumber;
};

#endif
