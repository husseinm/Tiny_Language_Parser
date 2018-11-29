#ifndef TINY_PARSER_H
#define TINY_PARSER_H

#include "./include/TinyLexicalAnalyzer.h"

// Implemented via Recursive Descent
class TinyParser
{
public:
  TinyParser();
  ~TinyParser();

  enum Node
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

  struct TreeNode
  {
    std::vector<TreeNode> children;
    TreeNode *parent;
    Node type;
    void *data;
  };

  void parseProgram(std::vector<TinyLexicalAnalyzer::Token> tokens,
                    std::map<size_t, std::string> values);
  TreeNode getAst();
  void printAst();

private:
  TreeNode _ast;

  void printAstLayer(int layer);

  void Tiny();
  void Consts();
  void Const();
  void ConstValue();
  void Types();
  void Type();
  void LitList();
  void SubProgs();
  void Fcn();
  void Params();
  void Dclns();
  void Dcln();
  void Body();
  void Statement();
  void OutExp();
  void StringNode();
  void CaseClauses();
  void CaseClause();
  void CaseExpression();
  void OtherwiseClause();
  void Assignment();
  void ForStat();
  void ForExp();
  void Expression();
  void Term();
  void Factor();
  void Primary();
  void Name();
};

#endif