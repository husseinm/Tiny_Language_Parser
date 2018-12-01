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
  size_t initialQueueSize;

  void assertNextToken(TinyLexicalAnalyzer::Token expected);

  void Tiny();
  TreeNode Consts();
  TreeNode Const();
  TreeNode ConstValue();
  TreeNode Types();
  TreeNode TypeNode();
  TreeNode LitList();
  TreeNode SubProgs();
  TreeNode Fcn();
  TreeNode Params();
  TreeNode Dclns();
  TreeNode Dcln();
  TreeNode Body();
  TreeNode Statement();
  TreeNode OutExp();
  TreeNode StringNode();
  TreeNode CaseClauses();
  TreeNode CaseClause();
  TreeNode CaseExpression();
  TreeNode OtherwiseClause();
  TreeNode AssignmentNode();
  TreeNode ForStat();
  TreeNode ForExp();
  TreeNode Expression();
  TreeNode Term();
  TreeNode Factor();
  TreeNode Primary();
  TreeNode Name();

  TreeNode ValueNode();
};

#endif
