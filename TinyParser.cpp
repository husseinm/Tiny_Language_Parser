#include <iostream>

#include "./include/parser/TinyParser.h"

TinyParser::TinyParser()
{
  this->_ast = TreeNode();

  TreeNode subChild1 = TreeNode();
  subChild1.type = TreeNode::Type::Assignment;

  TreeNode child1 = TreeNode();
  child1.type = TreeNode::Type::And;
  child1.children.push_back(subChild1);

  this->_ast.type = TreeNode::Type::Program;
  this->_ast.children.push_back(child1);
  this->_ast.children.push_back(child1);
}

TinyParser::~TinyParser()
{
}

TreeNode TinyParser::getAst()
{
  return this->_ast;
}

void TinyParser::parseProgram(std::queue<TinyLexicalAnalyzer::Token> tokens,
                              std::map<size_t, std::string> values)
{
  this->tokens = &tokens;
  this->values = &values;

  Tiny();
}

void TinyParser::Tiny(){};

void TinyParser::Consts(){};

void TinyParser::Const(){};

void TinyParser::ConstValue(){};

void TinyParser::Types(){};

void TinyParser::TypeNode(){};

void TinyParser::LitList(){};

void TinyParser::SubProgs(){};

void TinyParser::Fcn(){};

void TinyParser::Params(){};

void TinyParser::Dclns(){};

void TinyParser::Dcln(){};

void TinyParser::Body(){};

void TinyParser::Statement(){};

void TinyParser::OutExp(){};

void TinyParser::StringNode(){};

void TinyParser::CaseClauses(){};

void TinyParser::CaseClause(){};

void TinyParser::CaseExpression(){};

void TinyParser::OtherwiseClause(){};

void TinyParser::AssignmentNode(){};

void TinyParser::ForStat(){};

void TinyParser::ForExp(){};

void TinyParser::Expression(){};

void TinyParser::Term(){};

void TinyParser::Factor(){};

void TinyParser::Primary(){};

void TinyParser::Name(){};
