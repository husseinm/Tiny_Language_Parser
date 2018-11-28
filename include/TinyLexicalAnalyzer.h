#ifndef TINY_LEXICAL_ANALYZER_H
#define TINY_LEXICAL_ANALYZER_H

#include <string>
#include <map>
#include <vector>

class TinyLexicalAnalyzer
{
public:
  TinyLexicalAnalyzer();
  ~TinyLexicalAnalyzer();

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
    Divide
  };

  std::vector<Token> analyzeProgram(std::istream &tinyProgram);
  std::string convertTokenToString(Token token);

private:
  Token convertStringToToken(std::string string);

  std::map<Token, std::string> tokenRepresentationMap;
  /*
  const std::vector<std::string> tokenRepresentations = {"\n", "program", "var", "const", "type", "function", "return", "begin", "end", ":=:", ":=", "output", "if", "then", "else", "while", "do", "case", "of", "..", "otherwise", "repeat", "for", "until", "loop", "pool", "exit", "<=", "<>", "<", ">=", ">", "=", "mod", "and", "or", "not", "read", "succ", "pred", "chr", "ord", "eof", "{", ":", ";", ".", ",", "(", ")", "+", "-", "*", "/"};
  */
};

#endif
