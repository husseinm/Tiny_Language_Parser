#ifndef TINY_PARSER_H
#define TINY_PARSER_H

#include "../TreeNode.h"
#include "../lexical_analyzer/TinyLexicalAnalyzer.h"

// Implemented via Recursive Descent
class TinyParser
{
public:
  TinyParser();
  ~TinyParser();

  void parseProgram(std::queue<TinyLexicalAnalyzer::Token> tokens,
                    std::map<size_t, std::string> values);
  TreeNode getAst();

private:
  TreeNode _ast;

  std::queue<TinyLexicalAnalyzer::Token> *tokens;
  std::map<size_t, std::string> *values;

  void assertNextToken(TinyLexicalAnalyzer::Token expected);

  void Tiny();
  void Consts();
  void Const();
  void ConstValue();
  void Types();
  void TypeNode();
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
  void AssignmentNode();
  void ForStat();
  void ForExp();
  void Expression();
  void Term();
  void Factor();
  void Primary();
  void Name();
};

#endif